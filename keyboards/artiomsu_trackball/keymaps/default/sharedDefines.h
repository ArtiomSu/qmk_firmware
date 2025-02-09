#ifndef SHAREDDEFINES_H
#define SHAREDDEFINES_H

#include QMK_KEYBOARD_H
#include "quantum.h"

extern uint16_t custom_dpi;
extern const uint16_t step_size;
extern const uint16_t minimum_dpi;
extern const uint16_t max_dpi;

extern bool set_scrolling;
extern const float scroll_divisor_default;
extern float scroll_divisor;
extern const float scroll_divisor_min;
extern const float scroll_divisor_max;

extern float scroll_accumulated_h;
extern float scroll_accumulated_v;

extern const bool scroll_invert_default;
extern bool scroll_invert;

void manageDPI(bool up);
void manageScroll(bool up);

#endif
