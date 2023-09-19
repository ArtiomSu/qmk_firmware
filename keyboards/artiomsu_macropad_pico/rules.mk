BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_DRIVER = ws2812
WS2812_DRIVER = vendor
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = no

OLED_ENABLE = yes
OPT_DEFS += -DHAL_USE_I2C=TRUE

ENCODER_ENABLE = yes
