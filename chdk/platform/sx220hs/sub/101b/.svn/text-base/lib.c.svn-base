#include "platform.h"

/*
SX220
full 19131120
0x1048 *  BF4   =  C29CA0
4168 * 3060 = 12754080 
*/

char *hook_raw_image_addr()
{

	if (*((int*)0x3F04) != 0)
		return (char*) 0x46000000;
	else
		return (char*) 0x413591F0;

}

char *hook_alt_raw_image_addr()
{

	if (*((int*)0x3F04) == 0)
		return (char*) 0x46000000;
	else
		return (char*) 0x413591F0;

}

long hook_raw_size()
{
	//FF375484 dword_FF375484  DCD 0x123EAF0
	return 0x123EAF0;
	
}

void *vid_get_viewport_fb_d()
{
	//FF06C580 dword_FF06C580  DCD 0x3C70
	//FF06D300                 STR     R12, [R5,#0x58
	return (void*)(*(int*)(0x3C70+0x58));                  

}

char *camera_jpeg_count_str()
{
	//FF2327FC(v100A)          LDR     R0, =0xCA790
	return (void*)0xCA790;                                      

}
