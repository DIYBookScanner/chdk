/*
 *
 * Copyright (C) 2010-2012 <reyalp (at) gmail dot com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/*
 * functions for handling remote camera display
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#if defined(CHDKPTP_CD)
#include <cd.h>
#include <cdlua.h>
#endif
#include "core/live_view.h"
#include "lbuf.h"
#include "liveimg.h"
/*
planar img
TODO would make sense to use a CD bitmap for this but not public
also may want image handling without CD, but probably want packed rather than planar

TODO if we do packed, might want to make planar and packed use same struct with type flag
*/
typedef struct {
	unsigned width;
	unsigned height;
	uint8_t *data;
	uint8_t *r;
	uint8_t *g;
	uint8_t *b;
	uint8_t *a;
} liveimg_pimg_t;

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} palette_entry_rgba_t;

typedef struct {
	uint8_t a;
	uint8_t y;
	int8_t u;
	int8_t v;
} palette_entry_ayuv_t;

typedef struct {
	int8_t v;
	int8_t u;
	uint8_t y;
	uint8_t a;
} palette_entry_vuya_t;

typedef void (*yuv_palette_to_rgba_fn)(const char *pal_yuv, uint8_t pixel,palette_entry_rgba_t *pal_rgb);

void palette_type1_to_rgba(const char *palette, uint8_t pixel, palette_entry_rgba_t *pal_rgb);
void palette_type2_to_rgba(const char *palette, uint8_t pixel, palette_entry_rgba_t *pal_rgb);
void palette_type3_to_rgba(const char *palette, uint8_t pixel, palette_entry_rgba_t *pal_rgb);
void palette_type4_to_rgba(const char *palette, uint8_t pixel, palette_entry_rgba_t *pal_rgb);
void palette_type5_to_rgba(const char *palette, uint8_t pixel, palette_entry_rgba_t *pal_rgb);

void yuv_live_to_cd_rgb(const char *p_yuv,
						unsigned buf_width,
						unsigned width,unsigned height,
						int skip,
						uint8_t *r,uint8_t *g,uint8_t *b);

// from a540, playback mode
static const char palette_type1_default[]={
0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0x00, 0x00, 0xff, 0x60, 0xee, 0x62, 0xff, 0xb9, 0x00, 0x00,
0x7f, 0x00, 0x00, 0x00, 0xff, 0x7e, 0xa1, 0xb3, 0xff, 0xcc, 0xb8, 0x5e, 0xff, 0x5f, 0x00, 0x00,
0xff, 0x94, 0xc5, 0x5d, 0xff, 0x8a, 0x50, 0xb0, 0xff, 0x4b, 0x3d, 0xd4, 0x7f, 0x28, 0x00, 0x00,
0x7f, 0x00, 0x7b, 0xe2, 0xff, 0x30, 0x00, 0x00, 0xff, 0x69, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
};

typedef struct {
	yuv_palette_to_rgba_fn to_rgba;
	unsigned num_entries;
} palette_convert_t;

// type implied from index
// TODO only one function for now
palette_convert_t palette_funcs[] = {
	{NULL,0}, 					// type 0 - no palette, we could have a default func here
	{palette_type1_to_rgba,16},	// type 1 - ayuv, 16 entries double 4 bit index
	{palette_type2_to_rgba,16}, 	// type 2 - like type 1, but with 2 bit alpha lookup - UNTESTED
	{palette_type3_to_rgba,256}, 	// type 3 - vuya, 256 entries, 2 bit alpha lookup
	{palette_type4_to_rgba,16}, 	// type 4 - with 2 bit alpha lookup like 2
	{palette_type5_to_rgba,256}, 	// type 5 - vuya, 256 entries, 6 bit alpha lookup (only 2 bits used)
};

#define N_PALETTE_FUNCS (sizeof(palette_funcs)/sizeof(palette_funcs[0]))

static palette_convert_t* get_palette_convert(unsigned type) {
	if(type<N_PALETTE_FUNCS) {
		return &(palette_funcs[type]);
	}
	return NULL;
}

static unsigned get_palette_size(unsigned type) {
	palette_convert_t* convert = get_palette_convert(type);
	if(convert) {
		return convert->num_entries*4;
	}
	return 0;
}

static uint8_t clip_yuv(int v) {
	if (v<0) return 0;
	if (v>255) return 255;
	return v;
}

static uint8_t yuv_to_r(uint8_t y, int8_t v) {
	return clip_yuv(((y<<12) +          v*5743 + 2048)>>12);
}

static uint8_t yuv_to_g(uint8_t y, int8_t u, int8_t v) {
	return clip_yuv(((y<<12) - u*1411 - v*2925 + 2048)>>12);
}

static uint8_t yuv_to_b(uint8_t y, int8_t u) {
	return clip_yuv(((y<<12) + u*7258          + 2048)>>12);
}

static uint8_t clamp_uint8(unsigned v) {
	return (v>255)?255:v;
}

static int8_t clamp_int8(int v) {
	if(v>127) {
		return 127;
	}
	if(v<-128) {
		return -128;
	}
	return v;
}

void palette_type1_to_rgba(const char *palette, uint8_t pixel,palette_entry_rgba_t *pal_rgb) {
	const palette_entry_ayuv_t *pal = (const palette_entry_ayuv_t *)palette;
	unsigned i1 = pixel & 0xF;
	unsigned i2 = (pixel & 0xF0)>>4;
	int8_t u,v;
	uint8_t y;
	pal_rgb->a = (pal[i1].a + pal[i2].a)>>1;
	// TODO not clear if combined should be /2 or not
	// special case in canon firmware, if lower 4 bits 0, grays
	if(i1 == 0) {
		u = v = 0;
	} else {
		u = clamp_int8(pal[i1].u + pal[i2].u);
		v = clamp_int8(pal[i1].v + pal[i2].v);
	}
	y = clamp_uint8(pal[i1].y + pal[i2].y);
	pal_rgb->r = yuv_to_r(y,v);
	pal_rgb->g = yuv_to_g(y,u,v);
	pal_rgb->b = yuv_to_b(y,u);
}

static const uint8_t alpha2_lookup[] = {128,171,214,255};
// like above, but with alpha lookup
// TODO this is untested an probably wrong
void palette_type2_to_rgba(const char *palette, uint8_t pixel,palette_entry_rgba_t *pal_rgb) {
	const palette_entry_ayuv_t *pal = (const palette_entry_ayuv_t *)palette;
	unsigned i1 = pixel & 0xF;
	unsigned i2 = (pixel & 0xF0)>>4;
	int8_t u,v;
	uint8_t y;
	uint8_t a = (pal[i1].a + pal[i2].a)>>1;
	pal_rgb->a = alpha2_lookup[a&3];
	// TODO not clear if these should be /2 or not
	y = clamp_uint8(pal[i1].y + pal[i2].y);
	u = clamp_int8(pal[i1].u + pal[i2].u);
	v = clamp_int8(pal[i1].v + pal[i2].v);
	pal_rgb->r = yuv_to_r(y,v);
	pal_rgb->g = yuv_to_g(y,u,v);
	pal_rgb->b = yuv_to_b(y,u);
}

// Convert 32 bit AYUV palette to RGB.
// Assumes A only uses 2 bits - 'shift' parameter used to scale A value.
void palette_AYUV_to_rgba(const char *palette, uint8_t pixel, palette_entry_rgba_t *pal_rgb, int shift) {
	const palette_entry_vuya_t *pal = (const palette_entry_vuya_t *)palette;
	// special case for index 0
	if(pixel == 0) {
		pal_rgb->a = pal_rgb->r = pal_rgb->g = pal_rgb->b = 0;
		return;
	}
	pal_rgb->a = alpha2_lookup[(pal[pixel].a>>shift)&3];
	pal_rgb->r = yuv_to_r(pal[pixel].y,pal[pixel].v);
	pal_rgb->g = yuv_to_g(pal[pixel].y,pal[pixel].u,pal[pixel].v);
	pal_rgb->b = yuv_to_b(pal[pixel].y,pal[pixel].u);
}

void palette_type3_to_rgba(const char *palette, uint8_t pixel,palette_entry_rgba_t *pal_rgb) {
    palette_AYUV_to_rgba(palette, pixel, pal_rgb, 0);
}

// like 2, but vuya
void palette_type4_to_rgba(const char *palette, uint8_t pixel,palette_entry_rgba_t *pal_rgb) {
	const palette_entry_vuya_t *pal = (const palette_entry_vuya_t *)palette;
	unsigned i1 = pixel & 0xF;
	unsigned i2 = (pixel & 0xF0)>>4;
	int8_t u,v;
	uint8_t y;
	// special case for index 0
	if(pixel == 0) {
		pal_rgb->a = pal_rgb->r = pal_rgb->g = pal_rgb->b = 0;
		return;
	}

	// TODO this isn't right for sx110
	uint8_t a = (pal[i1].a + pal[i2].a)>>1;
	pal_rgb->a = alpha2_lookup[a&3];
	// TODO not clear if these should be /2 or not
	y = clamp_uint8(pal[i1].y + pal[i2].y);
	u = clamp_int8(pal[i1].u + pal[i2].u);
	v = clamp_int8(pal[i1].v + pal[i2].v);
	pal_rgb->r = yuv_to_r(y,v);
	pal_rgb->g = yuv_to_g(y,u,v);
	pal_rgb->b = yuv_to_b(y,u);
}

void palette_type5_to_rgba(const char *palette, uint8_t pixel,palette_entry_rgba_t *pal_rgb) {
    palette_AYUV_to_rgba(palette, pixel, pal_rgb, 4);
}

void yuv_live_to_cd_rgb(const char *p_yuv,
						unsigned buf_width,
						unsigned width,unsigned height,
						int skip,
						uint8_t *r,uint8_t *g,uint8_t *b) {
	unsigned x,row;
	unsigned row_inc = (buf_width*12)/8;
	const char *p;
	// start at end to flip for CD
	const char *p_row = p_yuv + (height - 1) * row_inc;
	for(row=0;row<height;row++,p_row -= row_inc) {
		for(x=0,p=p_row;x<width;x+=4,p+=6) {
			*r++ = yuv_to_r(p[1],p[2]);
			*g++ = yuv_to_g(p[1],p[0],p[2]);
			*b++ = yuv_to_b(p[1],p[0]);

			*r++ = yuv_to_r(p[3],p[2]);
			*g++ = yuv_to_g(p[3],p[0],p[2]);
			*b++ = yuv_to_b(p[3],p[0]);
			if(!skip) {
				// TODO it might be better to use the next pixels U and V values
				*r++ = yuv_to_r(p[4],p[2]);
				*g++ = yuv_to_g(p[4],p[0],p[2]);
				*b++ = yuv_to_b(p[4],p[0]);

				*r++ = yuv_to_r(p[5],p[2]);
				*g++ = yuv_to_g(p[5],p[0],p[2]);
				*b++ = yuv_to_b(p[5],p[0]);
			}
		}
	}
}

static void pimg_destroy(liveimg_pimg_t *im) {
	free(im->data);
	im->width = im->height = 0;
	im->data = im->r = im->g = im->b = im->a = NULL;
}

static int pimg_gc(lua_State *L) {
	liveimg_pimg_t *im = (liveimg_pimg_t *)luaL_checkudata(L,1,LIVEIMG_PIMG_META);
	pimg_destroy(im);
	return 0;
}

static int pimg_get_width(lua_State *L) {
	liveimg_pimg_t *im = (liveimg_pimg_t *)luaL_checkudata(L,1,LIVEIMG_PIMG_META);
	if(!im->data) {
		return luaL_error(L,"dead pimg");
	}
	lua_pushnumber(L,im->width);
	return 1;
}

static int pimg_get_height(lua_State *L) {
	liveimg_pimg_t *im = (liveimg_pimg_t *)luaL_checkudata(L,1,LIVEIMG_PIMG_META);
	if(!im->data) {
		return luaL_error(L,"dead pimg");
	}
	lua_pushnumber(L,im->height);
	return 1;
}

static int pimg_kill(lua_State *L) {
	liveimg_pimg_t *im = (liveimg_pimg_t *)luaL_checkudata(L,1,LIVEIMG_PIMG_META);
	pimg_destroy(im);
	return 0;
}

/*
create a new pimg and push it on the stack
TODO might want to pass in width, height or data, but need to handle rgb vs rgba
*/
int pimg_create(lua_State *L) {
	liveimg_pimg_t *im = (liveimg_pimg_t *)lua_newuserdata(L,sizeof(liveimg_pimg_t));
	if(!im) {
		return 0;
	}
	im->width = im->height = 0;
	im->data = im->r = im->g = im->b = im->a = NULL;
	luaL_getmetatable(L, LIVEIMG_PIMG_META);
	lua_setmetatable(L, -2);

	return 1;
}

int pimg_init_rgb(liveimg_pimg_t *im,unsigned width,unsigned height) {
	unsigned size = width*height;
	if(!size) {
		return 0;
	}
	im->data=malloc(size*3);
	if(!im->data) {
		return 0;
	}
	im->width = width;
	im->height = height;
	im->r=im->data;
	im->g=im->r+size;
	im->b=im->g+size;
	im->a=NULL;
	return 1;
}

/*
TODO stupid copy/paste
*/
int pimg_init_rgba(liveimg_pimg_t *im,unsigned width,unsigned height) {
	unsigned size = width*height;
	if(!size) {
		return 0;
	}
	im->data=malloc(size*4);
	if(!im->data) {
		return 0;
	}
	im->width = width;
	im->height = height;
	im->r=im->data;
	im->g=im->r+size;
	im->b=im->g+size;
	im->a=im->b+size;
	return 1;
}

/*
check whether given stack index is an pimg, and if so, return it
*/
liveimg_pimg_t * pimg_get(lua_State *L,int i) {
	if(!lua_isuserdata(L,i)) {
		return NULL;
	}
	if(lua_islightuserdata(L,i)) {
		return NULL;
	}
	if(!lua_getmetatable(L,i)) {
		return NULL;
	}
	lua_getfield(L,LUA_REGISTRYINDEX,LIVEIMG_PIMG_META);
	int r = lua_rawequal(L,-1,-2);
	lua_pop(L,2);
	if(r) {
		return lua_touserdata(L,i);
	}
	return NULL;
}

/*
check framebuffer desc values, and return a descriptive error or NULL
*/
static const char * check_fb_desc(lv_framebuffer_desc **desc_out,lv_data_header *frame, int expect_type,int data_len) {
	int bpp;
	int start;
	lv_framebuffer_desc *desc;
	// note, if there's ever more than on possible type for viewport or bitmap, this will need to change
	switch(expect_type) {
		case LV_FB_YUV8:
			bpp = 12;
			start = frame->vp_desc_start;
			break;
		case LV_FB_PAL8:
			bpp = 8;
			start = frame->bm_desc_start;
			break;
		default:
			return "invalid type";
	}
		
	if( start + sizeof(lv_framebuffer_desc) > data_len) {
		return "data < fb_desc";
	}

	desc = (lv_framebuffer_desc *)((char *)frame + start);
	if(desc->fb_type != expect_type) {
		return "incorrect type";
	}

	// note, we can get a frame with no FB data
	if(desc->data_start && desc->data_start + (desc->buffer_width*desc->visible_height*bpp)/8 > data_len) {
		return "data < buffer_width*height";
	}

	if(desc->visible_width > desc->buffer_width) {
		return "width  > buffer_width";
	}
	*desc_out = desc;
	return NULL;
}

/*
convert viewport data to RGB pimg
pimg=liveimg.get_viewport_pimg(pimg,live_frame,skip)
pimg: pimg to re-use, created if nil, replaced if size doesn't match
live_fream: from get_live_data
skip: boolean - if true, each U Y V Y Y Y is converted to 2 pixels, otherwise 4
returns nil if info does not contain a live view
*/
static int liveimg_get_viewport_pimg(lua_State *L) {
	lv_data_header *frame;
	lv_framebuffer_desc *vp;

	liveimg_pimg_t *im = pimg_get(L,1);
	lBuf_t *frame_lb = luaL_checkudata(L,2,LBUF_META);
	int skip = lua_toboolean(L,3);
	// pixel aspect ratio
	int par = (skip == 1)?2:1;

	frame = (lv_data_header *)frame_lb->bytes;
	const char *fb_desc_err = check_fb_desc(&vp,frame,LV_FB_YUV8,frame_lb->len);
	if(fb_desc_err) {
		return luaL_error(L,fb_desc_err);
	}

	// this is not currently an error, if sent live data without viewport selected, just return nil image
	if(!vp->data_start) {
		lua_pushnil(L);
		return 1;
	}

	unsigned vwidth = vp->visible_width/par;
	unsigned dispsize = vwidth*vp->visible_height;

	if(im && dispsize != im->width*im->height) {
		pimg_destroy(im);
		im = NULL;
	}
	if(im) {
		lua_pushvalue(L, 1); // copy im onto top for return
		// set width and height, could have changed without changing byte count
		im->width = vwidth;
		im->height = vp->visible_height;
	} else { // create an new im 
		pimg_create(L);
		im = luaL_checkudata(L,-1,LIVEIMG_PIMG_META);
		if(!pimg_init_rgb(im,vwidth,vp->visible_height)) {
			return luaL_error(L,"failed to create image");
		}
	}

	yuv_live_to_cd_rgb(frame_lb->bytes+vp->data_start,
						vp->buffer_width,
						vp->visible_width,
						vp->visible_height,
						skip,
						im->r,im->g,im->b);
	return 1;
}

static void convert_palette(palette_entry_rgba_t *pal_rgba,lv_data_header *frame) {
	const char *pal=NULL;
	palette_convert_t *convert=get_palette_convert(frame->palette_type);
	if(!convert || !frame->palette_data_start) {
		convert = get_palette_convert(1);
		pal = palette_type1_default;
	} else {
		pal = ((char *)frame + frame->palette_data_start);
	}
	yuv_palette_to_rgba_fn fn = convert->to_rgba;
	int i;
	for(i=0;i<256;i++) {
		fn(pal,i,&pal_rgba[i]);
	}
}

/*
convert bitmap data to RGBA pimg
pimg=liveimg.get_bitmap_pimg(pimg,frame,skip)
pimg: pimg to re-use, created if nil, replaced if size doesn't match
frame: from live_get_data
skip: boolean - if true, every other pixel in the x axis is discarded (for viewports with a 1:2 par)
returns nil if info does not contain a bitmap
*/
static int liveimg_get_bitmap_pimg(lua_State *L) {
	palette_entry_rgba_t pal_rgba[256];

	lv_data_header *frame;
	lv_framebuffer_desc *bm;

	liveimg_pimg_t *im = pimg_get(L,1);
	lBuf_t *frame_lb = luaL_checkudata(L,2,LBUF_META);
	int skip = lua_toboolean(L,3);
	// pixel aspect ratio
	int par = (skip == 1)?2:1;

	frame = (lv_data_header *)frame_lb->bytes;
	const char *fb_desc_err = check_fb_desc(&bm,frame,LV_FB_PAL8,frame_lb->len);
	if(fb_desc_err) {
		return luaL_error(L,fb_desc_err);
	}

	if(!bm->data_start) {
		lua_pushnil(L);
		return 1;
	}

	if(get_palette_size(frame->palette_type) + frame->palette_data_start > frame_lb->len) {
		return luaL_error(L,"data < palette size");
	}

	convert_palette(pal_rgba,frame);

	unsigned vwidth = bm->visible_width/par;
	unsigned dispsize = vwidth*bm->visible_height;


	if(im && dispsize != im->width*im->height) {
		pimg_destroy(im);
		im = NULL;
	}
	if(im) {
		lua_pushvalue(L, 1); // copy im onto top for return
	} else { // create an new im 
		pimg_create(L);
		im = luaL_checkudata(L,-1,LIVEIMG_PIMG_META);
		if(!pimg_init_rgba(im,vwidth,bm->visible_height)) {
			return luaL_error(L,"failed to create image");
		}
	}

	int y_inc = bm->buffer_width;
	int x_inc = par;
	int x,y;
	int height = bm->visible_height;

	uint8_t *p=((uint8_t *)frame_lb->bytes + bm->data_start) + (height-1)*y_inc;

	uint8_t *r = im->r;
	uint8_t *g = im->g;
	uint8_t *b = im->b;
	uint8_t *a = im->a;

	for(y=0;y<height;y++,p-=y_inc) {
		for(x=0;x<bm->visible_width;x+=x_inc) {
			palette_entry_rgba_t *c =&pal_rgba[*(p+x)];
			*r++ = c->r;
			*g++ = c->g;
			*b++ = c->b;
			*a++ = c->a;
		}
	}
	return 1;
}

#if defined(CHDKPTP_CD)
/*
pimg:put_to_cd_canvas(canvas, x, y, width, height, xmin, xmax, ymin, ymax)
*/
static int pimg_put_to_cd_canvas(lua_State *L) {
	liveimg_pimg_t *im = (liveimg_pimg_t *)luaL_checkudata(L,1,LIVEIMG_PIMG_META);
	cdCanvas *cnv = cdlua_checkcanvas(L,2);
	if(!im->data) {
		return luaL_error(L,"dead pimg");
	}
	// left, bottom
	int x=luaL_optint(L,3,0);
	int y=luaL_optint(L,4,0);
	// target width, height. 0 = default
	int width=luaL_optint(L,5,0);
	int height=luaL_optint(L,6,0);
	// sub image
	int xmin=luaL_optint(L,7,0);
	int xmax=luaL_optint(L,8,0);
	int ymin=luaL_optint(L,9,0);
	int ymax=luaL_optint(L,10,0);
	cdCanvasPutImageRectRGB(cnv,
							im->width,im->height, // image size
							im->r,im->g,im->b, // data
							x,y,
							width,height,
							xmin,xmax,ymin,ymax);
	return 0;
}

/*
as above, but with alpha
*/
static int pimg_blend_to_cd_canvas(lua_State *L) {
	liveimg_pimg_t *im = (liveimg_pimg_t *)luaL_checkudata(L,1,LIVEIMG_PIMG_META);
	cdCanvas *cnv = cdlua_checkcanvas(L,2);
	if(!im->data) {
		return luaL_error(L,"dead pimg");
	}
	if(!im->a) {
		return luaL_error(L,"pimg has no alpha channel");
	}
	// left, bottom
	int x=luaL_optint(L,3,0);
	int y=luaL_optint(L,4,0);
	// target width, height. 0 = default
	int width=luaL_optint(L,5,0);
	int height=luaL_optint(L,6,0);
	// sub image
	int xmin=luaL_optint(L,7,0);
	int xmax=luaL_optint(L,8,0);
	int ymin=luaL_optint(L,9,0);
	int ymax=luaL_optint(L,10,0);
	cdCanvasPutImageRectRGBA(cnv,
							im->width,im->height, // image size
							im->r,im->g,im->b,im->a, // data
							x,y,
							width,height,
							xmin,xmax,ymin,ymax);
	return 0;
}

#endif

static const luaL_Reg liveimg_funcs[] = {
  {"get_bitmap_pimg", liveimg_get_bitmap_pimg},
  {"get_viewport_pimg", liveimg_get_viewport_pimg},
  {NULL, NULL}
};

static const luaL_Reg pimg_methods[] = {
#if defined(CHDKPTP_CD)
  {"put_to_cd_canvas", pimg_put_to_cd_canvas},
  {"blend_to_cd_canvas", pimg_blend_to_cd_canvas},
#endif
  {"width", pimg_get_width},
  {"height", pimg_get_height},
  {"kill", pimg_kill},
  {NULL, NULL}
};

static const luaL_Reg pimg_meta_methods[] = {
  {"__gc", pimg_gc},
  {NULL, NULL}
};

// TODO based on lbuf,
// would be nice to have a way to extend lbuf with additional custom bindings
void liveimg_open(lua_State *L) {
	luaL_newmetatable(L,LIVEIMG_PIMG_META);
	luaL_register(L, NULL, pimg_meta_methods);  

	/* use a table of methods for the __index method */
	lua_newtable(L);
	luaL_register(L, NULL, pimg_methods);  
	lua_setfield(L,-2,"__index");

	/* global lib */
	lua_newtable(L);
	luaL_register(L, "liveimg", liveimg_funcs);  
	lua_pop(L,3);
}

