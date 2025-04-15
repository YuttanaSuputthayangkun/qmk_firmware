#pragma once

#include QMK_KEYBOARD_H
#include "jugemu.h"
#include "modes.h"

#ifdef TAP_DANCE_ENABLE
    #include "custom_tap_dance.h"
#endif

typedef enum {
    INITIAL_CUSTOM_KEYCODE = SAFE_RANGE,

    CK_SWITCH_LANGUAGE,
    CK_FULL_PRINT_SCREEN,
    CK_PARTIAL_PRINT_SCREEN,

    CK_TD_MODE = TD(TD_MODE),
    TD_AUDIO = TD(TD_PLAY_MUTE),

    CK_MAIN_MOD,
    CK_TG_COMBO,

    ARROW_SCLN = LT(ARROW_LAYER, KC_SCLN),         // LT(ARROW_LAYER, KC_SCLN)

} custom_keycode;

#define CK_MM CK_MAIN_MOD
#define CK_SWL CK_SWITCH_LANGUAGE
#define CK_FPSCR CK_FULL_PRINT_SCREEN
#define CK_PPSCR CK_PARTIAL_PRINT_SCREEN
#define CK_TGCMB CK_TG_COMBO

uint16_t get_main_mod(void);
void tap_switch_language(void);

void press_release(uint16_t keycode, const keyrecord_t *record);
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record);
