#include "sharedDefines.h"

bool keep_shortcuts_active = false;
bool rgb_timed_out = false;
uint32_t rgb_time_out_options[RGB_MAX_OPTIONS] = {30000, 60000, 300000, 600000};
char rgb_time_out_options_dict[RGB_MAX_OPTIONS][4] = {"30s\0", "1m\0", "5m\0", "10m\0"};
uint32_t rgb_time_out_index = 0;
uint32_t rgb_timeout_counter = 0;

uint8_t count_down_to_boot = 32;
bool about_to_boot = false;

void keyboard_post_init_user(void) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_TWINKLE + 3);
    rgblight_sethsv_noeeprom(13, 250, 100);
    expressions_buffer[0] = '\0';
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

void oled_write_led_state(void){
    led_t led_state = host_keyboard_led_state();
    uint8_t buff_size = oled_max_chars();
    char buff[buff_size];
    snprintf(buff, buff_size, "%s%s%s%s",
        led_state.num_lock ? " NUM" : " ",
        led_state.caps_lock ? " CAPS" : " ",
        led_state.scroll_lock ? " SCROLL" : " ",
        "                                   "
    );
    oled_write_P(buff, false);
}

void oled_write_led_status(void){
    uint8_t buff_size = oled_max_chars();
    char buff[buff_size];
    snprintf(buff, buff_size, " ArtiomSu Mode-> %d ",
        rgblight_get_mode()
    );
    oled_write_P(buff, false);
    char buff2[buff_size];
    snprintf(buff2, buff_size, "\n Hue-> %d St-> %d",
        rgblight_get_hue(),
        rgblight_get_sat()
    );
    oled_write_P(buff2, false);
    char buff3[buff_size];
    snprintf(buff3, buff_size, "\n Val-> %d Tm-> %s",
        rgblight_get_val(),
        rgb_time_out_options_dict[rgb_time_out_index]
    );
    oled_write_P(buff3, false);
}

void oled_write_led_shortcuts(void){
    uint8_t buff_size = oled_max_chars();
    char buff[buff_size];
    snprintf(buff, buff_size, " Shortcuts   %s",
        rgb_time_out_options_dict[rgb_time_out_index]
    );
    oled_write_P(buff, false);
    oled_write_P(PSTR("\n F2 BOOT FLASH\n"), false);
    char buff2[buff_size];
    snprintf(buff2, buff_size, " S Sat-> %d Tm T/R\n",
        rgblight_get_sat()
    );
    oled_write_P(buff2, false);
    oled_write_P(PSTR(""), false);
}

bool oled_task_user(void) {
    // The boot is delayed so that the screen has time to update
    if(about_to_boot){
        render_logo();
        oled_write_P(PSTR("    Mounting To PC "), false);
        count_down_to_boot--;
        if(rgblight_get_mode() != RGBLIGHT_MODE_STATIC_LIGHT){
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(0, 250, 100);
        }
        if(count_down_to_boot == 0){
            reset_keyboard();
        }
        return false;
    }

    switch (get_highest_layer(layer_state)) {
        case Layer_main:
            oled_write_led_status();
            oled_write_P(PSTR("\n"), false);
            if(keep_shortcuts_active){
                keep_shortcuts_active = false;
                layer_move(Layer_shortcuts);
            }
            break;
        case Layer_shortcuts:
            oled_write_led_shortcuts();
            break;
        case Layer_calc:
            oled_write_P(PSTR(" Calculator\n"), false);
            char pres[32];
            sprintf(pres, " Precision %d\n", decimal_point_pressision);
            oled_write_P(pres, false);
            if(expressions_buffer[0] == '\0'){
                oled_write_P(" Enter Your Equation", false);
            }else{
                oled_write_P(" ", false);
                oled_write_P(expressions_buffer, false);
            }
            oled_write_P(PSTR("\n"), false);
            break;
        default:
            render_logo();
    }
    oled_write_led_state();
    return false;
}

void matrix_scan_user(void) {
  uint32_t current_timer_value = timer_read32();

  if(rgb_timeout_counter == 0){ // this is reset in macros
      rgb_timeout_counter = current_timer_value;
  }

  if(!rgb_timed_out){
      if(timer_elapsed32(rgb_timeout_counter) > rgb_time_out_options[rgb_time_out_index]){
          rgb_timed_out = true;
          rgb_timeout_counter = current_timer_value;
      }
  }

  if(rgb_timed_out){
    if(rgblight_is_enabled()){
        rgblight_disable_noeeprom();
    }
  }else{
    if(!rgblight_is_enabled()){
        rgblight_enable_noeeprom();
    }
  }

  if(rgblight_is_enabled()){
    if(!is_oled_on()){
        oled_on();
    }
  }else{
    if(is_oled_on()){
        oled_off();
    }
  }

}
