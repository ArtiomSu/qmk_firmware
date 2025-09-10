#ifndef SHARED_DEFINES_PLOOPY_ADEPT
#define SHARED_DEFINES_PLOOPY_ADEPT

extern uint16_t custom_dpi;
extern const uint16_t step_size;
extern const uint16_t minimum_dpi;

extern bool set_scrolling;
extern bool set_scrolling_horizontal;
extern const float scroll_divisor_default;
extern float scroll_divisor;
extern const float scroll_divisor_min;
extern const float scroll_divisor_max;

void manageDPI(bool up);
void manageScroll(bool up);


#endif
