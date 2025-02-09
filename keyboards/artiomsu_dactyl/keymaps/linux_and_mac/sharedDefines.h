#ifndef SHAREDDEFINES_H
#define SHAREDDEFINES_H

#include QMK_KEYBOARD_H
//#include "version.h"
#include "secrets.h"
#include "os_detection.h"
#include "raw_hid_client.h"

#define bool _Bool
#define true 1
#define false 0

// layer defines
/*
    Layers accessing other layers must be under the layer that they access.
    For example, if layer 1 is accessing layer 2, layer 2 must be after layer 1.
*/
#define Layer_main 0
#define Layer_mac_main 1
#define Layer_colemak 2
#define Layer_symbols 3
#define Layer_mac_symbols 4
#define Layer_macros 5
#define Layer_gaming 6
#define Layer_mouse 7
#define Layer_nav 8
#define Layer_track_ball 9

// layer Colours since they are different from layers themselves now
#define Layer_main_colour 0
#define Layer_symbols_colour 1
#define Layer_macros_colour 2
#define Layer_gaming_colour 3


enum custom_keycodes {
  ST_MACRO_SSH = SAFE_RANGE, // SAFE_RANGE sets the first one in the list to a value that won't interfere with anything
  ST_MACRO_VIM_wq,
  ST_M_n_equal,
  ST_M_n_equal_2,
  ST_M_l_equal,
  ST_M_g_equal,
  ST_M_vim_q,
  ST_M_vim_w,
  ST_M_vim_sp,
  ST_M_vim_vs,
  ST_M_vim_sp_e,
  ST_M_vim_vs_e,
  ST_M_double_colon,
  ST_M_bunny_hop,
  ST_M_enable_bunny_hop,
  ST_M_brightness_down,
  ST_M_brightness_up,
  ST_M_hue_down,
  ST_M_hue_up,
  ST_M_sat_down,
  ST_M_sat_up,
  ST_M_mode_down,
  ST_M_mode_up,
  ST_M_toggle_rgb,
  ST_M_led_timeout_30s,
  ST_M_led_timeout_1m,
  ST_M_led_timeout_5m,
  ST_M_led_timeout_10m,
  ST_M_combo_toggle,
  ST_M_mac_mode_toggle,
  ST_M_colemak_mode_toggle,
  ST_M_password_bypass,
  ST_M_rgb_snake,
  ST_M_rgb_twinkle,
  ST_M_rgb_knight,
  RAW_HID_M_1,
  RAW_HID_TB_DPI_UP,
  RAW_HID_TB_DPI_DOWN,
  RAW_HID_TB_DPI_DEFAULT,
  RAW_HID_TB_SCROLL_UP,
  RAW_HID_TB_SCROLL_DOWN,
  RAW_HID_TB_SCROLL_DEFAULT,
  RAW_HID_TB_SCROLL_INVERT,
  RAW_HID_TB_DRAG_SCROLL
};

extern bool rgb_show;
extern bool rgb_timed_out;
extern uint32_t rgb_timeout_counter;
extern uint32_t rgb_time_out_value;  // in milliseconds

extern bool use_bunnyhop;
extern bool enable_bunnyhop;
extern uint8_t bunny_hop_delay_counter;

extern bool leader_key_is_running;

extern bool combos_on; // use combo feature by default
extern bool mac_mode;

extern bool colemak_mode;

//custom password to use keyboard
//#error "Change the password before compiling and commment this line out"
/*
    To make this work you need to create a file called secrets.c and secrets.h

    In secrets.h you need to define the following:
    ----------------------------------------------
    #ifndef SECRETSDEFINES_H
    #define SECRETSDEFINES_H

    #define UNLOCK_PASSWORD_LENGTH 2

    #endif
    ----------------------------------------------

    In secrets.c you need to define the following:
    ----------------------------------------------
    #include "secrets.h"

    uint16_t unlock_password[UNLOCK_PASSWORD_LENGTH] = {4, 5}; // example a, b
    ----------------------------------------------

    To get the keycodes check this following link:
    https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2
*/

extern uint16_t unlock_password_index;
extern uint16_t unlock_password[UNLOCK_PASSWORD_LENGTH];

extern bool password_bypass;

void manage_mac_mode_fn(void);
void rgb_manage_leader(bool on);
void rgb_manage_timeout(bool timed_out);
void rgb_manage_macro_recording(bool on);
void rgb_manage_password_lock(bool on);

extern bool dynamic_macro_recording;

#endif
