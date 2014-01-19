#ifndef SCRIPT_KEY_FUNCS_H
#define SCRIPT_KEY_FUNCS_H

// CHDK Script interface

// Note: used in modules and platform independent code. 
// Do not add platform dependent stuff in here (#ifdef/#endif compile options or camera dependent values)

//-------------------------------------------------------------------
__attribute__((short_call)) int script_key_is_pressed( int keyid );
__attribute__((short_call)) int script_key_is_clicked( int keyid );
__attribute__((short_call)) int script_keyid_by_name( const char *name );
//-------------------------------------------------------------------

#endif
