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
#include "quantum.h"

#define Layer_main 0
#define Layer_settings_dpi 1
#define Layer_settings_scroll 2
#define Layer_settings 3

enum custom_keycodes {
    COMPILE = SAFE_RANGE,
    DPI_UP,
    DPI_DOWN,
    DPI_400,
    DRAG_SCROLL,
    SCROLL_UP,
    SCROLL_DOWN,
    SCROLL_DEFAULT,
    SCROLL_INVERT_TOGGLE
};

uint16_t custom_dpi = 400;
const uint16_t step_size = 200;
const uint16_t minimum_dpi = 200;
const uint16_t max_dpi = 12000;

bool set_scrolling = false;
const float scroll_divisor_default = 5.0;
float scroll_divisor = scroll_divisor_default;
const float scroll_divisor_min = 1.0;
const float scroll_divisor_max = 20.0;

float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

const bool scroll_invert_default = true;
bool scroll_invert = scroll_invert_default;

// this is just to make the keymap lool neeter.
#define LT_SCROLL LT(Layer_settings_scroll, KC_BTN4)
#define LT_DPI LT(Layer_settings_dpi, KC_BTN5)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [Layer_main] = LAYOUT(
            LT_SCROLL,      LT_DPI,      DRAG_SCROLL,     KC_BTN2,
            KC_BTN1,                                      KC_BTN3
    ),
    [Layer_settings_dpi] = LAYOUT(
            DPI_UP,         _______,     _______,         DPI_400,
            DPI_DOWN,                                     _______
    ),
    [Layer_settings_scroll] = LAYOUT(
            _______,       SCROLL_UP,   _______,          SCROLL_DEFAULT,
            SCROLL_DOWN,                                  SCROLL_INVERT_TOGGLE
    ),
    [Layer_settings] = LAYOUT(
            QK_BOOT,       COMPILE,     _______,          _______,
            _______,                                      _______
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

void manageScroll(bool up){
    float step = 1.0;
    float s = scroll_divisor;
    // if the scroll divisor is increased it will actually make the scrolling slower so do the oposite in this case for up so it makes a bit more sense.
    if(!up){
        s+=step;
    }else{
        if(s > step){
            s-=step;
        }
    }

    if(s < scroll_divisor_min){
        s = scroll_divisor_min;
    }
    if(s > scroll_divisor_max){
        s = scroll_divisor_max;
    }

    scroll_divisor = s;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COMPILE:
            if (record->event.pressed) {
                SEND_STRING("cd /temp/GIT/qmk_firmware && make clean && qmk flash -kb ploopy_adept -km default");
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
        case DRAG_SCROLL:
            // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
            set_scrolling = record->event.pressed;
            if (record->event.pressed) {
                layer_on(Layer_settings);
            }else{
                layer_off(Layer_settings);
            }
        break;
        case SCROLL_DEFAULT:
            if (record->event.pressed) {
                scroll_divisor = scroll_divisor_default;
            }
        break;
        case SCROLL_UP:
            if (record->event.pressed) {
                manageScroll(true);
            }
        break;
        case SCROLL_DOWN:
            if (record->event.pressed) {
                manageScroll(false);
            }
        break;
        case SCROLL_INVERT_TOGGLE:
            if (record->event.pressed) {
                scroll_invert = !scroll_invert;
            }
        break;
    }
    return true;
};

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(400);
    scroll_divisor = scroll_divisor_default;
    scroll_invert = scroll_invert_default;
}

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / scroll_divisor;
        scroll_accumulated_v += (float)mouse_report.y / scroll_divisor;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        if(scroll_invert){
            mouse_report.v = -(int8_t)scroll_accumulated_v;
        }else{
            mouse_report.v = (int8_t)scroll_accumulated_v;
        }

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}
