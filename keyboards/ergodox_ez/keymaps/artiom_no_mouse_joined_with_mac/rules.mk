# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
LTO_ENABLE = yes
COMMAND_ENABLE = no
DYNAMIC_MACRO_ENABLE = yes
SRC = matrix.c
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes


#stuff I added lol
CONSOLE_ENABLE = no
MOUSEKEY_ENABLE = no
POINTING_DEVICE_ENABLE = yes
EXTRAKEY_ENABLE = no #audio and brightness and shiet like that
BOOTMAGIC_ENABLE = no
COMBO_ENABLE = yes #pretty cool allows you to press two keys at the same time which will result in another key
AUDIO_ENABLE = no
LEADER_ENABLE = yes # allows you to do vim like key sequences
MIDI_ENABLE = no
UNICODE_ENABLE = no
BLUETOOTH_ENABLE = no
RAW_ENABLE = no
NKRO_ENABLE = yes

SRC+= combos.c leader.c macros.c rgb_led_control.c
