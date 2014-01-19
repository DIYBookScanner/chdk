#include "camera_info.h"
#include "stdlib.h"
#include "keyboard.h"

//-------------------------------------------------------------------
// Lua and uBasic script key helper funtions

__attribute__((short_call)) int script_key_is_pressed(int k)
{
    if (k==0xFF)
        return get_usb_power(1);
    if (k > 0)
        return kbd_is_key_pressed(k);
    return 0;
}

__attribute__((short_call)) int script_key_is_clicked(int k)
{
    if (k==0xFF)
        return get_usb_power(1);
    if (k > 0)
        return (camera_info.state.kbd_last_clicked == k);
    return 0;
}

static const struct Keynames {
    int keyid;
    char *keyname;
} keynames[] = {
    { KEY_UP,               "up"         },
    { KEY_DOWN,             "down"       },
    { KEY_LEFT,             "left"       },
    { KEY_RIGHT,            "right"      },
    { KEY_SET,              "set"        },
    { KEY_SHOOT_HALF,       "shoot_half" },
    { KEY_SHOOT_FULL,       "shoot_full" },
    { KEY_SHOOT_FULL_ONLY,  "shoot_full_only" },
    { KEY_ZOOM_IN,          "zoom_in"    },
    { KEY_ZOOM_OUT,         "zoom_out"   },
    { KEY_MENU,             "menu"       },
    { KEY_DISPLAY,          "display"    },
    { KEY_PRINT,            "print"      },
    { KEY_ERASE,            "erase"      },
    { KEY_ISO,              "iso"        },
    { KEY_FLASH,            "flash"      },
    { KEY_MF,               "mf"         },
    { KEY_MACRO,            "macro"      },
    { KEY_VIDEO,            "video"      },
    { KEY_TIMER,            "timer"      },
    { KEY_EXPO_CORR,        "expo_corr"  },
    { KEY_MICROPHONE,       "fe"         },
    { KEY_FACE,             "face"       },
    { KEY_ZOOM_ASSIST,      "zoom_assist"},
    { KEY_AE_LOCK,          "ae_lock"    },
    { KEY_METERING,         "metering_mode"},
    { KEY_HELP,             "help"       },
    { KEY_MODE,             "mode"       },
    { 0xFF,                 "remote"     },
    { 0xFFFF,               "no_key"     },
};

__attribute__((short_call)) int script_keyid_by_name (const char *n)
{
    int i;
    for (i=0;i<sizeof(keynames)/sizeof(keynames[0]);i++)
    if (strcmp(keynames[i].keyname,n) == 0)
        return keynames[i].keyid;
    return 0;
}

//-------------------------------------------------------------------
