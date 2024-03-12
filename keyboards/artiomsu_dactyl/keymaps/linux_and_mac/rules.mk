# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
COMBO_ENABLE = yes			# combo feature
LEADER_ENABLE = yes			# leader key
DYNAMIC_MACRO_ENABLE = yes  # dynamic macro feature
OS_DETECTION_ENABLE = yes   # os detection
CAPS_WORD_ENABLE = yes		# no need to hold down

RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_DRIVER = ws2812
WS2812_DRIVER = vendor
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor

# if this is enabled for some reason mouse buttons won't work on macos, but mouse movement does. so there is that...
PROGRAMMABLE_BUTTON_ENABLE = no # for my obs rust program - keycodes for HID usage "Telephony Device Page" (0x0B), "Programmable button usage" (0x07)

# note to self, combos must be removed from SRC
INTROSPECTION_KEYMAP_C = combos.c # if you are wondering wtf is this. see here https://github.com/qmk/qmk_firmware/issues/21137#issuecomment-1577898767

#SRC+= secrets.c combos.c leader.c macros.c rgb_led_control.c
SRC+= secrets.c leader.c macros.c rgb_led_control.c
