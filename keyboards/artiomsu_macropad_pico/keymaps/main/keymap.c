#include "sharedDefines.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [Layer_main] = LAYOUT_artiomsu_macropad(
        LT(Layer_shortcuts, KC_MUTE), KC_KP_EQUAL, TO(Layer_calc), KC_BACKSPACE,
        KC_NUM_LOCK,     KC_KP_SLASH,    KC_KP_ASTERISK,     KC_KP_MINUS,
        KC_KP_7,         KC_KP_8,        KC_KP_9,            KC_KP_PLUS,
        KC_KP_4,         KC_KP_5,        KC_KP_6,
        KC_KP_1,         KC_KP_2,        KC_KP_3,
        KC_KP_0,         KC_KP_DOT,      KC_KP_ENTER
    ),
    [Layer_shortcuts] = LAYOUT_artiomsu_macropad(
		TO(Layer_main),  KC_F2,          BOOT_TRIGGER,       FLASH_MACRO,
        PB_10,           PB_11,          PB_12,              PB_13,
		PB_7,            PB_8,           PB_9,               PB_14,
		PB_4,            PB_5,           PB_6,
		PB_1,            PB_2,           PB_3,
		PB_20,           PB_21,          PB_22
    ),
    [Layer_calc] = LAYOUT_artiomsu_macropad( //hardware calculator
        L1_EXIT_LAYER,      L1_POWER,   L1_MOD,         L1_DELETE,
		L1_PRINT_EQUATION,  L1_SLASH,   L1_MULTIPLY,    L1_MINUS,
		L1_7,               L1_8,       L1_9,           L1_PLUS,
		L1_4,               L1_5,       L1_6,
		L1_1,               L1_2,       L1_3,
		L1_0,               L1_DOT,     L1_EQUALS
    )

};

bool encoder_update_user_Layer_calc(uint8_t index, bool clockwise) {
    switch (index){
        case 0:
            if (clockwise) {
                if(decimal_point_pressision < 10){
                    decimal_point_pressision++;
                }
            } else {
                if(decimal_point_pressision > 0){
                    decimal_point_pressision--;
                }
            }
            break;
        case 1:
            if (clockwise) {} else {}
            break;
        case 2:
            if (clockwise) {    write_char_to_buff('('); }
            else {              write_char_to_buff(')'); }
            break;
        case 3:
            if (clockwise) {}
            else {
                // delete the buffer
                expressions_buffer[0] = '\0';
                input_count = 0;
            }
            break;
        default:
            return true;
    }
    return false;
}

bool encoder_update_user_Layer_main(uint8_t index, bool clockwise) {
    switch (index){
        case 0:
            if (clockwise) {    tap_code(KC_VOLU);
            } else {            tap_code(KC_VOLD);}
            break;
        case 1:
            if (clockwise) {    rgblight_increase_val_noeeprom();
            } else {            rgblight_decrease_val_noeeprom();}
            break;
        case 2:
            if (clockwise) {    rgblight_increase_hue_noeeprom();
            } else {            rgblight_decrease_hue_noeeprom();}
            break;
        case 3:
            if (clockwise) {    rgblight_step_noeeprom();
            } else {            rgblight_step_reverse_noeeprom();}
            break;
        default:
            return true;
    }
    return false;
}

bool encoder_update_user_Layer_shortcuts(uint8_t index, bool clockwise) {
    switch (index){
        case 0:
            if (clockwise) {    rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 1);
            } else {            keep_shortcuts_active = true;}
            break;
        case 1:
            if (clockwise) {    rgblight_increase_sat_noeeprom();
            } else {            rgblight_decrease_sat_noeeprom();}
            break;
        case 2:
            if (clockwise) {
                if(rgb_time_out_index < RGB_MAX_OPTIONS -1){
                    rgb_time_out_index++;
                }
            } else {
                if(rgb_time_out_index > 0){
                    rgb_time_out_index--;
                }
            }
            break;
        case 3:
            if (clockwise) {    rgblight_mode_noeeprom(RGBLIGHT_MODE_TWINKLE + 3);
            } else {            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 1);}
            break;
        default:
            return true;
    }
    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    rgb_timed_out = false;
    rgb_timeout_counter=0;
    switch (get_highest_layer(layer_state)) {
        case Layer_main:
            return encoder_update_user_Layer_main(index, clockwise);
        case Layer_shortcuts:
            return encoder_update_user_Layer_shortcuts(index, clockwise);
        case Layer_calc:
            return encoder_update_user_Layer_calc(index, clockwise);
        default:
            return true;
    }
}
