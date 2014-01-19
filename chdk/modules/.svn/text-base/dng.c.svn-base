#include "camera_info.h"
#include "modes.h"
#include "debug_led.h"
#include "clock.h"
#include "properties.h"
#include "shooting.h"
#include "conf.h"
#include "console.h"
#include "raw.h"
#include "action_stack.h"
#include "gui.h"
#include "gui_mbox.h"
#include "gui_lang.h"
#include "gps.h"
#include "math.h"
#include "cache.h"
#include "task.h"
#include "cachebit.h"
#include "remotecap.h"

#include "dng.h"
#include "module_def.h"

// Set to 1 when module loaded and active
static int running = 0;

//thumbnail
#define DNG_TH_WIDTH 128
#define DNG_TH_HEIGHT 96
#define DNG_TH_BYTES (DNG_TH_WIDTH*DNG_TH_HEIGHT*3)
// higly recommended that DNG_TH_WIDTH*DNG_TH_HEIGHT would be divisible by 512

// new version to support DNG double buffer
void reverse_bytes_order2(char* from, char* to, int count);
// convert old version calls to new version (to minimise code changes)
#define reverse_bytes_order(start, count)   reverse_bytes_order2(start,start,count)

struct dir_entry{unsigned short tag; unsigned short type; unsigned int count; unsigned int offset;};

#define T_BYTE      1
#define T_ASCII     2
#define T_SHORT     3
#define T_LONG      4
#define T_RATIONAL  5
#define T_SBYTE     6
#define T_UNDEFINED 7
#define T_SSHORT    8
#define T_SLONG     9
#define T_SRATIONAL 10
#define T_FLOAT     11
#define T_DOUBLE    12
#define T_PTR       0x100   // Stored as long/short etc in DNG header, referenced by pointer in IFD (must be pointer to int variable)
#define T_SKIP      0x200   // Tag value to be skipped (for marking GPS entries if camera does not have GPS)

unsigned short get_exp_program_for_exif(int exp_program);
unsigned short get_orientation_for_exif(short orientation);
unsigned short get_flash_mode_for_exif(short mode, short fired);
unsigned short get_metering_mode_for_exif(short metering_mode);

const int cam_BaselineNoise[]           = {1,1};
const int cam_BaselineSharpness[]       = {4,3};
const int cam_LinearResponseLimit[]     = {1,1};
const int cam_AnalogBalance[]           = {1,1,1,1,1,1};
static char cam_name[32]                = "";
static char artist_name[64]             = "";
static char copyright[64]               = "";
const short cam_PreviewBitsPerSample[]  = {8,8,8};
const int cam_Resolution[]              = {180,1};
static int cam_AsShotNeutral[]          = {1000,1000,1000,1000,1000,1000};
static char cam_datetime[20]            = "";                   // DateTimeOriginal
static char cam_subsectime[4]           = "";                   // DateTimeOriginal (milliseconds component)
static int cam_shutter[2]               = { 0, 1000000 };       // Shutter speed
static int cam_aperture[2]              = { 0, 10 };            // Aperture
static int cam_apex_shutter[2]          = { 0, 96 };            // Shutter speed in APEX units
static int cam_apex_aperture[2]         = { 0, 96 };            // Aperture in APEX units
static int cam_exp_bias[2]              = { 0, 96 };
static int cam_max_av[2]                = { 0, 96 };
static int cam_focal_length[2]          = { 0, 1000 };

struct t_data_for_exif{
    short iso;
    int exp_program;
    int effective_focal_length;
    short orientation;
    short flash_mode;
    short flash_fired;
    short metering_mode;
};

static struct t_data_for_exif exif_data;

#define BE(v)   ((v&0x000000FF)<<24)|((v&0x0000FF00)<<8)|((v&0x00FF0000)>>8)|((v&0xFF000000)>>24)   // Convert to big_endian

#define BADPIX_CFA_INDEX    6   // Index of CFAPattern value in badpixel_opcodes array

static unsigned int badpixel_opcode[] =
{
    // *** all values must be in big endian order

    BE(1),              // Count = 1

    BE(4),              // FixBadPixelsConstant = 4
    BE(0x01030000),     // DNG version = 1.3.0.0
    BE(1),              // Flags = 1
    BE(8),              // Opcode length = 8 bytes
    BE(0),              // Constant = 0
    BE(0),              // CFAPattern (set in code below)
};

// warning: according to TIFF format specification, elements must be sorted by tag value in ascending order!

// Index of specific entries in ifd0 below.
// *** warning - if entries are added or removed these should be updated ***
#define CAMERA_NAME_INDEX           8       // tag 0x110
#define THUMB_DATA_INDEX            9       // tag 0x111
#define ORIENTATION_INDEX           10      // tag 0x112
#define CHDK_VER_INDEX              15      // tag 0x131
#define ARTIST_NAME_INDEX           17      // tag 0x13B
#define SUBIFDS_INDEX               18      // tag 0x14A
#define COPYRIGHT_INDEX             19      // tag 0x8298
#define EXIF_IFD_INDEX              20      // tag 0x8769
#define GPS_IFD_INDEX               21      // tag 0x8825
#define DNG_VERSION_INDEX           23      // tag 0xC612
#define UNIQUE_CAMERA_MODEL_INDEX   25      // tag 0xC614
#define COLOR_MATRIX2_INDEX         27      // tag 0xc622
#define CALIBRATION1_INDEX          28      // tag 0xc623
#define CALIBRATION2_INDEX          29      // tag 0xc624
#define ILLUMINANT2_INDEX           38      // tag 0xc65b
#define FORWARD_MATRIX1_INDEX       39      // tag 0xc714
#define FORWARD_MATRIX2_INDEX       40      // tag 0xc715

#define CAM_MAKE                    "Canon"

struct dir_entry ifd0[]={
    {0xFE,   T_LONG,       1,  1},                                 // NewSubFileType: Preview Image
    {0x100,  T_LONG,       1,  DNG_TH_WIDTH},                      // ImageWidth
    {0x101,  T_LONG,       1,  DNG_TH_HEIGHT},                     // ImageLength
    {0x102,  T_SHORT,      3,  (int)cam_PreviewBitsPerSample},     // BitsPerSample: 8,8,8
    {0x103,  T_SHORT,      1,  1},                                 // Compression: Uncompressed
    {0x106,  T_SHORT,      1,  2},                                 // PhotometricInterpretation: RGB
    {0x10E,  T_ASCII,      1,  0},                                 // ImageDescription
    {0x10F,  T_ASCII,      sizeof(CAM_MAKE), (int)CAM_MAKE},       // Make
    {0x110,  T_ASCII,      32, (int)cam_name},                     // Model: Filled at header generation.
    {0x111,  T_LONG,       1,  0},                                 // StripOffsets: Offset
    {0x112,  T_SHORT,      1,  1},                                 // Orientation: 1 - 0th row is top, 0th column is left
    {0x115,  T_SHORT,      1,  3},                                 // SamplesPerPixel: 3
    {0x116,  T_SHORT,      1,  DNG_TH_HEIGHT},                     // RowsPerStrip
    {0x117,  T_LONG,       1,  DNG_TH_BYTES},                      // StripByteCounts = preview size
    {0x11C,  T_SHORT,      1,  1},                                 // PlanarConfiguration: 1
    {0x131,  T_ASCII|T_PTR,32, 0},                                 // Software
    {0x132,  T_ASCII,      20, (int)cam_datetime},                 // DateTime
    {0x13B,  T_ASCII|T_PTR,64, (int)artist_name},                  // Artist: Filled at header generation.
    {0x14A,  T_LONG,       1,  0},                                 // SubIFDs offset
    {0x8298, T_ASCII|T_PTR,64, (int)copyright},                    // Copyright
    {0x8769, T_LONG,       1,  0},                                 // EXIF_IFD offset
    {0x8825, T_LONG,       1,  0},                                 // GPS_IFD offset
    {0x9216, T_BYTE,       4,  0x00000001},                        // TIFF/EPStandardID: 1.0.0.0
    {0xC612, T_BYTE,       4,  0x00000301},                        // DNGVersion: 1.3.0.0
    {0xC613, T_BYTE,       4,  0x00000101},                        // DNGBackwardVersion: 1.1.0.0
    {0xC614, T_ASCII,      32, (int)cam_name},                     // UniqueCameraModel. Filled at header generation.
    {0xC621, T_SRATIONAL,  9,  (int)&camera_sensor.color_matrix1},
    {0xC622, T_SRATIONAL,  9,  (int)&camera_sensor.color_matrix2},
    {0xC623, T_SRATIONAL,  9,  (int)&camera_sensor.camera_calibration1},
    {0xC624, T_SRATIONAL,  9,  (int)&camera_sensor.camera_calibration2},
    {0xC627, T_RATIONAL,   3,  (int)cam_AnalogBalance},
    {0xC628, T_RATIONAL,   3,  (int)cam_AsShotNeutral},
    {0xC62A, T_SRATIONAL,  1,  (int)&camera_sensor.exposure_bias},
    {0xC62B, T_RATIONAL,   1,  (int)cam_BaselineNoise},
    {0xC62C, T_RATIONAL,   1,  (int)cam_BaselineSharpness},
    {0xC62E, T_RATIONAL,   1,  (int)cam_LinearResponseLimit},
    {0xC630, T_RATIONAL,   4,  (int)&camera_sensor.lens_info},
    {0xC65A, T_SHORT|T_PTR,1,  (int)&camera_sensor.calibration_illuminant1}, 
    {0xC65B, T_SHORT|T_PTR,1,  (int)&camera_sensor.calibration_illuminant2}, 
    {0xC714, T_SRATIONAL,  9,  (int)&camera_sensor.forward_matrix1},
    {0xC715, T_SRATIONAL,  9,  (int)&camera_sensor.forward_matrix2},
};

// Index of specific entries in ifd1 below.
// *** warning - if entries are added or removed these should be updated ***
#define RAW_DATA_INDEX              6       // tag 0x111
#define BADPIXEL_OPCODE_INDEX       21      // tag 0xC740

struct dir_entry ifd1[]={
    {0xFE,   T_LONG,       1,  0},                                 // NewSubFileType: Main Image
    {0x100,  T_LONG|T_PTR, 1,  (int)&camera_sensor.raw_rowpix},    // ImageWidth
    {0x101,  T_LONG|T_PTR, 1,  (int)&camera_sensor.raw_rows},      // ImageLength
    {0x102,  T_SHORT|T_PTR,1,  (int)&camera_sensor.bits_per_pixel},// BitsPerSample
    {0x103,  T_SHORT,      1,  1},                                 // Compression: Uncompressed
    {0x106,  T_SHORT,      1,  0x8023},                            // PhotometricInterpretation: CFA
    {0x111,  T_LONG,       1,  0},                                 // StripOffsets: Offset
    {0x115,  T_SHORT,      1,  1},                                 // SamplesPerPixel: 1
    {0x116,  T_SHORT|T_PTR,1,  (int)&camera_sensor.raw_rows},      // RowsPerStrip
    {0x117,  T_LONG|T_PTR, 1,  (int)&camera_sensor.raw_size},      // StripByteCounts = CHDK RAW size
    {0x11A,  T_RATIONAL,   1,  (int)cam_Resolution},               // XResolution
    {0x11B,  T_RATIONAL,   1,  (int)cam_Resolution},               // YResolution
    {0x11C,  T_SHORT,      1,  1},                                 // PlanarConfiguration: 1
    {0x128,  T_SHORT,      1,  2},                                 // ResolutionUnit: inch
    {0x828D, T_SHORT,      2,  0x00020002},                        // CFARepeatPatternDim: Rows = 2, Cols = 2
    {0x828E, T_BYTE|T_PTR, 4,  (int)&camera_sensor.cfa_pattern},
    {0xC61A, T_LONG|T_PTR, 1,  (int)&camera_sensor.black_level},   // BlackLevel
    {0xC61D, T_LONG|T_PTR, 1,  (int)&camera_sensor.white_level},   // WhiteLevel
    {0xC61F, T_LONG,       2,  (int)&camera_sensor.crop.origin},
    {0xC620, T_LONG,       2,  (int)&camera_sensor.crop.size},
    {0xC68D, T_LONG,       4,  (int)&camera_sensor.dng_active_area},
    {0xC740, T_UNDEFINED|T_PTR, sizeof(badpixel_opcode),  (int)&badpixel_opcode},
};

// Index of specific entries in exif_ifd below.
// *** warning - if entries are added or removed these should be updated ***
#define EXPOSURE_PROGRAM_INDEX      2       // tag 0x8822
#define METERING_MODE_INDEX         10      // tag 0x9207
#define FLASH_MODE_INDEX            11      // tag 0x9209
#define SSTIME_INDEX                13      // tag 0x9290
#define SSTIME_ORIG_INDEX           14      // tag 0x9291

struct dir_entry exif_ifd[]={
    {0x829A, T_RATIONAL,   1,  (int)cam_shutter},          // Shutter speed
    {0x829D, T_RATIONAL,   1,  (int)cam_aperture},         // Aperture
    {0x8822, T_SHORT,      1,  0},                         // ExposureProgram
    {0x8827, T_SHORT|T_PTR,1,  (int)&exif_data.iso},       // ISOSpeedRatings
    {0x9000, T_UNDEFINED,  4,  0x31323230},                // ExifVersion: 2.21
    {0x9003, T_ASCII,      20, (int)cam_datetime},         // DateTimeOriginal
    {0x9201, T_SRATIONAL,  1,  (int)cam_apex_shutter},     // ShutterSpeedValue (APEX units)
    {0x9202, T_RATIONAL,   1,  (int)cam_apex_aperture},    // ApertureValue (APEX units)
    {0x9204, T_SRATIONAL,  1,  (int)cam_exp_bias},         // ExposureBias
    {0x9205, T_RATIONAL,   1,  (int)cam_max_av},           // MaxApertureValue
    {0x9207, T_SHORT,      1,  0},                         // Metering mode
    {0x9209, T_SHORT,      1,  0},                         // Flash mode
    {0x920A, T_RATIONAL,   1,  (int)cam_focal_length},     // FocalLength
    {0x9290, T_ASCII|T_PTR,4,  (int)cam_subsectime},       // DateTime milliseconds
    {0x9291, T_ASCII|T_PTR,4,  (int)cam_subsectime},       // DateTimeOriginal milliseconds
    {0xA405, T_SHORT|T_PTR,1,  (int)&exif_data.effective_focal_length},    // FocalLengthIn35mmFilm
};

tGPS gps_data;

struct dir_entry gpd_ifd[]={
    {0x0000, T_BYTE,              4,  0x00000302},                    //GPSVersionID: 2 3 0 0
    {0x0001, T_ASCII|T_PTR,       2,  (int)gps_data.latitudeRef},     //North or South Latitude "N\0" or "S\0"
    {0x0002, T_RATIONAL,          3,  (int)gps_data.latitude},        //Latitude
    {0x0003, T_ASCII|T_PTR,       2,  (int)gps_data.longitudeRef},    //East or West Latitude "E\0" or "W\0"
    {0x0004, T_RATIONAL,          3,  (int)gps_data.longitude},       //Longitude
    {0x0005, T_BYTE|T_PTR,        1,  (int)&gps_data.heightRef},      //AltitudeRef
    {0x0006, T_RATIONAL,          1,  (int)gps_data.height},          //Altitude
    {0x0007, T_RATIONAL,          3,  (int)gps_data.timeStamp},       //TimeStamp
    {0x0009, T_ASCII|T_PTR,       2,  (int)gps_data.status},          //Status
    //{0x000A, T_ASCII,             1,  0},                             //MeasureMode
    {0x0012, T_ASCII,             7,  (int)gps_data.mapDatum},        //MapDatum 7 + 1 pad byte
    {0x001D, T_ASCII,             11, (int)gps_data.dateStamp},       //DateStamp 11 + 1 pad byte
};

int get_type_size(int type)
{
    switch(type & 0xFF)
    {
    case T_BYTE:
    case T_SBYTE:
    case T_UNDEFINED:
    case T_ASCII:     return 1; 
    case T_SHORT:
    case T_SSHORT:    return 2;
    case T_LONG:
    case T_SLONG:
    case T_FLOAT:     return 4;
    case T_RATIONAL:
    case T_SRATIONAL:
    case T_DOUBLE:    return 8;
    default:          return 0;
    }
}

#define DIR_SIZE(ifd)   (sizeof(ifd)/sizeof(ifd[0]))

struct
{
    struct dir_entry* entry;
    int count;                  // Number of entries to be saved
    int entry_count;            // Total number of entries
} ifd_list[] = 
{
    {ifd0,      DIR_SIZE(ifd0),     DIR_SIZE(ifd0)}, 
    {ifd1,      DIR_SIZE(ifd1),     DIR_SIZE(ifd1)}, 
    {exif_ifd,  DIR_SIZE(exif_ifd), DIR_SIZE(exif_ifd)}, 
    {gpd_ifd,   DIR_SIZE(gpd_ifd),  DIR_SIZE(gpd_ifd)}
};

#define TIFF_HDR_SIZE (8)

char* dng_header_buf = 0;
int dng_header_buf_size;
int dng_header_buf_offset;
char *thumbnail_buf = 0;

void add_to_buf(void* var, int size)
{
    memcpy(dng_header_buf+dng_header_buf_offset,var,size);
    dng_header_buf_offset += size;
}

void add_val_to_buf(int val, int size)
{
    add_to_buf(&val,size);
}

/*
create a dng header, including space for thumbnail if required
if ver1_1 set, creates a dng 1.1 header, otherwise a 1.3 header (matching conf.dng_version)
if minimal is set, don't pad to 512 byte boundery or create thumbnail
*/
void create_dng_header(int ver1_1,int minimal){
    int i,j;
    int extra_offset;
    int raw_offset;

    // Set version and opcodes
    if (ver1_1)
    {
        // If CHDK is removing bad pixels then set DNG version to 1.1 and remove opcodes
        ifd0[DNG_VERSION_INDEX].offset = BE(0x01010000);
        ifd1[BADPIXEL_OPCODE_INDEX].type |= T_SKIP;
    }
    else
    {
        // Set DNG version to 1.3 and add bad pixel opcodes
        ifd0[DNG_VERSION_INDEX].offset = BE(0x01030000);
        ifd1[BADPIXEL_OPCODE_INDEX].type &= ~T_SKIP;
        // Set CFAPattern value
        switch (camera_sensor.cfa_pattern)
        {
        case 0x02010100:
            badpixel_opcode[BADPIX_CFA_INDEX] = BE(1);              // BayerPhase = 1 (top left pixel is green in a green/red row)
            break;
        case 0x01020001:
            badpixel_opcode[BADPIX_CFA_INDEX] = BE(0);              // BayerPhase = 0 (top left pixel is red)
            break;
        case 0x01000201:
            badpixel_opcode[BADPIX_CFA_INDEX] = BE(3);              // BayerPhase = 3 (top left pixel is blue)
            break;
        case 0x00010102:
            badpixel_opcode[BADPIX_CFA_INDEX] = BE(2);              // BayerPhase = 2 (top left pixel is green in a green/blue row)
            break;
        }
    }

    // filling EXIF fields

    int ifd_count = DIR_SIZE(ifd_list);

    if (camera_info.props.gps)
    {
        // If camera has GPS get the GPS data
        get_property_case(camera_info.props.gps, &gps_data, sizeof(gps_data));
    }
    else
    {
        // If no GPS then remove the GPS data from the header - assumes gps_ifd is the last one in ifd_list
        ifd_count--;
        ifd0[GPS_IFD_INDEX].type |= T_SKIP;         // mark entry so it is skipped
    }

    // Fix the counts and offsets where needed

    ifd0[CAMERA_NAME_INDEX].count = ifd0[UNIQUE_CAMERA_MODEL_INDEX].count = strlen(cam_name) + 1;
    ifd0[CHDK_VER_INDEX].offset = (int)camera_info.chdk_dng_ver;
    ifd0[CHDK_VER_INDEX].count = strlen(camera_info.chdk_dng_ver) + 1;
    ifd0[ARTIST_NAME_INDEX].count = strlen(artist_name) + 1;
    ifd0[COPYRIGHT_INDEX].count = strlen(copyright) + 1;
    ifd0[ORIENTATION_INDEX].offset = get_orientation_for_exif(exif_data.orientation);

    exif_ifd[EXPOSURE_PROGRAM_INDEX].offset = get_exp_program_for_exif(exif_data.exp_program);
    exif_ifd[METERING_MODE_INDEX].offset = get_metering_mode_for_exif(exif_data.metering_mode);
    exif_ifd[FLASH_MODE_INDEX].offset = get_flash_mode_for_exif(exif_data.flash_mode, exif_data.flash_fired);
    exif_ifd[SSTIME_INDEX].count = exif_ifd[SSTIME_ORIG_INDEX].count = strlen(cam_subsectime)+1;

    // Skip color matrix and calibration entries that aren't defined for the camera
    if (camera_sensor.calibration_illuminant2 == 0)
    {
        ifd0[ILLUMINANT2_INDEX].type |= T_SKIP;
        ifd0[COLOR_MATRIX2_INDEX].type |= T_SKIP;
    }
    if (camera_sensor.has_calibration1 == 0)    ifd0[CALIBRATION1_INDEX].type |= T_SKIP;
    if (camera_sensor.has_calibration2 == 0)    ifd0[CALIBRATION2_INDEX].type |= T_SKIP;
    if (camera_sensor.has_forwardmatrix1 == 0)  ifd0[FORWARD_MATRIX1_INDEX].type |= T_SKIP;
    if (camera_sensor.has_forwardmatrix2 == 0)  ifd0[FORWARD_MATRIX2_INDEX].type |= T_SKIP;

    // fixup up IFD count values, exclude skipped entries
    for (j=0;j<ifd_count;j++)
    {
        ifd_list[j].count = 0;
        for(i=0; i<ifd_list[j].entry_count; i++)
        {
            if ((ifd_list[j].entry[i].type & T_SKIP) == 0)  // Exclude skipped entries (e.g. GPS info if camera doesn't have GPS)
            {
                ifd_list[j].count++;
            }
        }
    }

    // calculating offset of RAW data and count of entries for each IFD
    raw_offset=TIFF_HDR_SIZE;

    for (j=0;j<ifd_count;j++)
    {
        raw_offset+=6; // IFD header+footer
        for(i=0; i<ifd_list[j].entry_count; i++)
        {
            if ((ifd_list[j].entry[i].type & T_SKIP) == 0)  // Exclude skipped entries (e.g. GPS info if camera doesn't have GPS)
            {
                raw_offset+=12; // IFD directory entry size
                int size_ext=get_type_size(ifd_list[j].entry[i].type)*ifd_list[j].entry[i].count;
                if (size_ext>4) raw_offset+=size_ext+(size_ext&1);
            }
        }
    }

    // creating buffer for writing data
    if(minimal) {
        raw_offset=(raw_offset/4+1)*4; // ensure 32 bit aligned
        dng_header_buf=malloc(raw_offset);
        thumbnail_buf = NULL;
    } else {
        raw_offset=(raw_offset/512+1)*512; // exlusively for CHDK fast file writing
        dng_header_buf=malloc(raw_offset + DNG_TH_BYTES);
        thumbnail_buf = dng_header_buf + raw_offset;
    }
    dng_header_buf_size=raw_offset;
    if (!dng_header_buf)
    {
        thumbnail_buf = NULL;
        return;
    }
    dng_header_buf_offset=0;

    //  writing offsets for EXIF IFD and RAW data and calculating offset for extra data

    extra_offset=TIFF_HDR_SIZE;

    ifd0[SUBIFDS_INDEX].offset = TIFF_HDR_SIZE + ifd_list[0].count * 12 + 6;                            // SubIFDs offset
    ifd0[EXIF_IFD_INDEX].offset = TIFF_HDR_SIZE + (ifd_list[0].count + ifd_list[1].count) * 12 + 6 + 6; // EXIF IFD offset
    if (camera_info.props.gps)
        ifd0[GPS_IFD_INDEX].offset = TIFF_HDR_SIZE + (ifd_list[0].count + ifd_list[1].count + ifd_list[2].count) * 12 + 6 + 6 + 6;  // GPS IFD offset

    ifd0[THUMB_DATA_INDEX].offset = raw_offset;                                     //StripOffsets for thumbnail
    ifd1[RAW_DATA_INDEX].offset = raw_offset + DNG_TH_BYTES;    //StripOffsets for main image

    for (j=0;j<ifd_count;j++)
    {
        extra_offset += 6 + ifd_list[j].count * 12; // IFD header+footer
    }

    // TIFF file header

    add_val_to_buf(0x4949, sizeof(short));      // little endian
    add_val_to_buf(42, sizeof(short));          // An arbitrary but carefully chosen number that further identifies the file as a TIFF file.
    add_val_to_buf(TIFF_HDR_SIZE, sizeof(int)); // offset of first IFD

    // writing IFDs

    for (j=0;j<ifd_count;j++)
    {
        int size_ext;
        add_val_to_buf(ifd_list[j].count, sizeof(short));
        for(i=0; i<ifd_list[j].entry_count; i++)
        {
            if ((ifd_list[j].entry[i].type & T_SKIP) == 0)
            {
                add_val_to_buf(ifd_list[j].entry[i].tag, sizeof(short));
                add_val_to_buf(ifd_list[j].entry[i].type & 0xFF, sizeof(short));
                add_val_to_buf(ifd_list[j].entry[i].count, sizeof(int));
                size_ext=get_type_size(ifd_list[j].entry[i].type)*ifd_list[j].entry[i].count;
                if (size_ext<=4) 
                {
                    if (ifd_list[j].entry[i].type & T_PTR)
                    {
                        add_to_buf((void*)ifd_list[j].entry[i].offset, sizeof(int));
                    }
                    else
                    {
                        add_val_to_buf(ifd_list[j].entry[i].offset, sizeof(int));
                    }
                }
                else
                {
                    add_val_to_buf(extra_offset, sizeof(int));
                    extra_offset += size_ext+(size_ext&1);    
                }
            }
        }
        add_val_to_buf(0, sizeof(int));
    }

    // writing extra data

    for (j=0;j<ifd_count;j++)
    {
        int size_ext;
        for(i=0; i<ifd_list[j].entry_count; i++)
        {
            if ((ifd_list[j].entry[i].type & T_SKIP) == 0)
            {
                size_ext=get_type_size(ifd_list[j].entry[i].type)*ifd_list[j].entry[i].count;
                if (size_ext>4)
                {
                    add_to_buf((void*)ifd_list[j].entry[i].offset, size_ext);
                    if (size_ext&1) add_val_to_buf(0, 1);
                }
            }
        }
    }

    // writing zeros to tail of dng header (just for fun)
    for (i=dng_header_buf_offset; i<dng_header_buf_size; i++) dng_header_buf[i]=0;
}

void free_dng_header(void)
{
    if (dng_header_buf)
    {
        free(dng_header_buf);
        dng_header_buf=NULL;
    }
}

unsigned short get_exp_program_for_exif(int exp_program)
{
    switch(exp_program)
    {
    case MODE_M: return 1;
    case MODE_P: return 2;
    case MODE_AV: return 3;
    case MODE_TV: return 4;
    default: return 0;
    }
}

unsigned short get_orientation_for_exif(short orientation)
{
    switch(orientation)
    {
    case  90: return 6;  // Right  - Top
    case 180: return 3;  // Bottom - Right
    case 270: return 8;  // Left   - Bottom
    case   0:            // Top    - Left
    default : return 1;
    }
}

unsigned short get_flash_mode_for_exif(short mode, short fired){
    fired&=1;
    switch(mode)
    {
    case 0: return (3<<3)|fired; // auto
    case 1: return (1<<3)|fired; // on
    case 2: return (2<<3)|fired; // off
    default: return fired;
    };
}

unsigned short get_metering_mode_for_exif(short metering_mode)
{
    switch (metering_mode)
    {
    case 0: return 5; // Evaluative
    case 1: return 3; // Spot
    case 2: return 2; // CenterWeightedAverage
    default: return 255; // other
    }
}

int pow_calc_2( int mult, int x, int x_div, double y, int y_div)
{
	double x1 = x;
	if ( x_div != 1 ) { x1=x1/x_div;}
	if ( y_div != 1 ) { y=y/y_div;}

	if ( mult==1 )
		return pow( x1, y );
                else
		return mult	* pow( x1, y );
}

int pow_calc( int mult, int x, int x_div, int y, int y_div)
{
	return pow_calc_2( mult, x, x_div, y, y_div);
}

void capture_data_for_exif(void)
{
    short short_prop_val;
    time_t datetime;
    long subsectime;
    struct tm *ttm;
    int wb[3];

    exif_data.iso=shooting_get_iso_market();

    // Shutter speed tags
    get_property_case(camera_info.props.tv, &short_prop_val, sizeof(short_prop_val));
    cam_shutter[0]      = pow_calc( 1000000, 2, 1, -short_prop_val, 96);
    cam_apex_shutter[0] = short_prop_val;

    // Date & time tag (note - uses shutter speed from 'short_prop_val' code above)
    if (camera_info.state.shutter_open_time)
    {
        // milliseconds component of shutter_open_time
        subsectime = (camera_info.state.shutter_open_tick_count - camera_info.tick_count_offset) % 1000;
        // shutter closing time
        datetime = camera_info.state.shutter_open_time + ((cam_shutter[0] + (subsectime * 1000)) / 1000000);
        camera_info.state.shutter_open_time = 0;
    }
    else
    {
        datetime = time(NULL);
        // milliseconds component of datetime
        subsectime = (get_tick_count() - camera_info.tick_count_offset) % 1000;
    }
    ttm = localtime(&datetime);
    sprintf(cam_datetime, "%04d:%02d:%02d %02d:%02d:%02d", ttm->tm_year+1900, ttm->tm_mon+1, ttm->tm_mday, ttm->tm_hour, ttm->tm_min, ttm->tm_sec);
    sprintf(cam_subsectime, "%02d", subsectime/10);     // camera tick count is only accurate to 10 msec intervals

    get_property_case(camera_info.props.av, &short_prop_val, sizeof(short_prop_val));
    cam_aperture[0]      = pow_calc( 10, 2, 1, short_prop_val, 192);
    cam_apex_aperture[0] = short_prop_val;

    get_property_case(camera_info.props.min_av, &short_prop_val, sizeof(short_prop_val));
    cam_max_av[0] = short_prop_val;

    get_property_case(camera_info.props.ev_correction_2, &short_prop_val, sizeof(short_prop_val));
    cam_exp_bias[0] = short_prop_val;

    exif_data.exp_program = camera_info.state.mode_shooting;

    cam_focal_length[0] = get_focal_length(shooting_get_zoom());
    exif_data.effective_focal_length = get_effective_focal_length(shooting_get_zoom()) / 1000;

    get_property_case(camera_info.props.orientation_sensor, &exif_data.orientation, sizeof(exif_data.orientation));
    get_parameter_data(camera_info.params.camera_name, &cam_name, sizeof(cam_name));
    if (camera_info.params.artist_name) get_parameter_data(camera_info.params.artist_name, &artist_name, sizeof(artist_name));
    else if (camera_info.params.owner_name) get_parameter_data(camera_info.params.owner_name, &artist_name, 32);
    if (camera_info.params.copyright) get_parameter_data(camera_info.params.copyright, &copyright, sizeof(copyright));
    get_property_case(camera_info.props.flash_mode, &exif_data.flash_mode, sizeof(exif_data.flash_mode));
    get_property_case(camera_info.props.flash_fire, &exif_data.flash_fired, sizeof(exif_data.flash_fired));
    get_property_case(camera_info.props.metering_mode, &exif_data.metering_mode, sizeof(exif_data.metering_mode));

    get_property_case(camera_info.props.wb_adj, &wb, sizeof(wb));  
    cam_AsShotNeutral[1]=wb[1];
    cam_AsShotNeutral[3]=wb[0];
    cam_AsShotNeutral[5]=wb[2];
}

//-------------------------------------------------------------------

static int convert_dng_to_chdk_raw(char* fn)
{
#define BUF_SIZE (32768)
    FILE *dng, *raw;
    int *buf;
    int i;
    struct stat st;
    struct utimbuf t;

    if (stat(fn, &st) != 0 || st.st_size<=camera_sensor.raw_size)
        return 0;

    running = 1;

    buf=malloc(BUF_SIZE);
    if (buf)
    {
        started();
        dng=fopen(fn,"rb");
        if (dng)
        {
            fread(buf, 1, 8, dng);
            if (buf[0]==0x2A4949 && buf[1]==8)
            {  // chdk dng header
                i=strlen(fn)-3;
                if (strncmp(fn+i,"CR",2)==0) strcpy(fn+i,"WAV"); else strcpy(fn+i,"CRW");
                raw=fopen(fn,"w+b");
                if (raw){
                    fseek(dng, st.st_size-camera_sensor.raw_size, SEEK_SET); // SEEK_END is not working?
                    for (i=0; i<camera_sensor.raw_size/BUF_SIZE; i++)
                    {
                        fread(buf, 1, BUF_SIZE, dng);
                        reverse_bytes_order((char*)buf, BUF_SIZE);
                        fwrite(buf, 1, BUF_SIZE, raw);
                    }
                    fread(buf, 1, camera_sensor.raw_size%BUF_SIZE, dng);
                    reverse_bytes_order((char*)buf, camera_sensor.raw_size%BUF_SIZE);
                    fwrite(buf, 1, camera_sensor.raw_size%BUF_SIZE, raw);
                    fclose(raw);
                    t.actime = t.modtime = time(NULL);
                    utime(fn, &t);
                } // if (raw)
            } // if chdk dng header
            fclose(dng);
        } //if (dng)
        free(buf);
        finished();
    }  //if (buf)

    running = 0;

    return 1;
}

static void load_dng_to_rawbuffer(char *fn, char *rawadr)
{
    running = 1;

    struct stat st;
    if ((stat(fn,&st) == 0) && (st.st_size >= camera_sensor.raw_size))
    {
        int fd = open(fn, O_RDONLY, 0777);
        if (fd >= 0)
        {
            lseek(fd, st.st_size-camera_sensor.raw_size, SEEK_SET);
            read(fd, rawadr, camera_sensor.raw_size);
            close(fd);
            reverse_bytes_order2(rawadr, rawadr, camera_sensor.raw_size);
        }
    }

    running = 0;
}

//-------------------------------------------------------------------
// Functions for creating DNG thumbnail image


// original code to generate the gamma buf
/*
static unsigned char gamma[256];
void fill_gamma_buf(void)
{
    int i;
    if (gamma[255]) return;
    for (i=0; i<12; i++) gamma[i]=pow_calc_2(255, i, 255, 0.5, 1);
    for (i=12; i<64; i++) gamma[i]=pow_calc_2(255, i, 255, 0.4, 1);
    for (i=64; i<=255; i++) gamma[i]=pow_calc_2(255, i, 255, 0.25, 1);
}
*/

static const unsigned char gamma[256] =
{
0,15,22,27,31,35,39,42,45,47,50,52,75,77,79,82,
84,86,88,90,92,93,95,97,99,100,102,103,105,106,108,109,
111,112,113,115,116,117,119,120,121,122,123,125,126,127,128,129,
130,131,132,133,134,136,137,138,139,140,141,141,142,143,144,145,
180,181,181,182,183,183,184,185,185,186,187,187,188,189,189,190,
190,191,192,192,193,193,194,194,195,195,196,197,197,198,198,199,
199,200,200,201,201,202,202,203,203,204,204,205,205,206,206,207,
207,208,208,208,209,209,210,210,211,211,212,212,212,213,213,214,
214,215,215,215,216,216,217,217,217,218,218,219,219,219,220,220,
221,221,221,222,222,222,223,223,224,224,224,225,225,225,226,226,
226,227,227,228,228,228,229,229,229,230,230,230,231,231,231,232,
232,232,233,233,233,234,234,234,235,235,235,235,236,236,236,237,
237,237,238,238,238,239,239,239,239,240,240,240,241,241,241,242,
242,242,242,243,243,243,244,244,244,244,245,245,245,246,246,246,
246,247,247,247,247,248,248,248,249,249,249,249,250,250,250,250,
251,251,251,251,252,252,252,252,253,253,253,253,254,254,254,255
};
void create_thumbnail()
{
    char *buf = thumbnail_buf;
    int shift = camera_sensor.bits_per_pixel - 8;

    int x_inc = camera_sensor.jpeg.width / DNG_TH_WIDTH;
    int y_inc = camera_sensor.jpeg.height / DNG_TH_HEIGHT;

    int x_end = camera_sensor.active_area.x1 + camera_sensor.jpeg.x + DNG_TH_WIDTH*x_inc;
    int y_end = camera_sensor.active_area.y1 + camera_sensor.jpeg.y + DNG_TH_HEIGHT*y_inc;

    int x_off,y_off;

    // The sensor bayer patterns are:
    //  0x02010100  0x01000201  0x01020001
    //      R G         G B         G R
    //      G B         R G         B G
    // for the second pattern yadj shifts the thumbnail row down one line
    // for the third pattern xadj shifts the thumbnail row accross one pixel
    // these make the patterns the same
    int yadj = (camera_sensor.cfa_pattern == 0x01000201) ? 1 : 0;
    int xadj = (camera_sensor.cfa_pattern == 0x01020001) ? 1 : 0;

    for (y_off=camera_sensor.active_area.y1 + camera_sensor.jpeg.y; y_off<y_end; y_off += y_inc)
        for (x_off=camera_sensor.active_area.x1 + camera_sensor.jpeg.x; x_off<x_end; x_off += x_inc)
        {
            int x = (x_off & 0xFFFFFFFE) + xadj;
            int y = (y_off & 0xFFFFFFFE) + yadj;

            *buf++ = gamma[get_raw_pixel(x,y)>>shift];           // red pixel
            //*buf++ = gamma[6*(get_raw_pixel(x+1,y)>>shift)/10];  // green pixel
            int g=get_raw_pixel(x+1,y) >> (shift+1);
            *buf++ = gamma[g+(g>>2)];  // green pixel was (6*g/10), now (g/2 + g/8)
            *buf++ = gamma[get_raw_pixel(x+1,y+1)>>shift];       // blue pixel
        }
}

//-------------------------------------------------------------------
// Functions for handling DNG bad pixel file creation and bad pixel
// removal from images.

#define INIT_BADPIXEL_COUNT -1
#define INIT_BADPIXEL_FILE -2

#define PATH_BADPIXEL_BIN "A/CHDK/badpixel.bin"
#define PATH_BAD_TMP_BIN "A/CHDK/bad_tmp.bin"

int init_badpixel_bin_flag; // contants above to count/create file, > 0 num bad pixel

int raw_init_badpixel_bin()
{
    int count;
    unsigned int x, y, xlen, ylen;
    unsigned short c[9];

    FILE*f;
    if(init_badpixel_bin_flag == INIT_BADPIXEL_FILE)
    {
        f=fopen(PATH_BAD_TMP_BIN,"w+b");
    }
    else if (init_badpixel_bin_flag == INIT_BADPIXEL_COUNT)
    {
        f=NULL;
    }
    else
    {
        return 0;
    }
    count = 0;
    for (x=camera_sensor.active_area.x1; x<camera_sensor.active_area.x2; x++)
    {
    	xlen = 0;
        for (y=camera_sensor.active_area.y1; y<camera_sensor.active_area.y2; y++)
        {
            if (get_raw_pixel(x,y) <= camera_sensor.dng_badpixel_value_limit)
            {
                for (ylen=1; ylen<8 && (y+ylen)<camera_sensor.active_area.y2; ylen++)
                    if (get_raw_pixel(x,y+ylen) > camera_sensor.dng_badpixel_value_limit)
                        break;
                if (f)
                {
                    c[++xlen] = y | ((ylen-1) << 13);
                    if (xlen == 8)
                    {
                        c[0] = x | ((xlen-1) << 13);
                        fwrite(c, 2, xlen+1, f);
                        xlen = 0;
                    }
                }
                count = count + ylen;
                y += ylen - 1;
            }
        }
        if (f && (xlen > 0))
        {
            c[0] = x | ((xlen-1) << 13);
            fwrite(c, 2, xlen+1, f);
        }
    }
    if (f) fclose(f);
    init_badpixel_bin_flag = count;
    camera_info.state.state_shooting_progress = SHOOTING_PROGRESS_PROCESSING;
    return 1;
}

short* binary_list=NULL;
int binary_count=-1;

void unload_bad_pixels_list_b(void)
{
    if (binary_list) free(binary_list);
    binary_list=NULL;
    binary_count=-1;
}

void load_bad_pixels_list_b(char* filename)
{
    struct stat st;
    long filesize;
    void* ptr;
    FILE *fd;

    if ( filename==0 )
    { 
        unload_bad_pixels_list_b();
        return;
    }

    binary_count=-1;
    if (stat(filename,&st)!=0) return;
    filesize=st.st_size;
    if (filesize%sizeof(short) != 0) return;
    if (filesize == 0) { binary_count = 0; return; }    // Allow empty badpixel.bin file
    ptr=malloc(filesize);
    if (!ptr) return;
    fd=fopen(filename, "rb");
    if (fd)
    {
        fread(ptr,1, filesize,fd);
        fclose(fd);
        binary_list=ptr;
        binary_count=filesize/sizeof(short);
    }
    else free(ptr);
}

void patch_bad_pixels_b(void)
{
    int i;
    short* ptr=binary_list;
    short x, y, xcnt, ycnt;
    for (i=0; i<binary_count;)
    {
        x = ptr[i] & 0x1FFF;
        xcnt = (ptr[i] >> 13) & 7;
        i++;
        for (; xcnt>=0; xcnt--)
        {
            y = ptr[i] & 0x1FFF;
            ycnt = (ptr[i] >> 13) & 7;
            i++;
            for (; ycnt>=0; ycnt--, y++)
                if (get_raw_pixel(x, y) <= camera_sensor.dng_badpixel_value_limit)
                    patch_bad_pixel(x, y);
        }
    }
}

int badpixel_list_loaded_b(void)
{
    return (binary_count >= 0) ? 1 : 0;
}

// -----------------------------------------------

static unsigned int badpix_cnt1;

static int action_stack_BADPIX_S3()
{
    action_pop_func(0);
    running = 0;
    return 1;
}

static int action_stack_BADPIX_S2()
{
    // Process bad pixel generation actions

    action_pop_func(0);

    console_clear();
    if (badpix_cnt1 == init_badpixel_bin_flag)
    {
        // TODO script asked confirmation first
        // should sanity check bad pixel count at least,
        // wrong buffer address could make badpixel bigger than available mem
        char msg[32];
        console_add_line("badpixel.bin created.");
        sprintf(msg, "Bad pixel count: %d", badpix_cnt1);
        console_add_line(msg);
        remove(PATH_BADPIXEL_BIN);
        rename(PATH_BAD_TMP_BIN,PATH_BADPIXEL_BIN);
    }
    else
    {
        console_add_line("badpixel.bin failed.");
        console_add_line("Please try again.");
    }
    init_badpixel_bin_flag = 0;
    remove(PATH_BAD_TMP_BIN);

    // Delay to give user time to read messages
    action_push_func(action_stack_BADPIX_S3);
    action_push_delay(3000);

    return 1;
}

static int action_stack_BADPIX_S1()
{
    // Process bad pixel generation actions

    action_pop_func(0);

    // Count bad pixels from previous shot
    badpix_cnt1 = init_badpixel_bin_flag;
    init_badpixel_bin_flag = INIT_BADPIXEL_FILE;
    shooting_set_tv96_direct(96, SET_LATER);

    // Push stack items for next phase (note reversed execution order)
    action_push_func(action_stack_BADPIX_S2);
    action_push_shoot(1);

    return 1;
}

static int action_stack_BADPIX_START()
{
    // Process bad pixel generation actions

    action_pop_func(0);

    // Notify yser
    console_clear();
    console_add_line("Wait please... ");
    console_add_line("This takes a few seconds,");
    console_add_line("don't panic!");

    init_badpixel_bin_flag = INIT_BADPIXEL_COUNT;

    shooting_set_tv96_direct(96, SET_LATER);

    // Push stack items for next phase (note reversed execution order)
    action_push_func(action_stack_BADPIX_S1);
    action_push_shoot(1);
    action_push_delay(3000);

    return 1;
}

void create_badpixel_bin()
{
    if (!camera_info.state.mode_rec)
    {
        gui_mbox_init(LANG_ERROR, LANG_MSG_RECMODE_REQUIRED, MBOX_BTN_OK|MBOX_TEXT_CENTER, NULL);
        return;
    }

    running = 1;

    gui_set_mode(&altGuiHandler);
    // Create an action stack to generate bad pixels - start with action_stack_BADPIX_START func above
    action_stack_create(&action_stack_BADPIX_START);
}

// TODO we really only need done/not done so far
#define RB_STAGE_DONE           0
#define RB_STAGE_INIT           1
#define RB_STAGE_REVERSING      2
#define RB_STAGE_DEREVERSING    3

/*
chunk size to for reversing task.
This defines the minimum increment that can be written in the writing task
smaller sizes reduce the chance the writing task will have to wait for
the initial reverse to finish, but increases the amount of time spent sleeping, 
and may increase the number of writes
From testing, 512kb appears to be a reasonable compromise
*/
#define DNG_REV_CHUNK_SIZE  (512*1024)

/*
chunk size for writing final chunks of DNG
only applicable to cameras with a single raw buffer
defines the size of chunks write at the end of the raw data
This this affects how well the reversing task can restore the buffer to
original byte order in parallel with writing, and how much overhead there
is for the final chunk.
*/
#define DNG_END_CHUNK_SIZE (512*1024)

/*
number of minimum number of chunks to write at the end (single raw buffer cams only)
*/
#define DNG_END_NUM_CHUNKS (3)

static struct {
    // all pointers here are cached or uncached per user settings
    // the following 3 values are not modifed after initialization
    char *src; // intial src address
    char *dst; // initial dest address, may be same as src
    char *end; // end of dst
    // the following 3 track the state of the writing and reversing process
    char *reversed; // pointer to completed, set by reverse_bytes_task
    char *written; // pointer to written, set by main task
    int stage; // stage to detect when done
} rb_state;

void reverse_bytes_task() {
    char *src = rb_state.src;
    rb_state.stage = RB_STAGE_REVERSING;
    rb_state.reversed = rb_state.dst;
    // reverse byte order of frame buffer for DNG in chunks, to allow writing to proceed in parallel
    while(rb_state.reversed < rb_state.end) {
        int chunk_size;
        if(rb_state.reversed + DNG_REV_CHUNK_SIZE > rb_state.end) {
            chunk_size = rb_state.end - rb_state.reversed;
        } else {
            chunk_size = DNG_REV_CHUNK_SIZE;
        }
        reverse_bytes_order2(src, rb_state.reversed, chunk_size);
        src += chunk_size;
        rb_state.reversed += chunk_size;
        // seems to give slightly faster times with less variation
        // usually plenty of time to reverse, but in configurations with
        // slow camera + small sensor + fast card + single buffer
        // may cause some avoidable overhead
        msleep(10);
    }
    rb_state.stage = RB_STAGE_DEREVERSING;
    // if only a single raw buffer exists, restore the original byte order for
    // the portions of the buffer which have been written out, waiting as needed
    if(rb_state.src == rb_state.dst) {
        src = rb_state.src;
        int offset = 0;
        while(src < rb_state.end) {
            int chunk_size = rb_state.written - src;
            if(!chunk_size) {
                msleep(10);
                continue;
            }
            reverse_bytes_order(src, chunk_size);
            src += chunk_size;
        }
        // if reverse was done on cached raw, 
        // clean cache so canon FW doesn't see reversed data in uncached
        if(ADR_IS_CACHED(rb_state.dst)) {
            dcache_clean_all();
        }
    }


    rb_state.stage = RB_STAGE_DONE;
    ExitTask();
}

//-------------------------------------------------------------------
// Write DNG header, thumbnail and data to file


int write_dng(char* rawadr, char* altrawadr) 
{
    int fd;

    create_dng_header(conf.dng_version,0);

    if (!dng_header_buf) {
        return 0;
    }

    if (conf.dng_version)
        patch_bad_pixels_b();

    create_thumbnail();

    // TODO - sanity check that prevous task isn't hanging around
    if(rb_state.stage != RB_STAGE_DONE) {
        int i;
        for(i=0;i<50;i++) {
            debug_led(1);
            msleep(200);
            debug_led(0);
            msleep(200);
        }
        return 0;
    }
    rb_state.stage = RB_STAGE_INIT;
    rb_state.src = rawadr;
    rb_state.written = rb_state.reversed = rb_state.dst = altrawadr;
    rb_state.end = rb_state.dst + camera_sensor.raw_size;

    // task is created with lower priority than spytask (0x19) 
    // to improve chance of spytask getting control when write completes
    CreateTask("RevBytes",0x1A,0x400,reverse_bytes_task);

    fd = raw_createfile();
    if(fd < 0) {
        // task already started, pretend write completed and wait
        rb_state.written = rb_state.end;
        while(rb_state.stage != RB_STAGE_DONE) {
            msleep(10);
        }
        return 0;
    }

    // ensure thumbnail is written to uncached
    dcache_clean_all();
    write(fd, ADR_TO_UNCACHED(dng_header_buf), dng_header_buf_size + DNG_TH_BYTES);
    free_dng_header();

    while(rb_state.written < rb_state.end) {
        int size = rb_state.reversed - rb_state.written; 
        if(!size) {
            msleep(10);
            continue;
        }
        // if de-reversing, force DNG_NUM_END_CHUNKS at the end, gives better performance on vxworks
        // doesn't seem to have significant cost on dryos
        if(rawadr == altrawadr) {
            if(size > DNG_END_CHUNK_SIZE && (rb_state.written + DNG_END_CHUNK_SIZE*DNG_END_NUM_CHUNKS) >= rb_state.end) {
                size = DNG_END_CHUNK_SIZE;
            }
        }
        // ensure reversed data is cleaned out to uncached before attempting write
        if(conf.raw_cache) {
            dcache_clean_all();
        }
        write(fd,ADR_TO_UNCACHED(rb_state.written),size);
        rb_state.written += size;
    }

    raw_closefile(fd);

    // wait for de-reverse, if required
    while(rb_state.stage != RB_STAGE_DONE) {
        msleep(10);
    }
    return 1;
}

void create_dng_header_for_ptp(ptp_data_chunk *pdc) 
{
    create_dng_header(0,1);
    if (dng_header_buf) {
        pdc->address = (unsigned int)dng_header_buf; // cached may be slightly slower, but need to clean otherwise
        pdc->length = (unsigned int)dng_header_buf_size;
    } else {
        pdc->address = 0;
        pdc->length = 0;
    }
}
void free_dng_header_for_ptp()
{
    free_dng_header();
}

/*********** BEGIN OF AUXILARY PART **********************/

//---------------------------------------------------------
// PURPOSE: Finalize module operations (close allocs, etc)
// RETURN VALUE: 0-ok, 1-fail
//---------------------------------------------------------
int _module_unloader()
{
    unload_bad_pixels_list_b();
    free_dng_header();
    return 0;
}

int _module_can_unload()
{
    return (running == 0) && (remotecap_using_dng_module() == 0) && ((conf.save_raw == 0) || (conf.dng_raw == 0));
}

/******************** Module Information structure ******************/

libdng_sym _libdng =
{
    {
         0, _module_unloader, _module_can_unload, 0, 0
    },

    create_badpixel_bin,
    raw_init_badpixel_bin,
    capture_data_for_exif,
    load_bad_pixels_list_b,
    badpixel_list_loaded_b,

    convert_dng_to_chdk_raw,
    write_dng,
    load_dng_to_rawbuffer,
    // for remote capture
	create_dng_header_for_ptp,
	free_dng_header_for_ptp
};

struct ModuleInfo _module_info =
{
    MODULEINFO_V1_MAGICNUM,
    sizeof(struct ModuleInfo),
    DNG_VERSION,                // Module version

    ANY_CHDK_BRANCH, 0,         // Requirements of CHDK version
    ANY_PLATFORM_ALLOWED,       // Specify platform dependency

    (int32_t)"DNG (dll)",       // Module name
    (int32_t)"Processing of DNG",

    &_libdng.base,

    CONF_VERSION,               // CONF version
    ANY_VERSION,                // CAM SCREEN version
    CAM_SENSOR_VERSION,         // CAM SENSOR version
    CAM_INFO_VERSION,           // CAM INFO version
};

/*************** END OF AUXILARY PART *******************/
