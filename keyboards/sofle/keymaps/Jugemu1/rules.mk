BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
COMMAND_ENABLE = no         # Commands for debug and configuration
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
CONSOLE_ENABLE = no
EXTRAKEY_ENABLE = yes
RGBLIGHT_ENABLE = no

SWAP_HANDS_ENABLE = no

SOCD_ENABLE = yes

#  convert to Splinky here
# https://github.com/qmk/qmk_firmware/blob/master/docs/feature_converters.md
# https://github.com/qmk/qmk_firmware/issues/18746
# consider using #ifdef CONVERT_TO_PROMICRO_RP2040 for condition
CONVERT_TO=promicro_rp2040

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += ./timelogger.c
endif

ifeq ($(strip $(CONVERT_TO)), promicro_rp2040)
	ENCODER_ENABLE = yes
	NKRO_ENABLE = yes
	MOUSEKEY_ENABLE = yes        # Mouse keys
	BOOTMAGIC_ENABLE = yes       # Enable Bootmagic Lite
endif
