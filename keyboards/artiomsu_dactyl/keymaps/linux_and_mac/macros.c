#include "sharedDefines.h"

bool use_bunnyhop = false;
bool enable_bunnyhop = false;

bool combos_on = true; // use combo feature by default
bool mac_mode = false;
bool colemak_mode = false;
uint32_t rgb_timeout_counter = 0;


uint16_t unlock_password_index = 0;
bool password_bypass = false;
bool dynamic_macro_recording = false;

bool dynamic_macro_record_start_user(int8_t direction){
    dynamic_macro_recording = true;
    rgb_manage_macro_recording(dynamic_macro_recording);
    return true;
}

bool dynamic_macro_record_end_user(int8_t direction){
    dynamic_macro_recording = false;
    rgb_manage_macro_recording(dynamic_macro_recording);
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(rgb_timed_out && unlock_password_index < UNLOCK_PASSWORD_LENGTH && !password_bypass){
        if(record->event.pressed){
            if(unlock_password[unlock_password_index] == keycode && record->event.pressed){
                unlock_password_index++;
            }else{
                unlock_password_index = 0;
            }
        }
        rgb_manage_password_lock(true);
        return false; // return false to block the keys.
    }
    rgb_manage_password_lock(false);

    unlock_password_index = 0;
    rgb_timed_out = false;
    rgb_timeout_counter=0; //reset timeout counter also, so that it will always count from the time the key was pressed.

    if(record->event.pressed){ // most are only using event pressed
    switch (keycode) {
        case ST_MACRO_SSH:
            SEND_STRING(SS_LCTL(SS_TAP(X_R)) SS_TAP(X_S) SS_TAP(X_S) SS_TAP(X_H));
        break;
        case ST_MACRO_VIM_wq: //save and exit vim
            SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_ESCAPE) SS_LSFT(SS_TAP(X_SEMICOLON)) SS_TAP(X_W) SS_TAP(X_Q) SS_TAP(X_ENTER));
        break;
        case ST_M_n_equal: // !=
            SEND_STRING(SS_LSFT(SS_TAP(X_1)) SS_TAP(X_EQUAL));
        break;
        case ST_M_n_equal_2: // !==
            SEND_STRING(SS_LSFT(SS_TAP(X_1)) SS_TAP(X_EQUAL) SS_TAP(X_EQUAL));
        break;
        case ST_M_l_equal: // <=
            SEND_STRING(SS_LSFT(SS_TAP(X_COMMA)) SS_TAP(X_EQUAL));
        break;
        case ST_M_g_equal:  // >=
            SEND_STRING(SS_LSFT(SS_TAP(X_DOT)) SS_TAP(X_EQUAL));
        break;
        case ST_M_vim_q: //quite vim without saving
            SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_ESCAPE)  SS_LSFT(SS_TAP(X_SEMICOLON)) SS_TAP(X_Q) SS_LSFT(SS_TAP(X_1)) SS_TAP(X_ENTER));
        break;
        case ST_M_vim_w: // write only
            SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_ESCAPE)  SS_LSFT(SS_TAP(X_SEMICOLON)) SS_TAP(X_W) SS_TAP(X_ENTER));
        break;
        case ST_M_vim_sp: // vim :sp without enter
            SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_ESCAPE) SS_LSFT(SS_TAP(X_SEMICOLON)) SS_TAP(X_S) SS_TAP(X_P));
        break;
        case ST_M_vim_vs:   // vim :vs without enter
            SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_ESCAPE) SS_LSFT(SS_TAP(X_SEMICOLON)) SS_TAP(X_V) SS_TAP(X_S));
        break;
        case ST_M_vim_sp_e: // vim :sp with enter
            SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_ESCAPE) SS_LSFT(SS_TAP(X_SEMICOLON)) SS_TAP(X_S) SS_TAP(X_P) SS_TAP(X_ENTER));
        break;
        case ST_M_vim_vs_e: // vim :vs with enter
            SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_ESCAPE) SS_LSFT(SS_TAP(X_SEMICOLON)) SS_TAP(X_V) SS_TAP(X_S) SS_TAP(X_ENTER));
        break;
        case ST_M_double_colon:
            SEND_STRING("::");
        break;
        case ST_M_enable_bunny_hop:
            enable_bunnyhop = !enable_bunnyhop;
        break;
        case ST_M_brightness_up:
            rgblight_increase_val_noeeprom();
        break;
        case ST_M_brightness_down:
            rgblight_decrease_val_noeeprom();
        break;
        case ST_M_hue_up:
            rgblight_increase_hue_noeeprom();
        break;
        case ST_M_hue_down:
            rgblight_decrease_hue_noeeprom();
        break;
        case ST_M_sat_up:
            rgblight_increase_sat_noeeprom();
        break;
        case ST_M_sat_down:
            rgblight_decrease_sat_noeeprom();
        break;
        case ST_M_mode_up:
            rgblight_step_noeeprom();
        break;
        case ST_M_mode_down:
            rgblight_step_reverse_noeeprom();
        break;
        case ST_M_rgb_snake:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 1);
        break;
        case ST_M_rgb_twinkle:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_TWINKLE + 3);
        break;
        case ST_M_rgb_knight:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 1);
        break;
        case ST_M_toggle_rgb:
            rgb_show = !rgb_show;
        break;
        case ST_M_led_timeout_30s:
            rgb_time_out_value = 30000;
        break;
        case ST_M_led_timeout_1m:
            rgb_time_out_value = 60000;
        break;
        case ST_M_led_timeout_5m:
            rgb_time_out_value = 300000;
        break;
        case ST_M_led_timeout_10m:
            rgb_time_out_value = 600000;
        break;
        case ST_M_mac_mode_toggle:
            mac_mode = !mac_mode;
            manage_mac_mode_fn();
        break;
        case ST_M_combo_toggle:
            combo_toggle();
            combos_on = is_combo_enabled();
        break;
        case ST_M_colemak_mode_toggle:
            colemak_mode = !colemak_mode;
            if(colemak_mode){
                layer_on(Layer_colemak);
            }else{
                layer_off(Layer_colemak);
            }
        break;
        case ST_M_password_bypass:
            password_bypass = !password_bypass;
        break;
        case RAW_HID_M_1:
            SEND_STRING("about to send hid. ");
            simple_hid_test_send_key(&trackball, 0x0a);
            SEND_STRING("send hid. ");
        case RAW_HID_TB_DPI_UP:
            raw_hid_set_setting(&trackball, HID_RAW_TB_S_DPI, 0x01);
        break;
        case RAW_HID_TB_DPI_DOWN:
            raw_hid_set_setting(&trackball, HID_RAW_TB_S_DPI, 0x02);
        break;
        case RAW_HID_TB_DPI_DEFAULT:
            raw_hid_set_setting(&trackball, HID_RAW_TB_S_DPI, 0x03);
        break;
        case RAW_HID_TB_SCROLL_UP:
            raw_hid_set_setting(&trackball, HID_RAW_TB_S_SCROLL, 0x01);
        break;
        case RAW_HID_TB_SCROLL_DOWN:
            raw_hid_set_setting(&trackball, HID_RAW_TB_S_SCROLL, 0x02);
        break;
        case RAW_HID_TB_SCROLL_DEFAULT:
            raw_hid_set_setting(&trackball, HID_RAW_TB_S_SCROLL, 0x03);
        break;
        case RAW_HID_TB_SCROLL_INVERT:
            raw_hid_set_setting(&trackball, HID_RAW_TB_S_SCROLL, 0x04);
        break;
    }
    }

    switch (keycode) {
        case ST_M_bunny_hop:
            use_bunnyhop = record->event.pressed;
            if(!enable_bunnyhop){
                record->event.pressed ? SEND_STRING(SS_DOWN(X_SPACE)) : SEND_STRING(SS_UP(X_SPACE));
            }
        break;
        case RAW_HID_TB_DRAG_SCROLL:
            raw_hid_custom_key(&trackball, 0x01, record->event.pressed);
        break;
        return false;
    }
    return true;
}

void manage_mac_mode_fn(void){
    if(mac_mode){
        layer_move(Layer_mac_main);
    }else{
        layer_move(Layer_main);
    }
    if(colemak_mode){ // reset the colemak mode
        layer_on(Layer_colemak);
    }
}
