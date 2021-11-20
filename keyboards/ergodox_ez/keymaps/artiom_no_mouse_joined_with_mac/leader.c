#include "sharedDefines.h"
#include "pointing_device.h"

int bunny_hop_delay_counter = 0;
bool leader_key_is_running = false;

uint16_t scroll_delay_timer;

LEADER_EXTERNS();
int did_leader_succeed;

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    did_leader_succeed = leading = false;

    SEQ_ONE_KEY(KC_T) {
      // Anything you can do in a macro.
      SEND_STRING(SS_DOWN(X_LGUI)  SS_TAP(X_ENTER) SS_UP(X_LGUI)  SS_DELAY(1000) "timer ");
      did_leader_succeed = true;
    } else
    SEQ_TWO_KEYS(KC_B, KC_I) {
      SEND_STRING("https://www.bing.com/images/search?q=");
      did_leader_succeed = true;
    } else
    SEQ_TWO_KEYS(KC_T, KC_O) {
      SEND_STRING("10.0.0.69:19009" SS_TAP(X_ENTER) SS_DELAY(700) "pirate" SS_TAP(X_TAB));
      did_leader_succeed = true;
    } else
    SEQ_ONE_KEY(KC_C) {
      SEND_STRING("code ." SS_TAP(X_ENTER));
      did_leader_succeed = true;
    } else
    SEQ_ONE_KEY(KC_RIGHT) { //wake leds
        rgb_timed_out = false;
        did_leader_succeed = true;
    } else
    SEQ_TWO_KEYS(KC_RIGHT, KC_RIGHT) { //toggle leds on/off
        rgb_show = !rgb_show;
        did_leader_succeed = true;
    } else
    SEQ_THREE_KEYS(KC_RIGHT, KC_RIGHT, KC_RIGHT){ //turn on leds and wake and reset brightness
        rgb_timed_out = false;
        rgb_show = true;
        brightness_amount = 0;
        hue_amount = 0;
        main_layer_brightness = true;
        did_leader_succeed = true;
    } else
    SEQ_ONE_KEY(KC_E) {
      SEND_STRING(SS_LSFT("'") "t80search_bot -t");
      did_leader_succeed = true;
    } else
    SEQ_TWO_KEYS(KC_G, KC_G) {
      mac_mode = false; // gaming layer currently always returns to Layer_main. shouldn't be a problem since I wouldn't be launching it from mac mode ever.
      layer_move(Layer_gaming);
      did_leader_succeed = true;
    } else
    SEQ_TWO_KEYS(KC_C, KC_O) {
      SEND_STRING("cd /media/veracrypt1/GIT/qmk_firmware && make clean && make ergodox_ez:artiom_no_mouse_joined_with_mac");
      did_leader_succeed = true;
    }
    leader_end();
  }

  if(rgb_sync_to_timer != g_rgb_timer){
        rgb_sync_to_timer = g_rgb_timer;
        if(!rgb_timed_out){ // update rgb timeout
            if(timeout_counter > rgb_time_out_value){
                timeout_counter = 0;
                rgb_timed_out = true;
            }
            timeout_counter++;
        }
  }

  if(enable_bunnyhop && use_bunnyhop){
       if(bunny_hop_delay_counter <= 0){
        srand(timeout_counter);
        SEND_STRING(SS_TAP(X_SPACE));
        bunny_hop_delay_counter = rand() % 10;
       }
       bunny_hop_delay_counter --;
  }

  if(scrollwheel_up_on || scrollwheel_down_on){
    if(timer_elapsed(scroll_delay_timer) > 100){ //call this every 100ms
        report_mouse_t currentReport = pointing_device_get_report();
        currentReport.v = scrollwheel_up_on ? 1 : -1;
        pointing_device_set_report(currentReport);
        pointing_device_send();
        scroll_delay_timer = timer_read();
    }
  }

}

void leader_start(void) {
    leader_key_is_running = true;
}

void leader_end(void) {
    leader_key_is_running = false;
}
