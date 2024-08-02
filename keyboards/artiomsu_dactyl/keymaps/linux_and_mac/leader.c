#include "sharedDefines.h"

uint8_t bunny_hop_delay_counter = 0;
bool leader_key_is_running = false;

void leader_start_user(void) {
    leader_key_is_running = true;
    rgb_manage_leader(leader_key_is_running);
}

void leader_end_user(void) {

    if(leader_sequence_one_key(KC_T)) {
      // Anything you can do in a macro.
      SEND_STRING(SS_DOWN(X_LGUI)  SS_TAP(X_ENTER) SS_UP(X_LGUI)  SS_DELAY(1000) "timer ");
    } else if
    (leader_sequence_two_keys(KC_B, KC_I)) {
      SEND_STRING("https://www.bing.com/images/search?q=");
    } else if
    (leader_sequence_two_keys(KC_T, KC_O)) {
      SEND_STRING("10.0.0.42:19009" SS_TAP(X_ENTER) SS_DELAY(700) "pirate" SS_TAP(X_TAB));
    } else if
    (leader_sequence_one_key(KC_C)) {
      SEND_STRING("codebin ." SS_TAP(X_ENTER));
    } else if
    (leader_sequence_two_keys(KC_C, KC_C)) {
      SEND_STRING("code ." SS_TAP(X_ENTER));
    } else if
    (leader_sequence_one_key(KC_E)) {
      SEND_STRING(SS_LSFT("'") "t80search_bot -t ");
    } else if
    (leader_sequence_two_keys(KC_G, KC_G)) {
      mac_mode = false; // gaming layer currently always returns to Layer_main. shouldn't be a problem since I wouldn't be launching it from mac mode ever.
      layer_move(Layer_gaming);
    } else if
    (leader_sequence_one_key(KC_L)) {
        rgb_timed_out = true;
        password_bypass = false;
    } else if
    (leader_sequence_two_keys(KC_C, KC_O)) {
      SEND_STRING("cd /temp/GIT/qmk_firmware && make clean && qmk flash -kb artiomsu_dactyl -km linux_and_mac -bl uf2-split-right");
    }
    leader_key_is_running = false;
    rgb_manage_leader(leader_key_is_running);
}

void matrix_scan_user(void) {
  uint32_t current_timer_value = timer_read32();

  if(rgb_timeout_counter == 0){ // this is reset in macros
      rgb_timeout_counter = current_timer_value;
  }

  if(!rgb_timed_out){
      if(timer_elapsed32(rgb_timeout_counter) > rgb_time_out_value){
          rgb_timed_out = true;
          rgb_timeout_counter = current_timer_value;
      }
  }

  rgb_manage_timeout(rgb_timed_out);

  // todo this needs some work rand() % 10 no longer works as expected.
  // right not its acting af if there is no randomization at all
  if(enable_bunnyhop && use_bunnyhop){
       if(bunny_hop_delay_counter >= 10){
        //srand(time(NULL));
        //srand(current_timer_value);
        SEND_STRING(SS_TAP(X_SPACE));
        bunny_hop_delay_counter = rand()>>8;
       }
       bunny_hop_delay_counter ++;
  }
}
