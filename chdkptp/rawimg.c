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

based on code from chdk tools/rawconvert.c and core/raw.c
*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "luautil.h"
#include "lbuf.h"
#include "rawimg.h"

#define RAWIMG_LIST "rawimg.rawimg_list" // keeps references to associated lbufs
#define RAWIMG_LIST_META "rawimg.rawimg_list_meta" // meta table


// funny case for macros
#define RAW_ENDIAN_l 0
#define RAW_ENDIAN_b 1

static const char *endian_strings[] = {
	"little",
	"big",
	NULL,
};

#define RAW_BLOCK_BYTES_8l 1

#define RAW_BLOCK_BYTES_10l 10
#define RAW_BLOCK_BYTES_10b 5

#define RAW_BLOCK_BYTES_12l 6
#define RAW_BLOCK_BYTES_12b 3

#define RAW_BLOCK_BYTES_14l 14
#define RAW_BLOCK_BYTES_14b 7

#define RAW_BLOCK_BYTES_16l 2
#define RAW_BLOCK_BYTES_16b 2

#define CFA_RED   0
#define CFA_GREEN 1
#define CFA_BLUE  2

typedef unsigned (*get_pixel_func_t)(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
typedef void (*set_pixel_func_t)(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);

typedef struct {
	unsigned bpp;
	unsigned endian;
	unsigned block_bytes;
	unsigned block_pixels;
	get_pixel_func_t get_pixel;
	set_pixel_func_t set_pixel;
} raw_format_t;

typedef struct {
	raw_format_t *fmt;
	unsigned row_bytes;
	unsigned width;
	unsigned height;
	uint8_t cfa_pattern[4];
	unsigned active_top;
	unsigned active_left;
	unsigned active_bottom;
	unsigned active_right;
	unsigned black_level;
	uint8_t *data;
} raw_image_t;

// TODO endian doesn't matter, but needs suffix for macros
unsigned raw_get_pixel_8l(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
void raw_set_pixel_8l(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);

unsigned raw_get_pixel_10l(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
void raw_set_pixel_10l(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);
unsigned raw_get_pixel_10b(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
void raw_set_pixel_10b(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);

unsigned raw_get_pixel_12l(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
void raw_set_pixel_12l(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);
unsigned raw_get_pixel_12b(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
void raw_set_pixel_12b(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);

unsigned raw_get_pixel_14l(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
void raw_set_pixel_14l(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);
unsigned raw_get_pixel_14b(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
void raw_set_pixel_14b(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);

unsigned raw_get_pixel_16l(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
void raw_set_pixel_16l(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);
unsigned raw_get_pixel_16b(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y);
void raw_set_pixel_16b(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value);


#define FMT_DEF_SINGLE(BPP,ENDIAN) \
{ \
	BPP, \
	RAW_ENDIAN_##ENDIAN, \
	RAW_BLOCK_BYTES_##BPP##ENDIAN, \
	RAW_BLOCK_BYTES_##BPP##ENDIAN*8/BPP, \
	raw_get_pixel_##BPP##ENDIAN, \
	raw_set_pixel_##BPP##ENDIAN, \
}

#define FMT_DEF(BPP) \
	FMT_DEF_SINGLE(BPP,l), \
	FMT_DEF_SINGLE(BPP,b)

raw_format_t raw_formats[] = {
	FMT_DEF_SINGLE(8,l),
	FMT_DEF(10),
	FMT_DEF(12),
	FMT_DEF(14),
	FMT_DEF(16),
};


static const int raw_num_formats = sizeof(raw_formats)/sizeof(raw_format_t);

static raw_format_t* rawimg_find_format(unsigned bpp, unsigned endian) {
	int i;
	for(i=0; i<raw_num_formats; i++) {
		raw_format_t *fmt = &raw_formats[i];
		if(fmt->bpp == bpp && (bpp == 8 || fmt->endian == endian) ) {
			return fmt;
		}
	}
	return NULL;
}

/*
return color for given x,y
*/
static unsigned cfa_color(raw_image_t *img, unsigned x, unsigned y) {
	return img->cfa_pattern[(x&1) + (y&1)*2];
}

unsigned raw_get_pixel_8l(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
	return p[y*row_bytes+x];
}

void raw_set_pixel_8l(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
	p[y*row_bytes+x] = value;
}

unsigned raw_get_pixel_10l(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
	const uint8_t *addr = p + y * row_bytes + (x/8) * 10;
	switch (x&7) {
		case 0: return ((0x3fc&(((unsigned short)addr[1])<<2)) | (addr[0] >> 6));
		case 1: return ((0x3f0&(((unsigned short)addr[0])<<4)) | (addr[3] >> 4));
		case 2: return ((0x3c0&(((unsigned short)addr[3])<<6)) | (addr[2] >> 2));
		case 3: return ((0x300&(((unsigned short)addr[2])<<8)) | (addr[5]));
		case 4: return ((0x3fc&(((unsigned short)addr[4])<<2)) | (addr[7] >> 6));
		case 5: return ((0x3f0&(((unsigned short)addr[7])<<4)) | (addr[6] >> 4));
		case 6: return ((0x3c0&(((unsigned short)addr[6])<<6)) | (addr[9] >> 2));
		case 7: return ((0x300&(((unsigned short)addr[9])<<8)) | (addr[8]));
	}
	return 0;
}

void raw_set_pixel_10l(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
	uint8_t* addr = p + y*row_bytes + (x/8)*10;
	switch (x&7) {
		case 0:
			addr[0] = (addr[0]&0x3F)|(value<<6); 
			addr[1] = value>>2;
		break;
		case 1:
			addr[0] = (addr[0]&0xC0)|(value>>4);
			addr[3] = (addr[3]&0x0F)|(value<<4);
		break;
		case 2:
			addr[2] = (addr[2]&0x03)|(value<<2);
			addr[3] = (addr[3]&0xF0)|(value>>6);
		break;
		case 3:
			addr[2] = (addr[2]&0xFC)|(value>>8); 
			addr[5] = value;
		break;
		case 4:
			addr[4] = value>>2;
			addr[7] = (addr[7]&0x3F)|(value<<6);
		break;
		case 5:
			addr[6] = (addr[6]&0x0F)|(value<<4);
			addr[7] = (addr[7]&0xC0)|(value>>4);
		break;
		case 6:
			addr[6] = (addr[6]&0xF0)|(value>>6);
			addr[9] = (addr[9]&0x03)|(value<<2);
		break;
		case 7:
			addr[8] = value;
			addr[9] = (addr[9]&0xFC)|(value>>8);
		break;
	}
}

unsigned raw_get_pixel_10b(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
	const uint8_t *addr = p + y * row_bytes + (x/4) * 5;

	switch (x&3) {
		case 0: return ((0x3fc&(((unsigned short)addr[0])<<2)) | (addr[1] >> 6));
		case 1: return ((0x3f0&(((unsigned short)addr[1])<<4)) | (addr[2] >> 4));
		case 2: return ((0x3c0&(((unsigned short)addr[2])<<6)) | (addr[3] >> 2));
		case 3: return ((0x300&(((unsigned short)addr[3])<<8)) | (addr[4]));
	}
	return 0;
}

void raw_set_pixel_10b(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
	uint8_t* addr = p + y*row_bytes + (x/4)*5;
	switch (x&3) {
		case 0:
			addr[0] = value>>2;
			addr[1] = (addr[1]&0x3F)|(value<<6); 
		break;
		case 1:
			addr[1] = (addr[1]&0xC0)|(value>>4);
			addr[2] = (addr[2]&0x0F)|(value<<4);
		break;
		case 2:
			addr[3] = (addr[3]&0x03)|(value<<2);
			addr[2] = (addr[2]&0xF0)|(value>>6);
		break;
		case 3:
			addr[3] = (addr[3]&0xFC)|(value>>8); 
			addr[4] = value;
		break;
	}
}

unsigned raw_get_pixel_12l(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
	const uint8_t *addr = p + y * row_bytes + (x/4) * 6;
	switch (x&3) {
		case 0: return ((unsigned short)(addr[1]) << 4) | (addr[0] >> 4);
		case 1: return ((unsigned short)(addr[0] & 0x0F) << 8) | (addr[3]);
		case 2: return ((unsigned short)(addr[2]) << 4) | (addr[5] >> 4);
		case 3: return ((unsigned short)(addr[5] & 0x0F) << 8) | (addr[4]);
	}
	return 0;
}

void raw_set_pixel_12l(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
	uint8_t *addr = p + y * row_bytes + (x/4) * 6;
	switch (x&3) {
		case 0: 
			addr[0] = (addr[0]&0x0F) | (value << 4);
			addr[1] = (value >> 4);
		break;
		case 1: 
			addr[0] = (addr[0]&0xF0) | (value >> 8);
			addr[3] = value;
		break;
		case 2: 
			addr[2] = (value >> 4);
			addr[5] = (addr[5]&0x0F) | (value << 4);
		break;
		case 3: 
			addr[4] = value;
			addr[5] = (addr[5]&0xF0) | (value >> 8);
		break;
	}
}

unsigned raw_get_pixel_12b(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
	const uint8_t *addr = p + y * row_bytes + (x/2) * 3;
	if (x&1)
		return ((unsigned short)(addr[1] & 0x0F) << 8) | (addr[2]);
	return ((unsigned short)(addr[0]) << 4) | (addr[1] >> 4);
}



void raw_set_pixel_12b(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
	uint8_t *addr = p + y * row_bytes + (x/2) * 3;
	switch (x&1) {
		case 0: 
			addr[0] = (unsigned char)(value >> 4);
			addr[1] = (addr[1]&0x0F) | (unsigned char)(value << 4);
		break;
		case 1: 
			addr[1] = (addr[1]&0xF0) | (unsigned char)(value >> 8);
			addr[2] = (unsigned char)value;
		break;
	}
}

unsigned raw_get_pixel_14l(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
	const uint8_t *addr = p + y * row_bytes + (x/8) * 14;
    switch (x%8) {
        case 0: return ((unsigned short)(addr[ 1])        <<  6) | (addr[ 0] >> 2);
        case 1: return ((unsigned short)(addr[ 0] & 0x03) << 12) | (addr[ 3] << 4) | (addr[ 2] >> 4);
        case 2: return ((unsigned short)(addr[ 2] & 0x0F) << 10) | (addr[ 5] << 2) | (addr[ 4] >> 6);
        case 3: return ((unsigned short)(addr[ 4] & 0x3F) <<  8) | (addr[ 7]);
        case 4: return ((unsigned short)(addr[ 6])        <<  6) | (addr[ 9] >> 2);
        case 5: return ((unsigned short)(addr[ 9] & 0x03) << 12) | (addr[ 8] << 4) | (addr[11] >> 4);
        case 6: return ((unsigned short)(addr[11] & 0x0F) << 10) | (addr[10] << 2) | (addr[13] >> 6);
        case 7: return ((unsigned short)(addr[13] & 0x3F) <<  8) | (addr[12]);
    }
	return 0;
}

void raw_set_pixel_14l(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value) 
{
    uint8_t *addr = p + y * row_bytes + (x/8) * 14;
    switch (x%8) {
        case 0: addr[ 0]=(addr[0]&0x03)|(value<< 2); addr[ 1]=value>>6;                                                         break;
        case 1: addr[ 0]=(addr[0]&0xFC)|(value>>12); addr[ 2]=(addr[ 2]&0x0F)|(value<< 4); addr[ 3]=value>>4;                   break;
        case 2: addr[ 2]=(addr[2]&0xF0)|(value>>10); addr[ 4]=(addr[ 4]&0x3F)|(value<< 6); addr[ 5]=value>>2;                   break;
        case 3: addr[ 4]=(addr[4]&0xC0)|(value>> 8); addr[ 7]=value;                                                            break;
        case 4: addr[ 6]=value>>6;                   addr[ 9]=(addr[ 9]&0x03)|(value<< 2);                                      break;
        case 5: addr[ 8]=value>>4;                   addr[ 9]=(addr[ 9]&0xFC)|(value>>12); addr[11]=(addr[11]&0x0F)|(value<<4); break;
        case 6: addr[10]=value>>2;                   addr[11]=(addr[11]&0xF0)|(value>>10); addr[13]=(addr[13]&0x3F)|(value<<6); break;
        case 7: addr[12]=value;                      addr[13]=(addr[13]&0xC0)|(value>> 8);                                      break;
    }
}

unsigned raw_get_pixel_14b(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
	const uint8_t *addr = p + y * row_bytes + (x/4) * 7;
    switch (x%4) {
        case 0: return ((unsigned short)(addr[0])        <<  6) | (addr[1] >> 2);
        case 1: return ((unsigned short)(addr[1] & 0x03) << 12) | (addr[2] << 4) | (addr[3] >> 4);
        case 2: return ((unsigned short)(addr[3] & 0x0F) << 10) | (addr[4] << 2) | (addr[5] >> 6);
        case 3: return ((unsigned short)(addr[5] & 0x3F) <<  8) | (addr[6]);
    }
	return 0;
}

void raw_set_pixel_14b(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
    uint8_t *addr = p + y * row_bytes + (x/4) * 7;
    switch (x%8) {
        case 0: addr[1]=(addr[1]&0x03)|(value<< 2); addr[0]=value>>6;                                    break;
        case 1: addr[1]=(addr[1]&0xFC)|(value>>12); addr[3]=(addr[3]&0x0F)|(value<<4); addr[2]=value>>4; break;
        case 2: addr[3]=(addr[3]&0xF0)|(value>>10); addr[5]=(addr[5]&0x3F)|(value<<6); addr[4]=value>>2; break;
        case 3: addr[5]=(addr[5]&0xC0)|(value>> 8); addr[6]=value;                                       break;
    }
}

unsigned raw_get_pixel_16l(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
	return *(unsigned short *)(p + y*row_bytes+x*2);
}

void raw_set_pixel_16l(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
	*(unsigned short *)(p + y*row_bytes+ x*2) = value;
}

unsigned raw_get_pixel_16b(const uint8_t *p, unsigned row_bytes, unsigned x, unsigned y)
{
	return p[y*row_bytes+x*2] << 8 | p[y*row_bytes+x*2+1];
}

void raw_set_pixel_16b(uint8_t *p, unsigned row_bytes, unsigned x, unsigned y, unsigned value)
{
	p[y*row_bytes+x*2] = value>>8;
	p[y*row_bytes+x*2+1] = value;
}

/*
pixel=img:get_pixel(x,y)
nil if out of bounds
*/
static int rawimg_lua_get_pixel(lua_State *L) {
	raw_image_t* img = (raw_image_t *)luaL_checkudata(L, 1, RAWIMG_META);
	unsigned x = luaL_checknumber(L,2);
	unsigned y = luaL_checknumber(L,3);
	if(x >= img->width || y >= img->height) {
		lua_pushnil(L);
	} else {
		lua_pushnumber(L,img->fmt->get_pixel(img->data,img->row_bytes,x,y));
	}
	return 1;
}

/*
img:set_pixel(x,y,value)
*/
static int rawimg_lua_set_pixel(lua_State *L) {
	raw_image_t* img = (raw_image_t *)luaL_checkudata(L, 1, RAWIMG_META);
	unsigned x = luaL_checknumber(L,2);
	unsigned y = luaL_checknumber(L,3);
	unsigned val = luaL_checknumber(L,4);
	if(x < img->width || y < img->height) {
		img->fmt->set_pixel(img->data,img->row_bytes,x,y,val);
	}
	return 0;
}

static int rawimg_lua_get_width(lua_State *L) {
	raw_image_t* img = (raw_image_t *)luaL_checkudata(L, 1, RAWIMG_META);
	lua_pushnumber(L,img->width);
	return 1;
}

static int rawimg_lua_get_height(lua_State *L) {
	raw_image_t* img = (raw_image_t *)luaL_checkudata(L, 1, RAWIMG_META);
	lua_pushnumber(L,img->height);
	return 1;
}

static int rawimg_lua_get_bpp(lua_State *L) {
	raw_image_t* img = (raw_image_t *)luaL_checkudata(L, 1, RAWIMG_META);
	lua_pushnumber(L,img->fmt->bpp);
	return 1;
}

static int rawimg_lua_get_endian(lua_State *L) {
	raw_image_t* img = (raw_image_t *)luaL_checkudata(L, 1, RAWIMG_META);
	if(img->fmt->endian == RAW_ENDIAN_l) {
		lua_pushstring(L,"little");
	} else if(img->fmt->endian == RAW_ENDIAN_b) {
		lua_pushstring(L,"big");
	} else {
		return luaL_error(L,"invalid endian");
	}
	return 1;
}

static int rawimg_lua_get_cfa_pattern(lua_State *L) {
	raw_image_t* img = (raw_image_t *)luaL_checkudata(L, 1, RAWIMG_META);
	lua_pushlstring(L, (const char *)img->cfa_pattern,4);
	return 1;
}

/*
make a simple, low quality thumbnail image
thumb=img:make_rgb_thumb(width,height)
*/
static int rawimg_lua_make_rgb_thumb(lua_State *L) {
	raw_image_t* img = (raw_image_t *)luaL_checkudata(L, 1, RAWIMG_META);
	unsigned width=luaL_checknumber(L,2);
	unsigned height=luaL_checknumber(L,3);

	// TODO active area or not should be optional
	// image active area width
	unsigned iw = img->active_right - img->active_left;
	unsigned ih = img->active_bottom - img->active_top;
	if(width > iw || height > ih) {
		return luaL_error(L,"thumb cannot be larger than active area");
	}
	if(!width  || !height) {
		return luaL_error(L,"zero dimensions not allowed");
	}
	unsigned size = width*height*3;
	uint8_t *thumb = malloc(size);
	if(!thumb) {
		return luaL_error(L,"malloc failed for thumb");
	}

	int rx=0,ry=0,gx=0,gy=0,bx=0,by=0;
	int i;
	for(i=0;i<4;i++) {
		switch(img->cfa_pattern[i]) {
			case 0: rx = i&1; ry = (i&2)>>1; break;
			case 1: gx = i&1; gy = (i&2)>>1; break; // will get hit twice, doesn't matter
			case 2: bx = i&1; by = (i&2)>>1; break;
		}
	}
	unsigned tx,ty;
	uint8_t *p = thumb;
	unsigned shift = img->fmt->bpp - 8;
	for(ty=0;ty<height;ty++) {
		for(tx=0;tx<width;tx++) {
			unsigned ix = (img->active_left + tx*iw/width)&~1;
			unsigned iy = (img->active_top + ty*ih/height)&~1;
			*p++=img->fmt->get_pixel(img->data,img->row_bytes,ix+rx,iy+ry)>>shift;
			*p++=img->fmt->get_pixel(img->data,img->row_bytes,ix+gx,iy+gy)>>shift;
			*p++=img->fmt->get_pixel(img->data,img->row_bytes,bx+gx,iy+by)>>shift;
		}
	}
	if(!lbuf_create(L, thumb, size, LBUF_FL_FREE)) {
		return luaL_error(L,"failed to create lbuf");
	}
	return 1;
}

static unsigned rawimg_get_pixel_safe(raw_image_t *img, unsigned x, unsigned y) {
	if(x >= img->width || y >= img->height) {
		return 0;
	}
	return img->fmt->get_pixel(img->data,img->row_bytes,x,y);
}
/*
interpolate over a pixel, using non-blacklevel neighbors of the same color
returns 1 if patched, 0 if not
*/
static int rawimg_patch_pixel(raw_image_t *img,unsigned x, unsigned y) {
	unsigned c = cfa_color(img,x,y);
	unsigned neigh[4];
	if(c == CFA_GREEN) {
		neigh[0] = rawimg_get_pixel_safe(img,x-1,y-1);
		neigh[1] = rawimg_get_pixel_safe(img,x+1,y-1);
		neigh[2] = rawimg_get_pixel_safe(img,x-1,y+1);
		neigh[3] = rawimg_get_pixel_safe(img,x+1,y+1);
	} else {
		neigh[0] = rawimg_get_pixel_safe(img,x-2,y);
		neigh[1] = rawimg_get_pixel_safe(img,x+2,y);
		neigh[2] = rawimg_get_pixel_safe(img,x,y-2);
		neigh[3] = rawimg_get_pixel_safe(img,x,y+2);
	}
	unsigned i,total = 0,count = 0;
	for(i=0;i<4;i++) {
		if(neigh[i] > img->black_level) {
			total += neigh[i];
			count++;
		}
	}
	if(count) {
		img->fmt->set_pixel(img->data,img->row_bytes,x,y,total/count);
		return 1;
	}
	return 0;
}

/*
patch pixels with value below a threshold
count=img:patch_pixels([badval])
badval: pixels <= this value will be patched, default 0
count: number of pixels actually modified
*/
static int rawimg_lua_patch_pixels(lua_State *L) {
	raw_image_t* img = (raw_image_t *)luaL_checkudata(L, 1, RAWIMG_META);
	unsigned badval=luaL_optnumber(L,2,0);
	unsigned x,y;
	unsigned count=0;
	for(y=img->active_top;y<img->active_bottom;y++) {
		for(x=img->active_left;x<img->active_right;x++) {
			unsigned val = img->fmt->get_pixel(img->data,img->row_bytes,x,y);
			if(val <= badval) {
				count += rawimg_patch_pixel(img,x,y);
			}
		}
	}
	lua_pushnumber(L,count);
	return 1;
}

// TODO these are identical for now
static const char *valupmod_strings[] = {
	"no",
	"shift",
	NULL,
};

static const char *valdownmod_strings[] = {
	"no",
	"shift",
	NULL,
};


/*
convert image data to a different format, returning the result in an lbuf and new rawimg
rawimg,lbuf=img:convert(options)
options {
	bpp:number
	endian:string
	-- TODO might want to allow active area only, or an arbitrary rectangle?
	lbuf:[lbuf] -- optional lbuf to store data in
	valupmod:string -- 'shift' or 'no', default no
	valdownmod:string -- 'shift' or 'no' default shift
}
*/
static int rawimg_lua_convert(lua_State *L) {
	raw_image_t* img = (raw_image_t *)luaL_checkudata(L, 1, RAWIMG_META);
	if(!lua_istable(L,2)) {
		return luaL_error(L,"expected table");
	}
	unsigned bpp = lu_table_checknumber(L,2,"bpp");
	unsigned endian = lu_table_checkoption(L,2,"endian",NULL,endian_strings);
	unsigned new_size = img->width*img->height*bpp/8;
	unsigned valupmod = lu_table_checkoption(L,2,"valupmod","no",valupmod_strings);
	unsigned valdownmod = lu_table_checkoption(L,2,"valdownmod","shift",valdownmod_strings);
	// shift for conversions to lower bpp
	int shift = 0;
	if(img->fmt->bpp > bpp) {
		if(valdownmod == 1) {
			shift = (img->fmt->bpp - bpp);
		}
	} else {
		if(valupmod == 1) {
			shift = (img->fmt->bpp - bpp);
		}
	}

	raw_image_t *newimg = (raw_image_t *)lua_newuserdata(L,sizeof(raw_image_t));
	if(!newimg) {
		return luaL_error(L,"failed to create userdata");
	}
	memcpy(newimg,img,sizeof(raw_image_t));
	newimg->fmt = rawimg_find_format(bpp,endian);
	if(!newimg->fmt) {
		return luaL_error(L,"unknown format");
	}
	newimg->row_bytes = newimg->width*bpp/8;
	newimg->black_level = img->black_level >> shift;

	luaL_getmetatable(L, RAWIMG_META);
	lua_setmetatable(L, -2);

	lBuf_t *lb = lu_table_optudata(L,2,"lbuf",LBUF_META,NULL);
	if(!lb) {
		char *data = malloc(new_size);
		if(!data) {
			return luaL_error(L,"malloc failed");
		}
		if(!lbuf_create(L, data, new_size, LBUF_FL_FREE)) {
			return luaL_error(L,"failed to create lbuf");
		}
		lb = luaL_checkudata(L,-1,LBUF_META);
	} else {
		if(lb->len != new_size) {
			return luaL_error(L,"lbuf size mismatched");
		}
		lua_pushvalue(L,2); // ensure lbuf is on top of stack
	}
	newimg->data = (uint8_t *)lb->bytes;
	// TODO this should be common code shared with bind_lbuf
	// save a reference in the registry to keep lbuf from being collected until image goes away
	lua_getfield(L,LUA_REGISTRYINDEX,RAWIMG_LIST);
	lua_pushvalue(L, -2); // our user data, for use as key
	lua_pushvalue(L, 1); // lbuf, the value
	lua_settable(L, -3); //set t[img]=lbuf
	lua_pop(L,1); // done with t
	
	// TODO could optimize the conversions where bpp or bpp and endian don't change
	int y;
	for(y=0;y<img->height;y++) {
		int x;
		for(x=0;x<img->width;x++) {
			unsigned v = img->fmt->get_pixel(img->data,img->row_bytes,x,y);
			if(shift < 0) {
				v = v<<-shift;
			} else {
				v = v>>shift;
			}
			newimg->fmt->set_pixel(newimg->data,newimg->row_bytes,x,y,v);
		}
	}

	return 2;
}


/*
img = rawimg.bind_lbuf(imgspec)
imgspec {
-- required fields
	data:lbuf
	width:number
	height:number
	bpp:number
	endian:string "little"|"big"
-- optional fields
	data_offset:number -- offset into data lbuf, default 0
	black_level -- default 0
	cfa_pattern:string -- 4 byte string
	active_area: { -- default 0,0,height,width
		top:number
		left:number
		bottom:number
		right:number
	} 
	color_matrix: -- TODO
}

*/
static int rawimg_lua_bind_lbuf(lua_State *L) {
	raw_image_t *img = (raw_image_t *)lua_newuserdata(L,sizeof(raw_image_t));
	if(!img) {
		return luaL_error(L,"failed to create userdata");
	}

	if(!lua_istable(L,1)) {
		return luaL_error(L,"expected table");
	}

	lBuf_t *buf = (lBuf_t *)lu_table_checkudata(L,1,"data",LBUF_META);

	unsigned offset = lu_table_optnumber(L,1,"data_offset",0);

	img->width = lu_table_checknumber(L,1,"width");
	img->height = lu_table_checknumber(L,1,"height");
	unsigned bpp = lu_table_checknumber(L,1,"bpp");

	unsigned endian = lu_table_checkoption(L,1,"endian",NULL,endian_strings);

	img->black_level = lu_table_optnumber(L,1,"black_level",0);

	size_t cfa_size;
	// TODO DNG cfa is relative to active area, should shift if top or left is odd
	const char *cfa_pattern = lu_table_optlstring(L,1,"cfa_pattern",NULL,&cfa_size);
	if(!cfa_pattern) {
		memset(img->cfa_pattern,0,4);
	} else if(cfa_size != 4) {
		return luaL_error(L,"unknown cfa pattern");
	} else {
		// TODO should verify contains only R,G,B
		memcpy(img->cfa_pattern,cfa_pattern,4);
	}

	// active area
	lua_getfield(L, 1, "active_area");
	if(lua_istable(L,-1)) {
		// if table present, all required
		img->active_top = lu_table_checknumber(L,-1,"top");
		img->active_left = lu_table_checknumber(L,-1,"left");
		img->active_bottom = lu_table_checknumber(L,-1,"bottom");
		img->active_right = lu_table_checknumber(L,-1,"right");
		if(img->active_top >= img->active_bottom) {
			return luaL_error(L,"active top >= bottom");
		}
		if(img->active_left >= img->active_right) {
			return luaL_error(L,"active left >= right");
		}
		if(img->active_left > img->width) {
			return luaL_error(L,"active right > width");
		}
		if(img->active_bottom > img->height) {
			return luaL_error(L,"active bottom > height");
		}
	} else {
		img->active_top = img->active_left = 0;
		img->active_right = img->width;
		img->active_bottom = img->height;
	}
	lua_pop(L,1); // pop off active area or nil
	

	img->fmt = rawimg_find_format(bpp,endian);
	if(!img->fmt) {
		return luaL_error(L,"unknown format");
	}
	
	if(img->width % img->fmt->block_pixels != 0) {
		return luaL_error(L,"width not a multiple of block size");
	}
	img->row_bytes = (img->width*img->fmt->bpp)/8;
	if(offset + img->row_bytes*img->height > buf->len) {
		return luaL_error(L,"size larger than data");
	}
	img->data = (uint8_t *)buf->bytes + offset;

	luaL_getmetatable(L, RAWIMG_META);
	lua_setmetatable(L, -2);
	
	// save a reference in the registry to keep lbuf from being collected until image goes away
	lua_getfield(L,LUA_REGISTRYINDEX,RAWIMG_LIST);
	lua_pushvalue(L, -2); // our user data, for use as key
	lua_pushvalue(L, 1); // lbuf, the value
	lua_settable(L, -3); //set t[img]=lbuf
	lua_pop(L,1); // done with t

	return 1;
}

static const luaL_Reg rawimg_lib[] = {
	{"bind_lbuf",rawimg_lua_bind_lbuf},
	{NULL, NULL}
};

// only for testing
/*
static int rawimg_gc(lua_State *L) {
	raw_image_t *img = (raw_image_t *)luaL_checkudata(L,1,RAWIMG_META);
	printf("collecting img %p:%dx%d\n",img->data,img->width,img->height);
	return 0;
}

static const luaL_Reg rawimg_meta_methods[] = {
  {"__gc", rawimg_gc},
  {NULL, NULL}
};
*/

static const luaL_Reg rawimg_methods[] = {
	{"get_pixel",rawimg_lua_get_pixel},
	{"set_pixel",rawimg_lua_set_pixel},
	{"width",rawimg_lua_get_width},
	{"height",rawimg_lua_get_height},
	{"bpp",rawimg_lua_get_bpp},
	{"endian",rawimg_lua_get_endian},
	{"cfa_pattern",rawimg_lua_get_cfa_pattern},
	{"make_rgb_thumb",rawimg_lua_make_rgb_thumb},
	{"patch_pixels",rawimg_lua_patch_pixels},
	{"convert",rawimg_lua_convert},
	{NULL, NULL}
};

void rawimg_open(lua_State *L) {
	luaL_newmetatable(L,RAWIMG_META);

	/* use a table of methods for the __index method */
//	luaL_register(L, NULL, rawimg_meta_methods);  
	lua_newtable(L);
	luaL_register(L, NULL, rawimg_methods);  
	lua_setfield(L,-2,"__index");
	lua_pop(L,1); // done with meta table
	
	// create a table to keep track of lbufs referenced by raw images
	lua_newtable(L);
	// metatable for above
	luaL_newmetatable(L, RAWIMG_LIST_META);
	lua_pushstring(L, "k");  /* mode values: weak keys, strong values */
	lua_setfield(L, -2, "__mode");  /* metatable.__mode */
	lua_setmetatable(L,-2);
	lua_setfield(L,LUA_REGISTRYINDEX,RAWIMG_LIST);
	lua_pop(L,1); // done with list table

	luaL_register(L, "rawimg", rawimg_lib);  
}
