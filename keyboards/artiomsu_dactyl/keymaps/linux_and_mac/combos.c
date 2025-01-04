#include "sharedDefines.h"

//combos don't forget to edit COMBO_COUNT in config.h
enum combo_events {
    COMBO_LEFT_SQUARE_BRACKET,
    COMBO_RIGHT_SQUARE_BRACKET,
    COMBO_LEFT_CURLY_BRACKET,
    COMBO_RIGHT_CURLY_BRACKET,
    COMBO_LEFT_BRACKET,
    COMBO_RIGHT_BRACKET,
    COMBO_MINUS,
    COMBO_EQUALS,
    COMBO_LESS,
    COMBO_GREATER,
    COMBO_LESS_EQUALS,
    COMBO_GREATER_EQUALS,
    COMBO_LESS_EQUALS_EQUALS,
    COMBO_GREATER_EQUALS_EQUALS,
    COMBO_NOT_EQUALS,
    COMBO_NOT_EQUALS_EQUALS,
    COMBO_PIPE,
    COMBO_ASTARISK,
    COMBO_AMPERSTAND,
    COMBO_ROOT,
    COMBO_HASH,
    COMBO_ALT_F4,
    COMBO_SCROLL_UP,
    COMBO_SCROLL_DOWN
};

const uint16_t PROGMEM combo_left_square_bracket[] = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM combo_right_square_bracket[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM combo_left_curly_bracket[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_right_curly_bracket[] = {KC_L, KC_K, COMBO_END};
const uint16_t PROGMEM combo_left_bracket[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_right_bracket[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_equals[] = {KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM combo_minus[] = {KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM combo_less[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM combo_greater[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_less_equals[] = {KC_F, KC_U, COMBO_END};
const uint16_t PROGMEM combo_greater_equals[] = {KC_F, KC_O, COMBO_END};
const uint16_t PROGMEM combo_less_equals_equals[] = {KC_F, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_greater_equals_equals[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_not_equals[] = {KC_J, KC_A, COMBO_END};
const uint16_t PROGMEM combo_not_equals_equals[] = {KC_J, KC_S, COMBO_END};
const uint16_t PROGMEM combo_pipe[] = {KC_F, KC_I, COMBO_END};
const uint16_t PROGMEM combo_amperstand[] = {KC_F, KC_J, COMBO_END};
const uint16_t PROGMEM combo_astarisk[] = {KC_F, KC_K, COMBO_END};
const uint16_t PROGMEM combo_root[] = {KC_F, KC_SEMICOLON, COMBO_END};
const uint16_t PROGMEM combo_hash[] = {KC_F, KC_H, COMBO_END};
const uint16_t PROGMEM combo_alt_f4[] = {KC_F, KC_4, COMBO_END};
const uint16_t PROGMEM combo_scroll_up[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_scroll_down[] = {KC_E, KC_R, COMBO_END};

/* COMBOS VISUAL LAYOUT
    +-------------+
    | S | F | [   |
    | J | L | ]   |
    | S | D | {   |
    | L | K | }   |
    | D | F | (   |
    | J | K | )   |
    | 9 | 0 | =   |
    | 8 | 9 | -   |
    | U | I | <   |
    | I | O | >   |
    | F | U | <=  |
    | F | O | >=  |
    | F | Y | <== |
    | F | P | >== |
    | J | A | !=  |
    | J | S | !== |
    | F | I | |   |
    | F | J | &   |
    | F | K | *   |
    | F | ; | ~   |
    | F | H | #   |
    | F | 4 | Af4 |
    | W | E | Sup |
    | E | R | Sdw |
    +-------------+

*/

combo_t key_combos[] = {
    [COMBO_LEFT_SQUARE_BRACKET] = COMBO_ACTION(combo_left_square_bracket),
    [COMBO_RIGHT_SQUARE_BRACKET] = COMBO_ACTION(combo_right_square_bracket),
    [COMBO_LEFT_CURLY_BRACKET] = COMBO_ACTION(combo_left_curly_bracket),
    [COMBO_RIGHT_CURLY_BRACKET] = COMBO_ACTION(combo_right_curly_bracket),
    [COMBO_LEFT_BRACKET] = COMBO_ACTION(combo_left_bracket),
    [COMBO_RIGHT_BRACKET] = COMBO_ACTION(combo_right_bracket),
    [COMBO_MINUS] = COMBO_ACTION(combo_minus),
    [COMBO_EQUALS] = COMBO_ACTION(combo_equals),
    [COMBO_LESS] = COMBO_ACTION(combo_less),
    [COMBO_GREATER] = COMBO_ACTION(combo_greater),
    [COMBO_LESS_EQUALS] = COMBO_ACTION(combo_less_equals),
    [COMBO_GREATER_EQUALS] = COMBO_ACTION(combo_greater_equals),
    [COMBO_LESS_EQUALS_EQUALS] = COMBO_ACTION(combo_less_equals_equals),
    [COMBO_GREATER_EQUALS_EQUALS] = COMBO_ACTION(combo_greater_equals_equals),
    [COMBO_NOT_EQUALS] = COMBO_ACTION(combo_not_equals),
    [COMBO_NOT_EQUALS_EQUALS] = COMBO_ACTION(combo_not_equals_equals),
    [COMBO_PIPE] = COMBO_ACTION(combo_pipe),
    [COMBO_ASTARISK] = COMBO_ACTION(combo_astarisk),
    [COMBO_AMPERSTAND] = COMBO_ACTION(combo_amperstand),
    [COMBO_ROOT] = COMBO_ACTION(combo_root),
    [COMBO_HASH] = COMBO_ACTION(combo_hash),
    [COMBO_ALT_F4] = COMBO_ACTION(combo_alt_f4),
    [COMBO_SCROLL_UP] = COMBO_ACTION(combo_scroll_up),
    [COMBO_SCROLL_DOWN] = COMBO_ACTION(combo_scroll_down)
};

void process_combo_event(uint16_t combo_index, bool pressed) {

    if(rgb_timed_out){
        return;
    }

    switch(combo_index) {
    case COMBO_LEFT_SQUARE_BRACKET:
        pressed ? register_code16(KC_LBRC) : unregister_code16(KC_LBRC);
    break;
    case COMBO_RIGHT_SQUARE_BRACKET:
        pressed ? register_code16(KC_RBRC) : unregister_code16(KC_RBRC);
    break;
    case COMBO_LEFT_CURLY_BRACKET:
        pressed ? register_code16(KC_LCBR) : unregister_code16(KC_LCBR);
    break;
    case COMBO_RIGHT_CURLY_BRACKET:
        pressed ? register_code16(KC_RCBR) : unregister_code16(KC_RCBR);
    break;
    case COMBO_LEFT_BRACKET:
        pressed ? register_code16(LSFT(KC_9)) : unregister_code16(LSFT(KC_9));
    break;
    case COMBO_RIGHT_BRACKET:
        pressed ? register_code16(LSFT(KC_0)) : unregister_code16(LSFT(KC_0));
    break;
    case COMBO_MINUS:
        pressed ? register_code16(KC_MINUS) : unregister_code16(KC_MINUS);
    break;
    case COMBO_EQUALS:
        pressed ? register_code16(KC_EQUAL) : unregister_code16(KC_EQUAL);
    break;
    case COMBO_LESS:
        pressed ? register_code16(KC_LABK): unregister_code16(KC_LABK);
    break;
    case COMBO_GREATER:
        pressed ? register_code16(KC_RABK) : unregister_code16(KC_RABK);
    break;
    case COMBO_LESS_EQUALS:
        if (pressed) {
            tap_code16(KC_LABK);
            tap_code16(KC_EQUAL);
        }
    break;
    case COMBO_GREATER_EQUALS:
        if (pressed) {
            tap_code16(KC_RABK);
            tap_code16(KC_EQUAL);
        }
    break;
    case COMBO_LESS_EQUALS_EQUALS:
        if (pressed) {
            tap_code16(KC_LABK);
            tap_code16(KC_EQUAL);
            tap_code16(KC_EQUAL);
        }
    break;
    case COMBO_GREATER_EQUALS_EQUALS:
        if (pressed) {
            tap_code16(KC_RABK);
            tap_code16(KC_EQUAL);
            tap_code16(KC_EQUAL);
        }
    break;
    case COMBO_NOT_EQUALS:
        if (pressed) {
            tap_code16(KC_EXLM);
            tap_code16(KC_EQUAL);
        }
    break;
    case COMBO_NOT_EQUALS_EQUALS:
        if (pressed) {
            tap_code16(KC_EXLM);
            tap_code16(KC_EQUAL);
            tap_code16(KC_EQUAL);
        }
    break;
    case COMBO_PIPE:
        pressed ? register_code16(LSFT(KC_NONUS_BACKSLASH)) : unregister_code16(LSFT(KC_NONUS_BACKSLASH));
    break;
    case COMBO_ASTARISK:
        pressed ? register_code16(KC_ASTR) : unregister_code16(KC_ASTR);
    break;
    case COMBO_AMPERSTAND:
        pressed ? register_code16(KC_AMPR) : unregister_code16(KC_AMPR);
    break;
    case COMBO_ROOT:
        pressed ? register_code16(LSFT(KC_NONUS_HASH)) : unregister_code16(LSFT(KC_NONUS_HASH));
    break;
    case COMBO_HASH:
        pressed ? register_code16(KC_NONUS_HASH) : unregister_code16(KC_NONUS_HASH);
    break;
    case COMBO_SCROLL_UP:
        pressed ? register_code16(KC_MS_WH_UP) : unregister_code16(KC_MS_WH_UP);
    break;
    case COMBO_SCROLL_DOWN:
        pressed ? register_code16(KC_MS_WH_DOWN) : unregister_code16(KC_MS_WH_DOWN);
    break;
    case COMBO_ALT_F4:
        if(pressed){
            tap_code16(LALT(KC_F4));
        }
    }
}
