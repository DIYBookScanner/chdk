#include "stdio.h"
#include "../lib/font/font_8x16_uni.h"

//-------------------------------------------------------------------

int main(int argc, char **argv)
{
    int i, j, offset, size;
    
    printf("// This is a compressed version of font_8x16_uni.h produced by the tools/font_8x16_pack program\n\n");
    printf("// Format of each character is 'FontData' structure, followed by FontData.size bytes of character data.\n\n");
    printf("static unsigned char font_data[] = {\n");

    for (i=0; font_data[i].charcode != -1; i++)
    {
        offset = 0;
        size = 16;
        for (j=0; j<16 && font_data[i].data[j] == 0; j++) { offset++; size--; }
        for (j=15; j>offset && font_data[i].data[j] == 0; j--) { size--; }

        printf("0x%02x, 0x%02x, 0x%02x, 0x%02x,", font_data[i].charcode & 0xff, (font_data[i].charcode >> 8) & 0xFF, offset, size);
        for (j=0; j<size; j++) printf(" 0x%02x,",font_data[i].data[offset+j]&0xff);
        printf("\n");
    }

    printf("0xff, 0xff\n};\n");

    return 0;
}
