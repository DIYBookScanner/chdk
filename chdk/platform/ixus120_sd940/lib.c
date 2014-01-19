#include "platform.h"
#include "lolevel.h"

#define LED_GREEN  0xC0220130
#define LED_ORANGE 0xC0220134
#define LED_AF     0xC0223030

extern int enabled_refresh_physical_screen;

void vid_bitmap_refresh()
{
	enabled_refresh_physical_screen=1;
	
	*(int*)0x8BB0=3;	// apparently not firmware specific (checked in 1.02c,1.03b,1.03c)
						// set in three function called by RefreshPhysicalScreen

	_RefreshPhysicalScreen(1);

}


void shutdown()
{
	volatile long *p = (void*)LED_AF;

	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");

	*p = 0x44;  // power off.

	while(1);
}


void debug_led(int state)
{
 *(int*)LED_ORANGE=state ? 0x46 : 0x44;
}

// ixus120_sd940 has three LEDs - a dual LED green/orange on back panel and an AF led above lens

void camera_set_led(int led, int state, int bright) {
 static char led_table[3]={0,1,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 120;
}

void vid_turn_off_updates()
{
  _ScreenLock();
}

void vid_turn_on_updates()
{
  _RefreshPhysicalScreen(1);
}

// Functions for PTP Live View system
int vid_get_palette_type()                      { return 3 ; }          // 1,2,3,4,or 5
int vid_get_palette_size()                      { return 256 * 4 ; }    // 16*4 or 256*4

void *vid_get_bitmap_active_palette()
{
    extern int active_palette_buffer;
    extern char** palette_buffer_ptr;
    return palette_buffer_ptr[active_palette_buffer]+8;
}

void load_chdk_palette()
{
    int i ;
    extern char** palette_buffer_ptr;
    extern int active_palette_buffer;

    if ((active_palette_buffer == 0) || (active_palette_buffer == 5)|| (active_palette_buffer == 8))  // Note : palette 4 (Canon Set Button Menu) colors conflict so not included here
    {
        int *pal = (int*)vid_get_bitmap_active_palette();
        if (pal[CHDK_COLOR_BASE+0] != 0x33ADF62)
        {
            pal[CHDK_COLOR_BASE+0]  = 0x33ADF62;  // Red
            pal[CHDK_COLOR_BASE+1]  = 0x326EA40;  // Dark Red
            pal[CHDK_COLOR_BASE+2]  = 0x34CD57F;  // Light Red
            pal[CHDK_COLOR_BASE+3]  = 0x373BFAE;  // Green
            pal[CHDK_COLOR_BASE+4]  = 0x34BD6CA;  // Dark Green
            pal[CHDK_COLOR_BASE+5]  = 0x395AB95;  // Light Green
            pal[CHDK_COLOR_BASE+6]  = 0x34766F0;  // Blue
            pal[CHDK_COLOR_BASE+7]  = 0x31250F3;  // Dark Blue
            pal[CHDK_COLOR_BASE+8]  = 0x37F408F;  // Cyan
            pal[CHDK_COLOR_BASE+9]  = 0x3512D5B;  // Magenta
            pal[CHDK_COLOR_BASE+10] = 0x3A9A917;  // Yellow
            pal[CHDK_COLOR_BASE+11] = 0x3819137;  // Dark Yellow
            pal[CHDK_COLOR_BASE+12] = 0x3DED115;  // Light Yellow

            // extern char palette_control;
            // palette_control = 1;
            vid_bitmap_refresh();
        }
    }
}

