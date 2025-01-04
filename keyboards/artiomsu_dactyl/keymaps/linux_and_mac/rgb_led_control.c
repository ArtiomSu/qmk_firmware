#include "sharedDefines.h"

bool rgb_show = true;
bool rgb_timed_out = true; // set to true so that you will need to type in the password straight away
uint32_t rgb_time_out_value = 300000; // in milliseconds // 5 minutes by default

#define LAYER_NUM_LEDS_INDIC 10

const rgblight_segment_t PROGMEM led_l_capslock[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, (LAYER_NUM_LEDS_INDIC / 2), HSV_RED}       // Light 1 LEDs, starting with LED 0
);

const rgblight_segment_t PROGMEM led_l_numlock[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, (LAYER_NUM_LEDS_INDIC / 2), HSV_SPRINGGREEN}       // Light 1 LEDs, starting with LED 1
);

const rgblight_segment_t PROGMEM led_l_mac_main[] = RGBLIGHT_LAYER_SEGMENTS(
    {55, 4,
    21, 255, 170} // orange
);

const rgblight_segment_t PROGMEM led_l_colemac[] = RGBLIGHT_LAYER_SEGMENTS(
    {50, 6, HSV_TEAL}
);

const rgblight_segment_t PROGMEM led_l_symbols[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, LAYER_NUM_LEDS_INDIC,
    181, 255, 170} // purple
);

const rgblight_segment_t PROGMEM led_l_macros[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, LAYER_NUM_LEDS_INDIC, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM led_l_gaming[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, LAYER_NUM_LEDS_INDIC, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM led_l_mouse[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, LAYER_NUM_LEDS_INDIC, HSV_WHITE}
);

const rgblight_segment_t PROGMEM led_l_nav[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, LAYER_NUM_LEDS_INDIC, HSV_PINK}
);

const rgblight_segment_t PROGMEM led_l_track_ball[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, LAYER_NUM_LEDS_INDIC, HSV_RED}
);

const rgblight_segment_t PROGMEM led_l_on_combos[] = RGBLIGHT_LAYER_SEGMENTS(
    {31, 5, HSV_RED}
);

const rgblight_segment_t PROGMEM led_l_on_password_bypass[] = RGBLIGHT_LAYER_SEGMENTS(
    {37, 6, HSV_SPRINGGREEN}
);

const rgblight_segment_t PROGMEM led_l_on_bunny_hopping[] = RGBLIGHT_LAYER_SEGMENTS(
    {59, 4, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM led_l_on_leader[] = RGBLIGHT_LAYER_SEGMENTS(
    {30, 6, HSV_BLUE}
);

const rgblight_segment_t PROGMEM led_l_on_dynamic_macros_rec[] = RGBLIGHT_LAYER_SEGMENTS(
    {65, 43, HSV_GREEN}
);

const rgblight_segment_t PROGMEM led_l_password_locked[] = RGBLIGHT_LAYER_SEGMENTS(
    {35, 30, HSV_RED}
);

// don't forget to increase RGBLIGHT_MAX_LAYERS in config.h
// now don't forget to increase rgblight.layers.max in keyboard.json
const rgblight_segment_t* const PROGMEM led_all_layers[] = RGBLIGHT_LAYERS_LIST(
    led_l_capslock,               // 0
    led_l_numlock,                // 1
    led_l_mac_main,               // 2
    led_l_colemac,                // 3
    led_l_symbols,                // 4
    led_l_macros,                 // 5
    led_l_gaming,                 // 6
    led_l_mouse,                  // 7
    led_l_nav,                    // 8
    led_l_track_ball,             // 9

    led_l_on_combos,              // 10
    led_l_on_password_bypass,     // 11
    led_l_on_bunny_hopping,       // 12
    led_l_on_leader,              // 13
    led_l_on_dynamic_macros_rec,  // 14
    led_l_password_locked         // 15
);

enum RGB_LAYER_MODS_STATE {
    RGB_L_M_S_CAPS = 0,
    RGB_L_M_S_NUM = 1,
    RGB_L_M_S_L_MAC = 2,
    RGB_L_M_S_L_COLMAC = 3,
    RGB_L_M_S_L_SYM = 4,
    RGB_L_M_S_L_MACROS = 5,
    RGB_L_M_S_L_GAMING = 6,
    RGB_L_M_S_L_MOUSE = 7,
    RGB_L_M_S_L_NAV = 8,
    RGB_L_M_S_L_TRACK_BALL = 9,
    RGB_L_M_S_COMBOS = 10,
    RGB_L_M_S_PASS_BYPASS = 11,
    RGB_L_M_S_B_HOPS = 12,
    RGB_L_M_S_LEADER = 13,
    RGB_L_M_S_MACRO_REC = 14,
    RGB_L_M_S_PASS_LOCK = 15
};

void default_layer_blink_unblink(bool blink, enum RGB_LAYER_MODS_STATE layer){
    blink ? rgblight_blink_layer_repeat(layer, 1000, 5) : rgblight_unblink_layer(layer);
}

void default_layer_blink_unblink_t(bool blink, enum RGB_LAYER_MODS_STATE layer, uint16_t duration_ms, uint8_t times){
    blink ? rgblight_blink_layer_repeat(layer, duration_ms, times) : rgblight_unblink_layer(layer);
}

void keyboard_post_init_user(void) {
    rgblight_layers = led_all_layers;
    // set this to sync the state of the two halves since we are not using eeprom.
    rgblight_mode_noeeprom(RGBLIGHT_MODE_TWINKLE + 3);
    rgblight_sethsv_noeeprom(13, 250, 20);
    switch (detected_host_os())
    {
        case OS_MACOS:
        case OS_IOS:
            mac_mode = true;
            manage_mac_mode_fn();
            break;
        default:
            break;
    }
}

void suspend_power_down_user(void) {
    rgb_show = true;
}

void suspend_wakeup_init_user(void) {
    rgb_show = false;
}

void rgb_manage_leader(bool on){
    rgblight_set_layer_state(RGB_L_M_S_LEADER, on);
}

void rgb_manage_timeout(bool timed_out){
    if(timed_out){
        if(rgblight_is_enabled()){
            rgblight_disable_noeeprom();
        }
    }else{
        if(!rgblight_is_enabled()){
            if(rgb_show){
                rgblight_enable_noeeprom();
            }
        }else{
            if(!rgb_show){
                // bit of a hack here but works for now..
                rgblight_unblink_all_but_layer(0);
                rgblight_set_layer_state(RGB_L_M_S_L_MOUSE, false);
                rgblight_disable_noeeprom();
            }
        }
    }
}

void rgb_manage_macro_recording(bool on){
    default_layer_blink_unblink_t(on, RGB_L_M_S_MACRO_REC, 800, 10);
}

void rgb_manage_password_lock(bool on){
    rgblight_set_layer_state(RGB_L_M_S_PASS_LOCK, on);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    default_layer_blink_unblink(layer_state_cmp(state, Layer_mac_main), RGB_L_M_S_L_MAC);
    default_layer_blink_unblink(layer_state_cmp(state, Layer_colemak), RGB_L_M_S_L_COLMAC);
    rgblight_set_layer_state(RGB_L_M_S_L_SYM, layer_state_cmp(state, Layer_symbols) || layer_state_cmp(state, Layer_mac_symbols));
    rgblight_set_layer_state(RGB_L_M_S_L_MACROS, layer_state_cmp(state, Layer_macros));
    rgblight_set_layer_state(RGB_L_M_S_L_GAMING, layer_state_cmp(state, Layer_gaming));
    rgblight_set_layer_state(RGB_L_M_S_L_MOUSE, layer_state_cmp(state, Layer_mouse));
    rgblight_set_layer_state(RGB_L_M_S_L_NAV, layer_state_cmp(state, Layer_nav));
    rgblight_set_layer_state(RGB_L_M_S_L_TRACK_BALL, layer_state_cmp(state, Layer_track_ball));

    default_layer_blink_unblink(combos_on, RGB_L_M_S_COMBOS);
    default_layer_blink_unblink(password_bypass, RGB_L_M_S_PASS_BYPASS);
    default_layer_blink_unblink(enable_bunnyhop, RGB_L_M_S_B_HOPS);
    default_layer_blink_unblink_t(dynamic_macro_recording, RGB_L_M_S_MACRO_REC, 800, 10);

    return state;
}

bool led_update_user(led_t led_state) {
    default_layer_blink_unblink(led_state.caps_lock, RGB_L_M_S_CAPS);
    default_layer_blink_unblink(led_state.num_lock, RGB_L_M_S_NUM);
    return true;
}
