#include "sharedDefines.h"
// make clean && qmk flash -kb artiomsu_trackball -km default

#define Layer_main 0

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [Layer_main] = LAYOUT(
            KC_A
    )
};

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(400);
    scroll_divisor = scroll_divisor_default;
    scroll_invert = scroll_invert_default;
}

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
