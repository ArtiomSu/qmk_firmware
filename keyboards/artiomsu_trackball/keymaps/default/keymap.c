#include QMK_KEYBOARD_H
#include "quantum.h"

#define Layer_main 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [Layer_main] = LAYOUT(
            KC_A
    )
};

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(400);
}
