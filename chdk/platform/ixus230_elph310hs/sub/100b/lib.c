#include "platform.h"

/*
IXUS230HS / ELPH310HS
full 19131120
0x1048 *  BF4   =  C29CA0
4168 * 3060 = 12754080 
*/

char *hook_raw_image_addr()
{
	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at 0xFF3B9B74  used in sub_FF0DDBFC
	// [0x2EF8 + 0xC] --> defines which buffer is active

	if (*((int*)(0x2EF8 + 0xC)) != 0) //loc_FF078D38: 0x2EF8 (@FF078D3C) + 0xC (@FF078D68)
		return (char*) 0x46000000; 
	else
		return (char*) 0x413391A0;
}

char *hook_alt_raw_image_addr()
{
	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at 0xFF3B9B74  used in sub_FF0DDBFC
	// [0x2EF8 + 0xC] --> defines which buffer is active

	if (*((int*)(0x2EF8 + 0xC)) == 0) //loc_FF078D38: 0x2EF8 (@FF078D3C) + 0xC (@FF078D68)
		return (char*) 0x46000000; 
	else
		return (char*) 0x413391A0;
}

long hook_raw_size()
{
	//FF36849C
	return 0x0123eaf0;	
}

// OSD buffer
void *vid_get_bitmap_fb()
{	
	//FF053204
	return (void*)0x40471000;
}	                           

void *vid_get_viewport_fb_d()
{
	//FF06C234
	//FF06C26C
	return (void*)(*(int*)(0x2C58+0x58));                  
}

char *camera_jpeg_count_str()
{
	//FF226398
	return (void*)0x000B9574;                                      
}
