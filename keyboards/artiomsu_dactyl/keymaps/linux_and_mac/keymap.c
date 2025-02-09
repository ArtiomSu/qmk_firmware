#include "sharedDefines.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [Layer_main] = LAYOUT_5x7(
        // left hand
        LCTL(KC_LALT),          KC_1,               KC_2,               KC_3,           KC_4,           KC_5,           KC_MINUS,
        KC_TAB,                 KC_Q,               KC_W,               KC_E,           KC_R,           KC_T,           LCTL(LSFT(KC_LGUI)),
        LT(Layer_mouse,KC_TAB), KC_A,               KC_S,    LT(Layer_track_ball,KC_D), KC_F,           KC_G,           KC_HYPR,
        KC_LSFT,                KC_Z,               KC_X,               KC_C,           LSFT_T(KC_V),   KC_B,
        KC_LCTL,                KC_LALT,            LCTL(KC_LGUI),      LSFT(KC_LGUI),

        LT(Layer_symbols,KC_BACKSPACE), LGUI_T(KC_DELETE),
        LCTL_T(KC_HOME), LSFT(KC_PRINT_SCREEN),
        LCTL(KC_SPACE), KC_PRINT_SCREEN,

        //# right hand ###################################################################################################################
        KC_EQUAL,               KC_6,               KC_7,               KC_8,               KC_9,           KC_0,                   LSFT(KC_ENTER),
        KC_F2,                  KC_Y,               KC_U,               KC_I,               KC_O,           KC_P,                   ST_MACRO_SSH,
        KC_F4,                  KC_H,               KC_J,               KC_K,               KC_L,           KC_SEMICOLON,           KC_RALT,
                                KC_N,               LSFT_T(KC_M),       KC_COMMA,           KC_DOT,         KC_SLASH,               KC_RCTL,
                                                                        LCTL(LSFT(KC_LGUI)),XXXXXXX,        QK_CAPS_WORD_TOGGLE,    QK_LEAD,

        LT(Layer_macros,KC_ENTER), LT(Layer_nav,KC_SPACE),
        KC_PAGE_UP, LSFT_T(KC_ESCAPE),
        KC_PAGE_DOWN, ST_MACRO_VIM_wq
    ),
    [Layer_mac_main] = LAYOUT_5x7(
        // left hand
        LCTL(KC_LALT),          KC_1,               KC_2,               KC_3,               KC_4,           KC_5,           KC_MINUS,
        KC_TAB,                 KC_Q,               KC_W,               KC_E,               KC_R,           KC_T,           LCTL(LSFT(KC_LGUI)),
        LT(Layer_mouse,KC_TAB), KC_A,               KC_S,       LT(Layer_track_ball,KC_D),  KC_F,           KC_G,           KC_HYPR,
        KC_LSFT,                KC_Z,               KC_X,               KC_C,               LSFT_T(KC_V),   KC_B,
        KC_LGUI,                KC_LALT,            LCTL(KC_LGUI),      LSFT(KC_LGUI),

        LT(Layer_mac_symbols,KC_BACKSPACE), LCTL_T(KC_DELETE),
        LGUI_T(KC_HOME), LSFT(KC_PRINT_SCREEN),
        LCTL(KC_SPACE), LCTL(LGUI(LSFT(KC_4))),

        //# right hand ###################################################################################################################
        KC_EQUAL,               KC_6,               KC_7,               KC_8,               KC_9,           KC_0,                   LSFT(KC_ENTER),
        KC_F2,                  KC_Y,               KC_U,               KC_I,               KC_O,           KC_P,                   ST_MACRO_SSH,
        KC_F4,                  KC_H,               KC_J,               KC_K,               KC_L,           KC_SEMICOLON,           KC_RALT,
                                KC_N,               LSFT_T(KC_M),       KC_COMMA,           KC_DOT,         KC_SLASH,               KC_RCTL,
                                                                        LCTL(LSFT(KC_LGUI)),XXXXXXX,        QK_CAPS_WORD_TOGGLE,    QK_LEAD,

        LT(Layer_macros,KC_ENTER), LT(Layer_nav, KC_SPACE),
        KC_PAGE_UP, LSFT_T(KC_ESCAPE),
        KC_PAGE_DOWN, ST_MACRO_VIM_wq
    ),
    [Layer_colemak] = LAYOUT_5x7(
        // left hand
        _______,    _______,    _______,    _______,    _______,        _______,        _______,
        _______,    KC_Q,       KC_W,       KC_F,       KC_P,           KC_B,           _______,
        _______,    KC_A,       KC_R,       KC_S,       KC_T,           KC_G,           _______,
        _______,    KC_Z,       KC_X,       KC_C,       LSFT_T(KC_D),   KC_V,
        _______,    _______,    _______,    _______,

        _______,    _______,
        _______,    _______,
        _______,    _______,

        //# right hand ###################################################################################################################
        _______,    _______,    _______,    _______,    _______,        _______,        _______,
        _______,    KC_J,       KC_L,       KC_U,       KC_Y,           KC_SEMICOLON,   _______,
        _______,    KC_M,       KC_N,       KC_E,       KC_I,           KC_O,           _______,
                    KC_K,       LSFT_T(KC_H),KC_COMMA,  KC_DOT,         KC_SLASH,       _______,
                                            _______,    _______,        _______,        _______,

        _______,    _______,
        _______,    _______,
        _______,    _______
    ),
    [Layer_symbols] = LAYOUT_5x7(
        // left hand
        LSFT(KC_GRAVE),     KC_F1,          KC_F2,              KC_F3,                      KC_F4,              KC_F5,              KC_F11,
        KC_MS_BTN5,         KC_GRAVE,       KC_QUOTE,           LSFT(KC_QUOTE),             LSFT(LCTL(KC_C)),   LSFT(LCTL(KC_V)),   KC_CIRC,
        KC_MS_BTN4,         KC_EXLM,        LSFT(KC_2),         LSFT(KC_3),                 KC_DLR,             KC_PERC,            KC_CIRC,
        KC_LSFT,            ST_M_n_equal,   KC_AMPR,            LSFT(KC_NONUS_BACKSLASH),   LSFT(KC_NONUS_HASH),KC_ASTR,
        LALT(KC_LCTL),      ST_M_n_equal_2, LCTL(KC_X),         LCTL(KC_C),                 //LCTL(KC_V),

        _______,    _______,
        _______,    _______,
        _______,    _______,

        //# right hand ###################################################################################################################
        KC_F12,             KC_F6,          KC_F7,              KC_F8,                      KC_F9,              KC_F10,             KC_F13,
        _______,            KC_LABK,        KC_PLUS,            KC_MINUS,                   KC_RABK,            KC_EQUAL,           _______,
        _______,            KC_ASTR,        KC_LBRC,            KC_RBRC,                    KC_UNDS,            KC_QUES,            _______,
                            KC_AMPR,        KC_LCBR,            KC_RCBR,                    KC_DOT,             KC_NONUS_BACKSLASH, KC_LSFT,
                                                                LSFT(KC_0),                 ST_M_l_equal,       ST_M_g_equal,       KC_LALT,

        KC_NONUS_HASH, KC_SEMICOLON,
        _______, LSFT(KC_SEMICOLON),
        _______, _______
    ),
    [Layer_mac_symbols] = LAYOUT_5x7(
        // left hand
        LSFT(KC_GRAVE),     KC_F1,          KC_F2,              KC_F3,                      KC_F4,              KC_F5,              KC_F11,
        KC_MS_BTN5,         KC_GRAVE,       KC_QUOTE,           LSFT(KC_2),                 LGUI(LCTL(KC_C)),   LGUI(LCTL(KC_V)),   KC_CIRC,
        KC_MS_BTN4,         KC_EXLM,        LSFT(KC_QUOTE),     LSFT(KC_3),                 KC_DLR,             KC_PERC,            KC_CIRC,
        KC_LSFT,            ST_M_n_equal,   KC_AMPR,            LSFT(KC_NONUS_HASH),        LSFT(KC_GRAVE),     KC_ASTR,
        LALT(KC_LCTL),      ST_M_n_equal_2, LGUI(KC_X),         LGUI(KC_C),                 //LGUI(KC_V),

        _______,    _______,
        _______,    _______,
        _______,    _______,

        //# right hand ###################################################################################################################
        KC_F12,             KC_F6,          KC_F7,              KC_F8,                      KC_F9,              KC_F10,             KC_F13,
        _______,            KC_LABK,        KC_PLUS,            KC_MINUS,                   KC_RABK,            KC_EQUAL,           _______,
        _______,            KC_ASTR,        KC_LBRC,            KC_RBRC,                    KC_UNDS,            KC_QUES,            _______,
                            KC_AMPR,        KC_LCBR,            KC_RCBR,                    KC_DOT,             KC_NONUS_HASH,      KC_LSFT,
                                                                LSFT(KC_0),                 ST_M_l_equal,       ST_M_g_equal,       KC_LALT,

        LALT(KC_3), KC_SEMICOLON,
        _______, LSFT(KC_SEMICOLON),
        _______, _______
    ),
    [Layer_macros] = LAYOUT_5x7(
        // left hand
        ST_M_led_timeout_30s,   _______,            _______,                    _______,                _______,          _______,                  ST_M_colemak_mode_toggle,
        ST_M_led_timeout_1m,    ST_M_vim_q,         ST_M_vim_w,                 _______,                LCTL(KC_V),       LCTL(KC_B),               _______,
        ST_M_led_timeout_5m,    _______,            _______,                    _______,                ST_M_vim_sp,      ST_M_vim_vs,              _______,
        ST_M_led_timeout_10m,   _______,            _______,                    _______,                ST_M_vim_sp_e,    ST_M_vim_vs_e,
        _______,                ST_M_combo_toggle,  _______,                    _______,

        KC_SPACE, LALT(KC_ENTER),
        _______,    _______,
        _______,    _______,

        //# right hand ###################################################################################################################
        KC_KB_MUTE,             _______,            _______,                    _______,                _______,          _______,                  QK_BOOT,
        KC_KB_VOLUME_UP,        _______,            _______,                    _______,                _______,          ST_M_password_bypass,     ST_M_enable_bunny_hop,
        KC_KB_VOLUME_DOWN,      LCTL(KC_H),         LCTL(KC_J),                 LCTL(KC_K),             LCTL(KC_L),       _______,                  _______,
                                _______,            ST_M_mac_mode_toggle,       _______,                _______,          _______,                  _______,
                                                                                _______,                _______,          _______,                  _______,

        _______, _______,
        KC_BRIGHTNESS_UP, _______,
        KC_BRIGHTNESS_DOWN, ST_M_double_colon
    ),
    [Layer_gaming] = LAYOUT_5x7(
        // left hand
        KC_0,               KC_1,           KC_2,               KC_3,           KC_4,           KC_5,           KC_6,
        KC_ESCAPE,          KC_8,           KC_Q,               KC_W,           KC_E,           KC_R,           KC_7,
        KC_TAB,             KC_9,           KC_A,               KC_S,           KC_D,           KC_F,           KC_ENTER,
        KC_LSFT,            KC_LSFT,        KC_X,               KC_C,           KC_V,           KC_G,
        KC_LCTL,            KC_Z,           KC_I,               KC_C,           //KC_B,

        ST_M_bunny_hop,KC_LCTL,
        KC_O,    KC_Y,
        KC_M,    KC_U,

        //# right hand ###################################################################################################################
        KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_HOME,
        KC_F6,          KC_KP_ASTERISK, KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_MINUS,    KC_END,
        KC_F5,          KC_KP_SLASH,    KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_PLUS,     KC_DELETE,
                        KC_KP_ENTER,    KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_UP,          TO(Layer_main),
                                                        KC_KP_0,        KC_LEFT,        KC_DOWN,        KC_RIGHT,

        KC_NUM_LOCK, KC_INSERT,
        KC_F4,    KC_F2,
        KC_F3,    KC_F1
    ),
    [Layer_mouse] = LAYOUT_5x7(
        // left hand
        QK_BOOT,    _______,    _______,            _______,        _______,    _______,            _______,
        _______,    _______,    _______,            _______,        _______,    ST_M_rgb_twinkle,   _______,
        _______,    _______,    ST_M_rgb_snake,     ST_M_rgb_knight,_______,    _______,            _______,
        _______,    _______,    _______,            _______,        KC_NUM,     KC_CAPS,
        _______,    _______,    _______,            _______,

        KC_MS_ACCEL0,KC_MS_ACCEL1,
        KC_MS_ACCEL2,    _______,
        _______,         _______,

        //# right hand ###################################################################################################################
        _______,    _______,    _______,            _______,        _______,    _______,            ST_M_toggle_rgb,
        _______,    _______,    _______,            _______,        _______,    ST_M_mode_up,       ST_M_mode_down,
        _______,    KC_MS_LEFT, KC_MS_DOWN,         KC_MS_UP,       KC_MS_RIGHT,ST_M_hue_up,        ST_M_hue_down,
                    _______,    _______,            _______,        _______,    ST_M_sat_up,        ST_M_sat_down,
                                                    _______,        _______,    ST_M_brightness_up, ST_M_brightness_down,

        KC_MS_BTN2, KC_MS_BTN1,
        _______,    KC_MS_BTN3,
        _______,    _______
    ),
    [Layer_nav] = LAYOUT_5x7(
        // left hand
        _______,    PB_1,       PB_2,       PB_3,       PB_4,       PB_5,           DM_RSTP,
        _______,    PB_11,      PB_12,      PB_13,      PB_14,      DM_PLY1,        DM_REC1,
        _______,    PB_21,      PB_22,      PB_23,      PB_24,      DM_PLY2,        DM_REC2,
        _______,    PB_31,      PB_32,      _______,    _______,    PB_15,
        _______,    _______,    _______,    _______,

        _______,    _______,
        _______,    _______,
        _______,    _______,

        //# right hand ###################################################################################################################
        _______,    PB_6,       PB_7,       PB_8,       PB_9,       PB_10,              _______,
        _______,    PB_16,      PB_17,      PB_18,      PB_19,      PB_20,              _______,
        _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   PB_30,              _______,
                    _______,    LSFT(KC_9), LSFT(KC_0), _______,    _______,            _______,
                                            _______,    _______,    _______,            _______,

        _______,    _______,
        _______,    _______,
        _______,    _______
    ),
    [Layer_track_ball] = LAYOUT_5x7(
        // left hand
        _______,    RAW_HID_M_1,    _______,            _______,    RAW_HID_TB_SCROLL_UP,    RAW_HID_TB_SCROLL_DOWN,  RAW_HID_TB_SCROLL_DEFAULT,
        _______,    _______,    _______,            _______,        RAW_HID_TB_SCROLL_INVERT,_______,                 RAW_HID_TB_DPI_DEFAULT,
        _______,    KC_MS_BTN4, KC_MS_BTN5,         _______,        RAW_HID_TB_DRAG_SCROLL,  RAW_HID_TB_DPI_UP,       RAW_HID_TB_DPI_DOWN,
        _______,    _______,    _______,            _______,        KC_MS_BTN3,              _______,
        _______,    _______,    _______,            _______,

        KC_MS_BTN1, KC_MS_BTN2,
        _______,    _______,
        _______,    _______,

        //# right hand ###################################################################################################################
        _______,    _______,    _______,            _______,        _______,       _______,            _______,
        _______,    _______,    KC_MS_WH_UP,        _______,        _______,       _______,            _______,
        _______,    _______,    KC_MS_BTN3,         _______,        KC_MS_BTN4,    KC_MS_BTN5,         _______,
                    _______,    KC_MS_WH_DOWN,      _______,        _______,       _______,            _______,
                                                    _______,        _______,       _______,            _______,

        KC_MS_BTN2, KC_MS_BTN1,
        _______,    _______,
        _______,    _______
    )
};

/*
    [clean] = LAYOUT_5x7(
        // left hand
        _______,    _______,    _______,            _______,        _______,    _______,            _______,
        _______,    _______,    _______,            _______,        _______,    _______,            _______,
        _______,    _______,    _______,            _______,        _______,    _______,            _______,
        _______,    _______,    _______,            _______,        _______,    _______,
        _______,    _______,    _______,            _______,

        _______,    _______,
        _______,    _______,
        _______,    _______,

        //# right hand ###################################################################################################################
        _______,    _______,    _______,            _______,        _______,    _______,            _______,
        _______,    _______,    _______,            _______,        _______,    _______,            _______,
        _______,    _______,    _______,            _______,        _______,    _______,            _______,
                    _______,    _______,            _______,        _______,    _______,            _______,
                                                    _______,        _______,    _______,            _______,

        _______,    _______,
        _______,    _______,
        _______,    _______
    )
*/
