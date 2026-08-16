TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
OLED_ENABLE = yes
ENCODER_ENABLE = yes

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += ./lib/keylogger.c
	SRC += ./lib/timelogger.c
endif
