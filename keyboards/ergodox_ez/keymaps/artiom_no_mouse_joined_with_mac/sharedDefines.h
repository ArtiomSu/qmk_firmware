#ifndef SHAREDDEFINES_H
#define SHAREDDEFINES_H

#include QMK_KEYBOARD_H
#include "version.h"

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
#define Layer_symbols 2
#define Layer_mac_symbols 3
#define Layer_macros 4
#define Layer_gaming 5

// layer Colours since they are different from layers themselves now
#define Layer_main_colour 0
#define Layer_symbols_colour 1
#define Layer_macros_colour 2
#define Layer_gaming_colour 3


enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  ST_MACRO_SSH,
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
  ST_M_toggle_main_layer_brightness,
  ST_M_led_timeout_30s,
  ST_M_led_timeout_1m,
  ST_M_led_timeout_5m,
  ST_M_led_timeout_10m,
  ST_M_combo_toggle,
  ST_M_mac_mode_toggle
};

extern bool rgb_show;
extern bool rgb_timed_out;
extern int timeout_counter;
extern uint32_t rgb_sync_to_timer; //sync out timer to the official rgb timer.
extern int rgb_time_out_value;   // 100 = ~9seconds, 666= ~ 54s

extern bool use_bunnyhop;
extern bool enable_bunnyhop;
extern int bunny_hop_delay_counter;

extern int modifiers_blink_count; // this is for stuff like enable_bunnyhop and the leader key
extern bool leader_key_is_running;

extern int brightness_amount;
extern int hue_amount;

extern bool main_layer_brightness; // can disable the main layer rgb individually

extern bool combos_on; // use combo feature by default
extern bool mac_mode;

extern int word_length_count;
extern int last_word_length;

//do not change the following
extern bool use_default_lighting; // do not change used inside loop
extern bool g_suspend_state;

//colours                   hsv             // rgb
#define KM_Light_red        {0,223,252}     // 252,32,31
#define KM_Light_yellow     {31,208,234}    // 234,181,42
#define KM_dirty_green      {97,231,230}    // 21,230,76
#define LM_golden_yellow    {32,191,236}    // 236,191,59
#define LM_Slight_dark_red  {255,246,238}   //238,8,23
#define LM_Blue             {166,240,228}   //13,41,228
#define LM_LightOrange      {0,183,238}     //238,67,66
#define LM_Cyan             {130,255,255}   //0,249,255
#define LM_Yellow           {42,248,240}    //240,237,6
#define LM_______           {0,0,0}         //no colour
#define LM_Light_pink       {216,123,238}   // 238,122,235
#define LM_White            {0,0,255}       // 255,255,255
#define LM_Red_Blood        {6,240,224}     // 224,43,13
#define LM_NeonGreen        {82,247,246}    // 28,246,7
#define LM_LighterBlue      {178,231,238}   // 53,22,238
#define LM_darker_Yellow    {36,230,248}    // 248,213,24
#define LM_Light_orange     {31,255,255}    // 255,186,0
#define LM_Blooder_Red      {0,242,205}     // 205,11,10
#define LM_LightBrown       {19,150,185}    // 185,125,75
#define LM_Orange           {13,237,253}    // 253,90,17
#define LM_skyBlue          {124,62,253}    // 190,253,246
#define LM_Toirquise        {115,255,248}   // 0,248,169
#define LM_Purple           {195,255,251}   // 136,0,251
#define LM_Light_blue_purple {178,183,238}   // 92,66,238


#define KM_TEST {214,253,245} //pink

#endif
