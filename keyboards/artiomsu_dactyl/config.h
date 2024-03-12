/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// WS2812 RGB LED strip input and number of LEDs
/* RGB light config
    36 LEDs for notifications using 144/m led strip
    30 LEDs around the bottom of the board using 60/m led strip
    43 LEDs pointing up, in a grid
*/
#define RGBLIGHT_LED_COUNT 109
#define RGBLIGHT_SPLIT
//#define RGBLED_SPLIT { 36, 36 }

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_DRIVER SIOD0
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_PIO_USE_PIO0 // use state machine 0 for serial split
#define WS2812_PIO_USE_PIO1 // use state machine 1 for rgb

//#define SPLIT_TRANSPORT_MIRROR // if this one is enabled the led modes dont sync // This mirrors the master side matrix to the slave side for features that react or require knowledge of master side key presses on the slave side. The purpose of this feature is to support cosmetic use of key events (e.g. RGB reacting to keypresses).
#define SPLIT_LAYER_STATE_ENABLE // This enables syncing of the layer state between both halves of the split keyboard. The main purpose of this feature is to enable support for use of things like OLED display of the currently active layer.
#define SPLIT_LED_STATE_ENABLE // This enables syncing of the Host LED status (caps lock, num lock, etc) between both halves of the split keyboard. The main purpose of this feature is to enable support for use of things like OLED display of the Host LED status.
#define SPLIT_MODS_ENABLE // This enables transmitting modifier state (normal, weak and oneshot) to the non primary side of the split keyboard. The purpose of this feature is to support cosmetic use of modifer state (e.g. displaying status on an OLED screen).
#define SPLIT_ACTIVITY_ENABLE // This synchronizes the activity timestamps between sides of the split keyboard, allowing for activity timeouts to occur.

//#define MASTER_LEFT
#define MASTER_RIGHT


#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE


#define RGBLIGHT_EFFECT_SNAKE_LENGTH 8
