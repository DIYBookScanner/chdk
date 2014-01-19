#include "camera_info.h"
#include "stdlib.h"
#include "debug_led.h"
#include "sd_card.h"
#include "gui_mbox.h"
#include "raw.h"
#include "gui_lang.h"
#include "lang.h"
#include "conf.h"

#include "raw_merge.h"
#include "module_def.h"

#define TEMP_FILE_NAME   "A/raw16.tmp"
#define TEMP_FILE_NAME_1 "A/raw16_1.tmp"

static int running = 0;
static int raw_action;
static int raw_count;
static unsigned short *row;
static unsigned char *rawrow;
static char namebuf[100];

extern void reverse_bytes_order2(char* from, char* to, int count);

// note: if processing with dcraw etc, zeros may get replaced with interpolated values
// this may or may not be what you want
static int raw_subtract_values(int from, int sub)
{
    int result;
    if ((from==0) || (sub==0)) return 0; // bad pixel
    result = from - sub + camera_sensor.black_level;
    if (result < camera_sensor.black_level) result = camera_sensor.black_level;
    if (result > camera_sensor.white_level) result = camera_sensor.white_level;
    return result;
}

// subtract "sub" from "from"
int raw_subtract(const char *fromName, const char* fromDir, const char *subName, const char* subDir)
{
    char from[100];
    char sub[100];

    unsigned int req = (camera_sensor.raw_size >> 20) + 1;      // Raw size in MB
    unsigned int avail = GetFreeCardSpaceKb() >> 10;            // Free space in MB

    if (avail < req)
    {
        sprintf(namebuf,lang_str(LANG_AVERAGE_NO_CARD_SPACE),req,avail);
        gui_mbox_init((int)"RAW OP", (int)namebuf, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
        return 0;
    }

    int fromDNG = 0;
    int subDNG = 0;
    struct stat st;

    sprintf(from, "%s/%s", fromDir, fromName);
    if (stat(from,&st) != 0 || st.st_size < camera_sensor.raw_size)
    {
        // TODO: error popup
        return 0;
    }
    fromDNG = st.st_size - camera_sensor.raw_size;

    sprintf(sub, "%s/%s", subDir, subName);
    if (stat(sub,&st) != 0 || st.st_size < camera_sensor.raw_size)
    {
        // TODO: error popup
        return 0;
    }
    subDNG = st.st_size - camera_sensor.raw_size;

    sprintf(namebuf, "%s/%s%s", fromDir, img_prefixes[conf.sub_batch_prefix], fromName+4);
    strcpy(namebuf + strlen(namebuf) - 4, (fromDNG && conf.raw_dng_ext) ? ".DNG" : img_exts[conf.sub_batch_ext]);

    FILE *ffrom = fopen(from, "rb");
    FILE *fsub = fopen(sub, "rb");
    FILE *fdest = fopen(namebuf, "wb");

    unsigned char *bacc = malloc(camera_sensor.raw_rowlen);
    unsigned char *bsub = malloc(camera_sensor.raw_rowlen);

    int status = 0;
    unsigned short s,d;
    int i,j;

    running = 1;

    if (bacc && bsub && ffrom && fsub && fdest)
    {
        started();

        if (fromDNG)
        {
            // Copy DNG header to output file
            int len = fromDNG;
            while (len > 0)
            {
                int l = len;
                if (l > camera_sensor.raw_rowlen) l = camera_sensor.raw_rowlen;
                fread(bacc, 1, l, ffrom);
                fwrite(bacc, 1, l, fdest);
                len -= l;
            }
            fseek(ffrom, fromDNG, SEEK_SET);
        }
        if (subDNG)
        {
            fseek(fsub, subDNG, SEEK_SET);
        }

        for (j = 0; j < camera_sensor.raw_rows; j++)
        {
            fread(bacc, 1, camera_sensor.raw_rowlen, ffrom);
            if (fromDNG) reverse_bytes_order2((char*)bacc, (char*)bacc, camera_sensor.raw_rowlen);
            fread(bsub, 1, camera_sensor.raw_rowlen, fsub);
            if (subDNG) reverse_bytes_order2((char*)bsub, (char*)bsub, camera_sensor.raw_rowlen);

            if (camera_sensor.bits_per_pixel == 10)
            {
                for (i=0; i<camera_sensor.raw_rowlen; i+=10)
                {
                    s = ((0x3fc&(((unsigned short)bsub[i+1])<<2)) | (bsub[i+0] >> 6));
                    d = ((0x3fc&(((unsigned short)bacc[i+1])<<2)) | (bacc[i+0] >> 6));
                    d = raw_subtract_values(d,s);
                    bacc[i+0] = (bacc[i+0]&0x3F)|(d<<6); 
                    bacc[i+1] = d>>2;

                    s = ((0x3f0&(((unsigned short)bsub[i+0])<<4)) | (bsub[i+3] >> 4));
                    d = ((0x3f0&(((unsigned short)bacc[i+0])<<4)) | (bacc[i+3] >> 4));
                    d = raw_subtract_values(d,s);
                    bacc[i+0] = (bacc[i+0]&0xC0)|(d>>4);
                    bacc[i+3] = (bacc[i+3]&0x0F)|(d<<4);

                    s = ((0x3c0&(((unsigned short)bsub[i+3])<<6)) | (bsub[i+2] >> 2));
                    d = ((0x3c0&(((unsigned short)bacc[i+3])<<6)) | (bacc[i+2] >> 2));
                    d = raw_subtract_values(d,s);
                    bacc[i+2] = (bacc[i+2]&0x03)|(d<<2);
                    bacc[i+3] = (bacc[i+3]&0xF0)|(d>>6);

                    s = ((0x300&(((unsigned short)bsub[i+2])<<8)) | (bsub[i+5])); 
                    d = ((0x300&(((unsigned short)bacc[i+2])<<8)) | (bacc[i+5])); 
                    d = raw_subtract_values(d,s);
                    bacc[i+2] = (bacc[i+2]&0xFC)|(d>>8); 
                    bacc[i+5] = d;

                    s = ((0x3fc&(((unsigned short)bsub[i+4])<<2)) | (bsub[i+7] >> 6)); 
                    d = ((0x3fc&(((unsigned short)bacc[i+4])<<2)) | (bacc[i+7] >> 6)); 
                    d = raw_subtract_values(d,s);
                    bacc[i+4] = d>>2;
                    bacc[i+7] = (bacc[i+7]&0x3F)|(d<<6);

                    s = ((0x3f0&(((unsigned short)bsub[i+7])<<4)) | (bsub[i+6] >> 4)); 
                    d = ((0x3f0&(((unsigned short)bacc[i+7])<<4)) | (bacc[i+6] >> 4)); 
                    d = raw_subtract_values(d,s);
                    bacc[i+6] = (bacc[i+6]&0x0F)|(d<<4);
                    bacc[i+7] = (bacc[i+7]&0xC0)|(d>>4);

                    s = ((0x3c0&(((unsigned short)bsub[i+6])<<6)) | (bsub[i+9] >> 2)); 
                    d = ((0x3c0&(((unsigned short)bacc[i+6])<<6)) | (bacc[i+9] >> 2)); 
                    d = raw_subtract_values(d,s);
                    bacc[i+6] = (bacc[i+6]&0xF0)|(d>>6);
                    bacc[i+9] = (bacc[i+9]&0x03)|(d<<2);

                    s = ((0x300&(((unsigned short)bsub[i+9])<<8)) | (bsub[i+8])); 
                    d = ((0x300&(((unsigned short)bacc[i+9])<<8)) | (bacc[i+8])); 
                    d = raw_subtract_values(d,s);
                    bacc[i+8] = d;
                    bacc[i+9] = (bacc[i+9]&0xFC)|(d>>8);
                }
            }
            else if (camera_sensor.bits_per_pixel == 12)
            {
                for (i=0; i<camera_sensor.raw_rowlen; i+=6)
                {
                    s = ((0xFF0&(((unsigned short)bsub[i+1])<<4)) | (bsub[i+0] >> 4));
                    d = ((0xFF0&(((unsigned short)bacc[i+1])<<4)) | (bacc[i+0] >> 4));
                    d = raw_subtract_values(d,s);
                    bacc[i+0] = (bacc[i+0]&0x0F)|(d<<4);
                    bacc[i+1] = d>>4;

                    s = ((0xF00&(((unsigned short)bsub[i+0])<<8)) | (bsub[i+3]     ));
                    d = ((0xF00&(((unsigned short)bacc[i+0])<<8)) | (bacc[i+3]   ));
                    d = raw_subtract_values(d,s);
                    bacc[i+0] = (bacc[i+0]&0xF0)|(d>>8);
                    bacc[i+3] = d;

                    s = ((0xFF0&(((unsigned short)bsub[i+2])<<4)) | (bsub[i+5] >> 4));
                    d = ((0xFF0&(((unsigned short)bacc[i+2])<<4)) | (bacc[i+5] >> 4));
                    d = raw_subtract_values(d,s);
                    bacc[i+2] = d>>4;
                    bacc[i+5] = (bacc[i+5]&0x0F)|(d<<4);

                    s = ((0xF00&(((unsigned short)bsub[i+5])<<8)) | (bsub[i+4]     ));
                    d = ((0xF00&(((unsigned short)bacc[i+5])<<8)) | (bacc[i+4]     ));
                    d = raw_subtract_values(d,s);
                    bacc[i+4] = d;
                    bacc[i+5] = (bacc[i+5]&0xF0)|(d>>8);
                }
            }
            else if (camera_sensor.bits_per_pixel == 14)
            {
                for (i=0; i<camera_sensor.raw_rowlen; i+=14)
                {
                    s = ((unsigned short)(bsub[i+ 1])        <<  6) | (bsub[i+ 0] >> 2);
                    d = ((unsigned short)(bacc[i+ 1])        <<  6) | (bacc[i+ 0] >> 2);
                    d = raw_subtract_values(d,s);
                    bacc[i+ 0] = (bacc[i+ 0]&0x03)|(d<< 2);
                    bacc[i+ 1] = d>>6;

                    s = ((unsigned short)(bsub[i+ 0] & 0x03) << 12) | ((unsigned short)(bsub[i+ 3]) << 4) | (bsub[i+ 2] >> 4);
                    d = ((unsigned short)(bacc[i+ 0] & 0x03) << 12) | ((unsigned short)(bacc[i+ 3]) << 4) | (bacc[i+ 2] >> 4);
                    d = raw_subtract_values(d,s);
                    bacc[i+ 0] = (bacc[i+ 0]&0xFC)|(d>>12);
                    bacc[i+ 2] = (bacc[i+ 2]&0x0F)|(d<< 4);
                    bacc[i+ 3] = d>>4;

                    s = ((unsigned short)(bsub[i+ 2] & 0x0F) << 10) | ((unsigned short)(bsub[i+ 5]) << 2) | (bsub[i+ 4] >> 6);
                    d = ((unsigned short)(bacc[i+ 2] & 0x0F) << 10) | ((unsigned short)(bacc[i+ 5]) << 2) | (bacc[i+ 4] >> 6);
                    d = raw_subtract_values(d,s);
                    bacc[i+ 2] = (bacc[i+ 2]&0xF0)|(d>>10);
                    bacc[i+ 4] = (bacc[i+ 4]&0x3F)|(d<< 6);
                    bacc[i+ 5] = d>>2;

                    s = ((unsigned short)(bsub[i+ 4] & 0x3F) <<  8) | (bsub[i+ 7]);
                    d = ((unsigned short)(bacc[i+ 4] & 0x3F) <<  8) | (bacc[i+ 7]);
                    d = raw_subtract_values(d,s);
                    bacc[i+ 4] = (bacc[i+ 4]&0xC0)|(d>> 8);
                    bacc[i+ 7] = d;

                    s = ((unsigned short)(bsub[i+ 6])        <<  6) | (bsub[i+ 9] >> 2);
                    d = ((unsigned short)(bacc[i+ 6])        <<  6) | (bacc[i+ 9] >> 2);
                    d = raw_subtract_values(d,s);
                    bacc[i+ 6] = d>>6;
                    bacc[i+ 9] = (bacc[i+ 9]&0x03)|(d<< 2);

                    s = ((unsigned short)(bsub[i+ 9] & 0x03) << 12) | ((unsigned short)(bsub[i+ 8]) << 4) | (bsub[i+11] >> 4);
                    d = ((unsigned short)(bacc[i+ 9] & 0x03) << 12) | ((unsigned short)(bacc[i+ 8]) << 4) | (bacc[i+11] >> 4);
                    d = raw_subtract_values(d,s);
                    bacc[i+ 8] = d>>4;
                    bacc[i+ 9] = (bacc[i+ 9]&0xFC)|(d>>12);
                    bacc[i+11] = (bacc[i+11]&0x0F)|(d<< 4);

                    s = ((unsigned short)(bsub[i+11] & 0x0F) << 10) | ((unsigned short)(bsub[i+10]) << 2) | (bsub[i+13] >> 6);
                    d = ((unsigned short)(bacc[i+11] & 0x0F) << 10) | ((unsigned short)(bacc[i+10]) << 2) | (bacc[i+13] >> 6);
                    d = raw_subtract_values(d,s);
                    bacc[i+10] = d>>2;
                    bacc[i+11] = (bacc[i+11]&0xF0)|(d>>10);
                    bacc[i+13] = (bacc[i+13]&0x3F)|(d<< 6);

                    s = ((unsigned short)(bsub[i+13] & 0x3F) <<  8) | (bsub[i+12]);
                    d = ((unsigned short)(bacc[i+13] & 0x3F) <<  8) | (bacc[i+12]);
                    d = raw_subtract_values(d,s);
                    bacc[i+12] = d;
                    bacc[i+13] = (bacc[i+13]&0xC0)|(d>> 8);
                }
            }

            if (fromDNG) reverse_bytes_order2((char*)bacc, (char*)bacc, camera_sensor.raw_rowlen);
            fwrite(bacc, 1, camera_sensor.raw_rowlen, fdest);
            if ((j & 0x1F) == 0)
                gui_browser_progress_show(namebuf, j*100/camera_sensor.raw_rows);
        }
        gui_browser_progress_show(namebuf, 100);
        finished();
        status = 1;
    }

    if (bacc)   free(bacc);
    if (bsub)   free(bsub);
    if (ffrom)  fclose(ffrom);
    if (fsub)   fclose(fsub);
    if (fdest)  
    {
        fclose(fdest);
        struct utimbuf t;
        t.actime = t.modtime = time(NULL);
        utime(namebuf, &t);
    }

    running = 0;
    return status;
}

int raw_merge_start(int action)
{
    unsigned int req = (camera_sensor.raw_size >> 18) + 1;      // Raw size * 4 in MB
    unsigned int avail = GetFreeCardSpaceKb() >> 10;            // Free space in MB
    if (avail < req)
    {
        sprintf(namebuf,lang_str(LANG_AVERAGE_NO_CARD_SPACE),req,avail);
        gui_mbox_init((int)"RAW OP", (int)namebuf, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
        return 0;
    }

    raw_action = action;
    raw_count = 0;
    row = malloc(camera_sensor.raw_rowpix*sizeof(unsigned short));
    if (!row)
        return 0;
    rawrow = malloc(camera_sensor.raw_rowlen);
    if (!rawrow)
    {
        free(row);
        return 0;
    }
    running = 1;
    return 1;
}

int raw_merge_add_file(const char * filename)
{
    int  src,i,j;
    FILE *fbrawin=NULL,*fbrawout,*fcraw;
    struct stat st;

    if (!filename)
    {
        // TODO: error popup?
        return 0;
    }

    if (stat(filename,&st) != 0 || st.st_size < camera_sensor.raw_size)
    {
        // TODO: error popup
        return 0;
    }
    int fcrawDNG = st.st_size - camera_sensor.raw_size;

    started();

    fcraw = fopen(filename,"rb");
    if (fcraw)
    {
        if (raw_count)
            fbrawin = fopen(TEMP_FILE_NAME,"rb");

        if (!raw_count || fbrawin)
        {
            fbrawout = fopen(TEMP_FILE_NAME_1,"wb");
            if (fbrawout)
            {
                if (fcrawDNG)
                    fseek(fcraw, fcrawDNG, SEEK_SET);

                for (j=0; j<camera_sensor.raw_rows; j++)
                {
                    if (raw_count)
                        fread(row, 1, camera_sensor.raw_rowpix*sizeof(unsigned short), fbrawin);
                    else
                        memset(row, 0, camera_sensor.raw_rowpix*sizeof(unsigned short));

                    fread(rawrow, 1, camera_sensor.raw_rowlen, fcraw);
                    if (fcrawDNG) reverse_bytes_order2((char*)rawrow, (char*)rawrow, camera_sensor.raw_rowlen);

                    if (camera_sensor.bits_per_pixel == 10)
                    {
                        for (i=0, src=0; i<camera_sensor.raw_rowpix; i+=8, src+=10)
                        {
                            row[i+0] += ((0x3fc&(((unsigned short)rawrow[src+1])<<2)) | (rawrow[src+0] >> 6));
                            row[i+1] += ((0x3f0&(((unsigned short)rawrow[src+0])<<4)) | (rawrow[src+3] >> 4));
                            row[i+2] += ((0x3c0&(((unsigned short)rawrow[src+3])<<6)) | (rawrow[src+2] >> 2));
                            row[i+3] += ((0x300&(((unsigned short)rawrow[src+2])<<8)) | (rawrow[src+5])); 
                            row[i+4] += ((0x3fc&(((unsigned short)rawrow[src+4])<<2)) | (rawrow[src+7] >> 6)); 
                            row[i+5] += ((0x3f0&(((unsigned short)rawrow[src+7])<<4)) | (rawrow[src+6] >> 4)); 
                            row[i+6] += ((0x3c0&(((unsigned short)rawrow[src+6])<<6)) | (rawrow[src+9] >> 2)); 
                            row[i+7] += ((0x300&(((unsigned short)rawrow[src+9])<<8)) | (rawrow[src+8])); 
                        }
                    }
                    else if (camera_sensor.bits_per_pixel == 12)
                    {
                        for (i=0, src=0; i<camera_sensor.raw_rowpix; i+=4, src+=6)
                        {
                            row[i+0] += ((0xFF0&(((unsigned short)rawrow[src+1])<<4)) | (rawrow[src+0] >> 4));
                            row[i+1] += ((0xF00&(((unsigned short)rawrow[src+0])<<8)) | (rawrow[src+3]     ));
                            row[i+2] += ((0xFF0&(((unsigned short)rawrow[src+2])<<4)) | (rawrow[src+5] >> 4));
                            row[i+3] += ((0xF00&(((unsigned short)rawrow[src+5])<<8)) | (rawrow[src+4]     ));
                        }
                    }
                    else if (camera_sensor.bits_per_pixel == 14)
                    {
                        for (i=0, src=0; i<camera_sensor.raw_rowpix; i+=8, src+=14)
                        {
                            row[i+0] += ((unsigned short)(rawrow[src+ 1])        <<  6) | (rawrow[src+ 0] >> 2);
                            row[i+1] += ((unsigned short)(rawrow[src+ 0] & 0x03) << 12) | (rawrow[src+ 3] << 4) | (rawrow[src+ 2] >> 4);
                            row[i+2] += ((unsigned short)(rawrow[src+ 2] & 0x0F) << 10) | (rawrow[src+ 5] << 2) | (rawrow[src+ 4] >> 6);
                            row[i+3] += ((unsigned short)(rawrow[src+ 4] & 0x3F) <<  8) | (rawrow[src+ 7]);
                            row[i+4] += ((unsigned short)(rawrow[src+ 6])        <<  6) | (rawrow[src+ 9] >> 2);
                            row[i+5] += ((unsigned short)(rawrow[src+ 9] & 0x03) << 12) | (rawrow[src+ 8] << 4) | (rawrow[src+11] >> 4);
                            row[i+6] += ((unsigned short)(rawrow[src+11] & 0x0F) << 10) | (rawrow[src+10] << 2) | (rawrow[src+13] >> 6);
                            row[i+7] += ((unsigned short)(rawrow[src+13] & 0x3F) <<  8) | (rawrow[src+12]);
                        }
                    }

                    fwrite(row, 1, camera_sensor.raw_rowpix*sizeof(unsigned short), fbrawout);
                    if ((j & 0x1F) == 0)
                        gui_browser_progress_show(filename, j*100/camera_sensor.raw_rows);
                }
                raw_count++;
                strcpy(namebuf,filename);
                fclose(fbrawout);
            }
            if (fbrawin)
                fclose(fbrawin);
        }
        fclose(fcraw);
    }

    remove(TEMP_FILE_NAME);
    rename(TEMP_FILE_NAME_1,TEMP_FILE_NAME);

    finished();
    return 1;
}

void raw_merge_end(void)
{
    int src,i,j;
    FILE *fbraw, *fcraw, *fdng = 0;
    char dest[100];

    if (!raw_count)
    {
        free(rawrow);
        free(row);
        return;
    } 

    struct stat st;
    if (stat(namebuf,&st) != 0 || st.st_size < camera_sensor.raw_size)
    {
        // TODO: error popup
        return;
    }
    int destDNG = st.st_size - camera_sensor.raw_size;

    if (destDNG)
        fdng = fopen(namebuf,"rb");

    strcpy(dest, namebuf);
    char *n = strrchr(dest, '/');
    if (n == 0) n = dest;
    else n++;

    strncpy(n, img_prefixes[conf.sub_batch_prefix], 4);
    strcpy(dest + strlen(dest) - 4, (destDNG && conf.raw_dng_ext) ? ".DNG" : img_exts[conf.sub_batch_ext]);

    // Check if overwriting input file
    if (strcmp(namebuf, dest) == 0)
    {
        if (strncmp(n, "IMG", 3) == 0)
            strncpy(n, "CRW", 3);
        else
            strncpy(n, "IMG", 3);
    }

    started();

    fbraw = fopen(TEMP_FILE_NAME,"rb");
    if (fbraw)
    {
        fcraw = fopen(dest,"wb");
        if (fcraw)
        {
            if (destDNG)
            {
                // Copy DNG header to output file
                int len = destDNG;
                while (len > 0)
                {
                    int l = len;
                    if (l > camera_sensor.raw_rowlen) l = camera_sensor.raw_rowlen;
                    fread(rawrow, 1, l, fdng);
                    fwrite(rawrow, 1, l, fcraw);
                    len -= l;
                }
            }

            for (j=0; j<camera_sensor.raw_rows; j++)
            {
                fread(row, 1, camera_sensor.raw_rowpix*sizeof(unsigned short), fbraw);

                if (raw_count > 1)
                {
                    for (i=0; i<camera_sensor.raw_rowpix; i++)
                    {
                        if (raw_action == RAW_OPERATION_AVERAGE)
                            row[i] /= raw_count;
                        else
                        {
                            if (row[i] > camera_sensor.black_level*(raw_count-1))
                                row[i] -= camera_sensor.black_level*(raw_count-1);
                            else
                                row[i] = 0;
                            if (row[i] > camera_sensor.white_level)
                                row[i] = camera_sensor.white_level;
                        }
                    }  
                }
                if (camera_sensor.bits_per_pixel == 10)
                {
                    for (i=0,src=0; i<camera_sensor.raw_rowpix; i+=8, src+=10)
                    {
                        rawrow[src+0] = (row[i+0]<<6)|(row[i+1]>>4);
                        rawrow[src+1] = (row[i+0]>>2);
                        rawrow[src+2] = (row[i+2]<<2)|(row[i+3]>>8);
                        rawrow[src+3] = (row[i+1]<<4)|(row[i+2]>>6);
                        rawrow[src+4] = (row[i+4]>>2);
                        rawrow[src+5] = (row[i+3]);
                        rawrow[src+6] = (row[i+5]<<4)|(row[i+6]>>6);
                        rawrow[src+7] = (row[i+4]<<6)|(row[i+5]>>4);
                        rawrow[src+8] = (row[i+7]);
                        rawrow[src+9] = (row[i+6]<<2)|(row[i+7]>>8);
                    }
                }
                else if (camera_sensor.bits_per_pixel == 12)
                {
                    for (i=0,src=0; i<camera_sensor.raw_rowpix; i+=4, src+=6)
                    {
                        rawrow[src+0] = (row[i+0]<<4)|(row[i+1]>>8);
                        rawrow[src+1] = (row[i+0]>>4);
                        rawrow[src+2] = (row[i+2]>>4);
                        rawrow[src+3] = (row[i+1]);
                        rawrow[src+4] = (row[i+3]);
                        rawrow[src+5] = (row[i+2]<<4)|(row[i+3]>>8);
                    }
                }
                else if (camera_sensor.bits_per_pixel == 14)
                {
                    for (i=0,src=0; i<camera_sensor.raw_rowpix; i+=8, src+=14)
                    {
                        rawrow[src+ 0] = (row[i+0]<<2)|(row[i+1]>>12);
                        rawrow[src+ 1] = (row[i+0]>>6);
                        rawrow[src+ 2] = (row[i+1]<<4)|(row[i+2]>>10);
                        rawrow[src+ 3] = (row[i+1]>>4);
                        rawrow[src+ 4] = (row[i+2]<<6)|(row[i+3]>>8);
                        rawrow[src+ 5] = (row[i+2]>>2);
                        rawrow[src+ 6] = (row[i+4]>>6);
                        rawrow[src+ 7] = (row[i+3]);
                        rawrow[src+ 8] = (row[i+5]>>4);
                        rawrow[src+ 9] = (row[i+4]<<2)|(row[i+5]>>12);
                        rawrow[src+10] = (row[i+6]>>2);
                        rawrow[src+11] = (row[i+5]<<4)|(row[i+6]>>10);
                        rawrow[src+12] = (row[i+7]);
                        rawrow[src+13] = (row[i+6]<<6)|(row[i+7]>>8);
                    }
                }

                if (destDNG) reverse_bytes_order2((char*)rawrow, (char*)rawrow, camera_sensor.raw_rowlen);
                fwrite(rawrow, 1, camera_sensor.raw_rowlen, fcraw);
                if ((j & 0x1F) == 0)
                    gui_browser_progress_show(dest, j*100/camera_sensor.raw_rows);
            }
            fclose(fcraw);
        }
        fclose(fbraw);
    }

    if (fdng) fclose(fdng);

    struct utimbuf t;
    t.actime = t.modtime = time(NULL);
    utime(namebuf, &t);
    remove(TEMP_FILE_NAME);

    finished();
    free(rawrow);
    free(row);

    running = 0;
}


// =========  MODULE INIT =================

/***************** BEGIN OF AUXILARY PART *********************
  ATTENTION: DO NOT REMOVE OR CHANGE SIGNATURES IN THIS SECTION
 **************************************************************/

int _module_can_unload()
{
    return running == 0;
}

/******************** Module Information structure ******************/

librawop_sym _librawop = 
{
    {
        0, 0, _module_can_unload, 0, 0
    },

    raw_merge_start,
    raw_merge_add_file,
    raw_merge_end,
    raw_subtract
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    RAW_MERGE_VERSION,			// Module version

    ANY_CHDK_BRANCH, 0,			// Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,		// Specify platform dependency

    (int32_t)"RAW operations (dll)",// Module name
    (int32_t)"Implementation of RAW operations\n(Avg, Sum, Sub)",

    &_librawop.base,

    ANY_VERSION,                // CONF version
    ANY_VERSION,                // CAM SCREEN version
    CAM_SENSOR_VERSION,         // CAM SENSOR version
    ANY_VERSION,                // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
