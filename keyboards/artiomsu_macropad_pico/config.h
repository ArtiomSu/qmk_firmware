
#pragma once


#define RGBLED_NUM 1

#define WS2812_PIO_USE_PIO1 // use state machine 1 for rgb

#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
//#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
//#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE


//#define RGBLIGHT_EFFECT_SNAKE_LENGTH 8

#define OLED_DISPLAY_128X32
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP12
#define I2C1_SCL_PIN GP13

#define OLED_BRIGHTNESS 220 // 255 max
#define ENCODERS_PAD_A { GP0, GP4, GP8, GP17 }
#define ENCODERS_PAD_B { GP1, GP5, GP9, GP16 }
#define ENCODER_RESOLUTION 4
