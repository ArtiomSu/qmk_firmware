/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define Layer_main 0
#define Layer_settings 1

enum custom_keycodes {
    COMPILE = SAFE_RANGE,
    DPI_UP,
    DPI_DOWN,
    DPI_400
};

uint16_t custom_dpi = 400;
const uint16_t step_size = 200;
const uint16_t minimum_dpi = 200;
const uint16_t max_dpi = 12000;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [Layer_main] = LAYOUT(
            KC_BTN4, LT(Layer_settings, KC_BTN5), DRAG_SCROLL, KC_BTN2,
                        KC_BTN1, KC_BTN3
    ),
    [Layer_settings] = LAYOUT(
            DPI_UP, _______, DPI_400, QK_BOOT,
                        DPI_DOWN, COMPILE
    )
};

void manageDPI(bool up){
    uint16_t step = step_size;

    /* increase step size as we go further down
    from 200 to 1500 we need to do 14 steps
    from 1500 to 5000 we need to do 7 steps
    from 5000 to 12000 we need to do 7 steps

    so overall we need to do 28 steps from 200 to 12000
    whereas without this we would need to do 60 steps
    */

    if(custom_dpi > 1500){
        step = 500;
    }else if(custom_dpi > 5000){
        step = 1000;
    }

    if(up){
        custom_dpi+=step;
    }else{
        if(custom_dpi > step){
            custom_dpi-=step;
        }
    }

    if(custom_dpi < minimum_dpi){
        custom_dpi = minimum_dpi;
    }
    if(custom_dpi > max_dpi){
        custom_dpi = max_dpi;
    }
    pointing_device_set_cpi(custom_dpi);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COMPILE:
            if (record->event.pressed) {
                SEND_STRING("cd /temp/GIT/qmk_firmware && make clean && qmk flash -kb ploopyco/madromys -km layered");
            }
        break;
        case DPI_400:
            if (record->event.pressed) {
                pointing_device_set_cpi(400);
                custom_dpi=400;
            }
        break;
        case DPI_UP:
            if (record->event.pressed) {
                manageDPI(true);
            }
        break;
        case DPI_DOWN:
            if (record->event.pressed) {
                manageDPI(false);
            }
        break;

    }
    return true;
};

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(400);
}
