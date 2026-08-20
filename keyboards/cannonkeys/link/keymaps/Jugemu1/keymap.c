// Copyright 2025 Andrew Kannan (awkannan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "eeconfig.h"
#include "eeprom.h"
#include "oled_logo.c"

// ----------------------- combo header begins

void set_custom_combo_enable(bool enabled);
bool is_custom_combo_enabled(void);
void custom_combo_toggle(void);
void custom_combo_init(void);

// ----------------------- combo header ends

// ----------------------- tap_dance header begins

typedef enum {
    TD_MODE,
    TD_PLAY_MUTE,
    TD_LCTL_F1,       // this doesn't work for unknown reason
    TD_LSFT_F7,
    TD_LCTL_GRV,
    TD_RCTL_F1,
    TD_R1,
} custom_tap_dance;

// ----------------------- tap_dance header ends

// ----------------------- tap_hold header begins

#define TH(KC) LT(0,KC)         // use this for keys that we want to use tap hold

bool tap_hold_enabled(void);
void set_tap_hold(bool enabled);
#ifdef TAP_HOLD_ENABLE
void toggle_tap_hold(void);
#endif
void init_tap_hold(void);
bool process_tap_hold_record(uint16_t keycode, keyrecord_t *record);

// ----------------------- tap_hold header ends

// ----------------------- modes begins

typedef enum {
    MODE_WINDOWS,
    MODE_MAC,
    MODE_LAST,          // keep this last
} modes;

modes get_mode(void);
void set_mode(modes new_mode);
void cycle_mode(void);
const char *get_current_mode_name(void);
void init_mode(void);

volatile modes current_mode = MODE_WINDOWS;

const char *get_current_mode_name(void){
    switch(current_mode){
        case MODE_WINDOWS:
            return "Windows";
        case MODE_MAC:
            return "Mac";
        default:
            return "Unknown";
    }
}

modes get_mode(void){
    current_mode = eeprom_read_byte(EECONFIG_MODE_INDEX);
    return current_mode;
}

void set_mode(modes new_mode){
    current_mode = new_mode;
    eeprom_update_byte(EECONFIG_MODE_INDEX, new_mode);
}

void cycle_mode(void){
    modes new_mode = current_mode + 1;
    if(new_mode >= MODE_LAST){       //use first
        new_mode = (modes)0;
    }
    set_mode(new_mode);
}

void init_mode(void){
    modes mode = get_mode();
    set_mode(mode);
}

// ----------------------- modes ends


// ----------------------- keycodes begins

typedef enum {
    INITIAL_CUSTOM_KEYCODE = SAFE_RANGE,

    CK_SWITCH_LANGUAGE,
    CK_FULL_PRINT_SCREEN,
    CK_PARTIAL_PRINT_SCREEN,

    CK_TD_MODE = TD(TD_MODE),
    TD_AUDIO = TD(TD_PLAY_MUTE),

    CK_TD_R1 = TD(TD_R1),

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

uint16_t get_main_mod(void){
    modes current_mode = get_mode();
    switch(current_mode){
        case MODE_WINDOWS:
            return KC_LCTL;
        case MODE_MAC:
            return KC_LGUI;
        default:
            return KC_LCTL;
    }
}

uint16_t get_second_mod(void){
    modes current_mode = get_mode();
    switch(current_mode){
        case MODE_WINDOWS:
            return KC_LGUI;
        case MODE_MAC:
            return KC_LCTL;
        default:
            return KC_LGUI;
    }
}

void press_release(uint16_t keycode, const keyrecord_t *record){
    if (record->event.pressed) {
        register_code16(keycode);
    }else{
        unregister_code16(keycode);
    }
}

void switch_language(bool is_pressed){
    if (is_pressed){
        register_code16(get_second_mod());
        register_code16(KC_SPACE);
    } else{
        unregister_code16(KC_SPACE);
        unregister_code16(get_second_mod());
    }
}

void tap_switch_language(void){
    switch_language(true);
    switch_language(false);
}

void switch_language_key_press(const keyrecord_t *record){
    switch_language(record->event.pressed);
}

void print_full_screen_key_press(const keyrecord_t *record){
    modes current_mode = get_mode();
    switch(current_mode){
        case MODE_WINDOWS:
            if (record->event.pressed)
            {
                register_code16(KC_LGUI);
                register_code16(KC_PSCR);
            }else {
                unregister_code16(KC_PSCR);
                unregister_code16(KC_LGUI);
            }
            break;
        case MODE_MAC:
            if (record->event.pressed)
            {
                register_code16(KC_LGUI);
                register_code16(KC_LSFT);
                register_code16(KC_4);
            }else {
                unregister_code16(KC_4);
                unregister_code16(KC_LSFT);
                unregister_code16(KC_LGUI);
            }
            break;
        default:
            if (record->event.pressed)
            {
                tap_code(KC_PSCR);
            }
            break;
    }
}

void print_partial_screen_key_press(const keyrecord_t *record){
    modes current_mode = get_mode();
    switch(current_mode){
        case MODE_WINDOWS:
            if (record->event.pressed)
            {
                register_code16(KC_LGUI);
                register_code16(KC_LSFT);
                register_code16(KC_S);
            }else {
                unregister_code16(KC_S);
                unregister_code16(KC_LSFT);
                unregister_code16(KC_LGUI);
            }
            break;
        case MODE_MAC:
            if (record->event.pressed)
            {
                register_code16(KC_LGUI);
                register_code16(KC_LCTL);
                register_code16(KC_LSFT);
                register_code16(KC_4);
            }else {
                unregister_code16(KC_4);
                unregister_code16(KC_LCTL);
                unregister_code16(KC_LSFT);
                unregister_code16(KC_LGUI);
            }
            break;
        default:
            if (record->event.pressed)
            {
                tap_code(KC_PSCR);
            }
            break;
    }
}

bool process_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_MAIN_MOD:
            press_release(get_main_mod(), record);
            return false;
        case CK_SWITCH_LANGUAGE:
            switch_language_key_press(record);
            return false;
        case CK_FULL_PRINT_SCREEN:
            print_full_screen_key_press(record);
            return false;
        case CK_TG_COMBO:
            custom_combo_toggle();
            return false;
        case CK_PARTIAL_PRINT_SCREEN:
            print_partial_screen_key_press(record);
            return false;
        default:
            return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!pre_process_record_user(keycode, record)){
        return false;
    }

#ifdef TAP_DANCE_ENABLE

    if(!process_tap_hold_record(keycode, record)){
        return false;
    }

    // if(tap_hold_enabled() && !process_tap_hold_record(keycode, record)){
    //     return false;
    // }else{
    //     if(keycode == TH(KC_SCLN)){
    //         if (record->event.pressed)
    //         {
    //             register_code16(KC_SCLN);
    //         }else {
    //             unregister_code16(KC_SCLN);
    //         }
    //         return false;
    //     }
    // }
#endif
    if (!process_keycodes(keycode, record)){
        return false;
    }

    return true;
}

// ----------------------- keycodes begins

// ----------------------- combo begins

typedef enum {
    // right
    CMB_JK,
    CMB_JL,
    CMB_KL,
    CMB_JI,
    CMB_OSCLN,              // TODO: remove
    CMB_TH_O_SCLN,
    CMB_O_ARROW_SCLN,       // TDOO: remove
    CMB_IO,
    CMB_L_SCLN,             // TODO: remove
    CMB_TH_L_SCLN,
    CMB_L_ARROW_SCLN,

    // left
    CMB_DF,
    CMB_EF,
    CMB_SR,
    CMB_SF,
    CMB_SD,
    // CMB_AF,
    CMB_AS,
    CMB_AW,
    CMB_XC,
    CMB_CV,

} custom_combos;

// right
const uint16_t PROGMEM cmb_jk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM cmb_jl[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM cmb_kl[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM cmb_ji[] = {KC_J, KC_I, COMBO_END};
const uint16_t PROGMEM cmb_io[]   = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM cmb_oscln[]   = {KC_O, KC_SCLN, COMBO_END};      // TODO: remove this
const uint16_t PROGMEM cmb_th_o_scln[]   = {KC_O, TH(KC_SCLN), COMBO_END};
const uint16_t PROGMEM cmb_o_arrow_scln[]   = {KC_O, ARROW_SCLN, COMBO_END};
const uint16_t PROGMEM cmb_l_scln[]   = {KC_L, KC_SCLN, COMBO_END};                 // TODO: remove
const uint16_t PROGMEM cmb_th_l_scln[]   = {KC_L, TH(KC_SCLN), COMBO_END};
const uint16_t PROGMEM cmb_l_arrow_scln[] = {KC_L, ARROW_SCLN, COMBO_END};

// left
const uint16_t PROGMEM cmb_df[]   = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM cmb_ef[]   = {KC_E, KC_F, COMBO_END};
const uint16_t PROGMEM cmb_sr[]   = {KC_S, KC_R, COMBO_END};
const uint16_t PROGMEM cmb_sf[]   = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM cmb_sd[]   = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM cmb_as[]   = {KC_A, KC_S, COMBO_END};
// const uint16_t PROGMEM cmb_af[]   = {KC_A, KC_F, COMBO_END};
const uint16_t PROGMEM cmb_aw[]   = {KC_A, KC_W, COMBO_END};
const uint16_t PROGMEM cmb_xc[]   = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cmb_cv[]   = {KC_C, KC_V, COMBO_END};

combo_t key_combos[] = {
    // right
    [CMB_JK] = COMBO(cmb_jk, KC_LCTL),
    [CMB_JL] = COMBO(cmb_jl, KC_LALT),
    [CMB_KL] = COMBO(cmb_kl, KC_LGUI),
    [CMB_JI] = COMBO(cmb_ji, KC_RSFT),
    [CMB_IO] = COMBO(cmb_io, KC_BSPC),
    [CMB_OSCLN] = COMBO(cmb_oscln, KC_ENT),
    [CMB_TH_O_SCLN] = COMBO(cmb_th_o_scln, KC_ENT),
    [CMB_O_ARROW_SCLN] = COMBO(cmb_o_arrow_scln, KC_ENT),
    [CMB_L_SCLN] = COMBO(cmb_l_scln, KC_BSPC),                  // TODO: remove this
    [CMB_TH_L_SCLN] = COMBO(cmb_th_l_scln, KC_BSPC),
    [CMB_L_ARROW_SCLN] = COMBO(cmb_l_arrow_scln, KC_BSPC),

    // left
    [CMB_DF] = COMBO(cmb_df, KC_LCTL),
    [CMB_EF] = COMBO(cmb_ef, KC_LSFT),
    [CMB_SR] = COMBO_ACTION(cmb_sr),
    [CMB_SF] = COMBO(cmb_sf, KC_TAB),
    [CMB_SD] = COMBO(cmb_sd, KC_LGUI),
    [CMB_AS] = COMBO(cmb_as, CK_MAIN_MOD),
    // [CMB_AF] = COMBO(cmb_af, KC_TAB),
    [CMB_AW] = COMBO(cmb_aw, KC_ESC),
    [CMB_XC] = COMBO(cmb_xc, KC_BSPC),
    [CMB_CV] = COMBO(cmb_cv, KC_ENT),
};

uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case CMB_SR:
            // LSFT + TAB
            if (pressed) {
                register_code16(KC_LSFT);
                register_code16(KC_TAB);
            }
            else
            {
                unregister_code16(KC_TAB);
                unregister_code16(KC_LSFT);
            }
            break;
    }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo){
    switch(index){
        // right
        case CMB_JK:
        case CMB_JL:

        // left
        case CMB_SR:
        case CMB_SF:
        case CMB_XC:
        case CMB_CV:
            return 50;

        case CMB_L_SCLN:
        case CMB_OSCLN:
            return 80;

        default:
            return COMBO_TERM;
    }
}

void set_combo_enable(bool enabled){
    if (enabled) {
        combo_enable();
    } else{
        combo_disable();
    }
}

volatile bool current_custom_combo_status = false;

void set_custom_combo_enable(bool enabled){
    set_combo_enable(enabled);
    current_custom_combo_status = enabled;
    eeprom_update_byte(EECONFIG_COMBO_INDEX, current_custom_combo_status);
}

bool is_custom_combo_enabled(void){
    current_custom_combo_status = eeprom_read_byte(EECONFIG_COMBO_INDEX);
    return current_custom_combo_status;
}

void custom_combo_toggle(void){
    set_custom_combo_enable(
        !is_custom_combo_enabled()
    );
}

void custom_combo_init(void){
    set_custom_combo_enable(
        is_custom_combo_enabled()
    );
}


// ----------------------- combo ends

// ----------------------- tap_dance begins

void dance_mo1(tap_dance_state_t *state, void *user_data){
    if (state->count >= 4) {
        combo_toggle();
        reset_tap_dance(state);
    }
}

void dance_modes(tap_dance_state_t *state, void *user_data){
    if(!state->finished) return;
    switch(state->count){
        case 1:
            tap_switch_language();
            break;
        case 2:
            custom_combo_toggle();
            break;
        case 3:
            cycle_mode();
            break;
#ifdef TAP_HOLD_ENABLE
        case 4:
            toggle_tap_hold();
            break;
#endif
        default:
            break;
    }
}

void dance_enter_delete(tap_dance_state_t *state, void *user_data){
    if(!state->finished) return;
    switch(state->count){
        case 1:
            register_code16(KC_ENTER);
            break;
        case 2:
            register_code16(KC_DELETE);
            break;
    }
}

void dance_audio(tap_dance_state_t *state, void *user_data){
    if(!state->finished) return;
    switch(state->count){
        case 1:
            tap_code(KC_MPLY);
            break;
        case 2:
            tap_code(KC_MUTE);
            break;
        case 3:
            tap_code(KC_MEDIA_NEXT_TRACK);
            break;
        case 4:
            tap_code(KC_MEDIA_PREV_TRACK);
            break;
    }
}

void dance_qk(tap_dance_state_t *state, void *user_data){
    if(!state->finished) return;
    switch(state->count){
        case 1:
        case 2:
        case 3:
            tap_code(KC_Z);
            break;
        case 4:
            tap_code16(QK_BOOT);
            break;
        default:
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_MODE] = ACTION_TAP_DANCE_FN(dance_modes),
    [TD_PLAY_MUTE] = ACTION_TAP_DANCE_FN(dance_audio),
    [TD_LCTL_F1] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_F1),      // this doesn't work for unknown reason
    [TD_LSFT_F7] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_F7),
    [TD_LCTL_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_GRV),
    [TD_RCTL_F1] = ACTION_TAP_DANCE_DOUBLE(KC_RCTL, KC_F1),
    [TD_R1] = ACTION_TAP_DANCE_FN(dance_qk),
};


// ----------------------- tap_dance ends

// ----------------------- tap_hold begins

volatile bool tap_hold_status = false;

bool tap_hold_enabled(void){
    tap_hold_status = eeprom_read_byte(EECONFIG_TAP_HOLD_INDEX);
    return tap_hold_status;
}

void set_tap_hold(bool enabled){
    tap_hold_status = enabled;
    eeprom_update_byte(EECONFIG_TAP_HOLD_INDEX, tap_hold_status);
}

void toggle_tap_hold(void){
    set_tap_hold(!tap_hold_status);
}

void init_tap_hold(void){
    set_tap_hold(tap_hold_enabled());
}

bool process_tap_hold(
    const keyrecord_t *record,
    uint16_t hold_keycode
){
    bool is_hold = record->tap.count == 0;
    if(is_hold){
        if (record->event.pressed)
        {
            register_code16(hold_keycode);
        }else {
            unregister_code16(hold_keycode);
        }
        return false;
    }else{
        return true;
    }
}

bool process_tap_layer_mo(
    const keyrecord_t *record,
    uint16_t layer
){
    bool is_hold = record->tap.count == 0;
    if(is_hold){
        if (record->event.pressed)
        {
            layer_on(layer);
        } else{
            layer_off(layer);
        }
        return false;
    }else{
        return true;
    }
}

bool process_tap_hold_record(uint16_t keycode, keyrecord_t *record) {
    // if(!tap_hold_enabled()){
    //     return true;
    // }

    switch(keycode){

        // case LT(0, KC_L):
        //     if (!record->tap.count && record->event.pressed) {
        //         tap_code16(KC_9); // Intercept hold function to send 9
        //         return false;
        //     }
        //     return true;             // Return true for normal processing of tap keycode

        // case LT(0,KC_X):
        //     if (!record->tap.count && record->event.pressed) {
        //         tap_code16(C(KC_X)); // Intercept hold function to send Ctrl-X
        //         return false;
        //     }
        //     return true;             // Return true for normal processing of tap keycode

        case TH(KC_SCLN):
            if(tap_hold_enabled() && !process_tap_layer_mo(record, ARROW_LAYER)){
                return false;
            }
            press_release(KC_SCLN, record);
            return false;
        default:
            return true;
    }
}

// ----------------------- tap_hold ends

void keyboard_post_init_user(void){
    custom_combo_init();
    init_mode();
}

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _GAME_GENSHIN,
    _GAME,
};

#define T_BASE DF(_QWERTY)
#define T_GENSH DF(_GAME_GENSHIN)
#define T_GAME DF(_GAME)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// [0] = LAYOUT(
//   KC_GRV,       KC_1,      KC_2,       KC_3,       KC_4,        KC_5,                                  KC_6,       KC_7,      KC_8,        KC_9,       KC_0,       KC_MINS,
//   KC_ESC,       KC_Q,      KC_W,       KC_E,       KC_R,        KC_T,                                  KC_Y,       KC_U,      KC_I,        KC_O,       KC_P,       KC_BSPC,
//   KC_TAB,       KC_A,      KC_S,       KC_D,       KC_F,        KC_G,                                  KC_H,       KC_J,      KC_K,        KC_L,    KC_SCLN,       KC_QUOT,
//   KC_LSFT,      KC_Z,      KC_X,       KC_C,       KC_V,        KC_B,      KC_MUTE,     KC_MPLY,       KC_N,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,       KC_RSFT,
//              KC_LGUI,   KC_LALT,    KC_LCTL,      MO(1),      KC_ENT,                                KC_SPC,      MO(2),   KC_RCTL,     KC_RALT,    KC_RGUI
// ),

// [0] = LAYOUT(
//   _______,       _______,      _______,       _______,       _______,        _______,                                  _______,       _______,      _______,        _______,       _______,       _______,
//   _______,       _______,      _______,       _______,       _______,        _______,                                  _______,       _______,      _______,        _______,       _______,       _______,
//   _______,       _______,      _______,       _______,       _______,        _______,                                  _______,       _______,      _______,        _______,       _______,       _______,
//   _______,       _______,      _______,       _______,       _______,        _______,      _______,     _______,       _______,       _______,      _______,        _______,       _______,       _______,
//                  _______,      _______,       _______,         MO(1),        _______,                                  _______,         MO(2),      _______,        _______,       _______
// ),

// [0] = LAYOUT(
//   XXXXXXX,       XXXXXXX,      XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,                                  XXXXXXX,       XXXXXXX,      XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//   XXXXXXX,       XXXXXXX,      XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,                                  XXXXXXX,       XXXXXXX,      XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//   XXXXXXX,       XXXXXXX,      XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,                                  XXXXXXX,       XXXXXXX,      XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//   XXXXXXX,       XXXXXXX,      XXXXXXX,       XXXXXXX,       XXXXXXX,        XXXXXXX,      XXXXXXX,     XXXXXXX,       XXXXXXX,       XXXXXXX,      XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//                  XXXXXXX,      XXXXXXX,       XXXXXXX,         MO(1),        XXXXXXX,                                  XXXXXXX,         MO(2),      XXXXXXX,        XXXXXXX,       XXXXXXX
// ),

[_QWERTY] = LAYOUT(
   KC_ESC,       KC_1,      KC_2,       KC_3,       KC_4,        KC_5,                                  KC_6,       KC_7,       KC_8,        KC_9,       KC_0,        KC_GRV,
   KC_TAB,       KC_Q,      KC_W,       KC_E,       KC_R,        KC_T,                                  KC_Y,       KC_U,       KC_I,        KC_O,       KC_P,       KC_BSPC,
  KC_LCTL,       KC_A,      KC_S,       KC_D,       KC_F,        KC_G,                                  KC_H,       KC_J,       KC_K,        KC_L,    KC_SCLN,       KC_QUOT,
  KC_LSFT,       KC_Z,      KC_X,       KC_C,       KC_V,        KC_B,  CK_TD_MODE, TG(_GAME_GENSHIN),  KC_N,       KC_M,    KC_COMM,      KC_DOT,    KC_SLSH,       KC_PIPE,
              KC_LALT,    KC_LGUI, MO(_LOWER),    KC_SPC,  CK_TD_MODE,                         TG(_GAME_GENSHIN),  KC_ENT, MO(_RAISE),    KC_BSPC,     KC_RGUI
),

// [_LOWER] = LAYOUT(
// _______,       KC_VOLD,   KC_VOLU,   TD_AUDIO,    _______,         _______,          _______,                 _______,        _______,       _______,       _______,     _______,     _______,     _______,
// KC_F1,           KC_F2,     KC_F3,      KC_F4,      KC_F5,           KC_F6,          _______,                 _______,        KC_F7,           KC_F8,         KC_F9,      KC_F10,      KC_F11,      KC_F12,
// TD(TD_LCTL_GRV),KC_EXLM,    KC_AT,    KC_HASH,     KC_DLR,         KC_PERC,          _______,                 _______,        KC_CIRC,       KC_AMPR,       KC_ASTR,     KC_LPRN,     KC_RPRN,     KC_TILD,
// _______,       _______,   _______,    _______,    _______,         _______,          _______,                 _______,        XXXXXXX,       KC_UNDS,       KC_PLUS,     KC_LCBR,     KC_RCBR,     KC_PIPE,
//                                       _______,    _______,         _______,          _______,                 _______,        _______,       _______,       _______
// ),

[_LOWER] = LAYOUT(
  _______,       KC_VOLD,      KC_VOLU,      TD_AUDIO,       _______,        _______,                                  _______,       _______,      _______,        _______,       _______,       _______,
    KC_F1,         KC_F2,        KC_F3,         KC_F4,         KC_F5,          KC_F6,                                    KC_F7,         KC_F8,        KC_F9,         KC_F10,        KC_F11,        KC_F12,
TD(TD_LCTL_GRV), KC_EXLM,        KC_AT,       KC_HASH,        KC_DLR,        KC_PERC,                                  KC_CIRC,       KC_AMPR,      KC_ASTR,        KC_LPRN,       KC_RPRN,       KC_TILD,
  _______,       _______,      _______,       _______,       _______,        _______,      QK_BOOT,     _______,       XXXXXXX,       KC_UNDS,      KC_PLUS,        KC_LCBR,       KC_RCBR,       KC_PIPE,
                 _______,      _______,       _______,       _______,        _______,                                  _______,       _______,      _______,        MS_WHLU,       MS_WHLD
),

// [_RAISE] = LAYOUT(
// _______,       _______,   _______,    _______,    _______,         _______,          _______,                 _______,        KC_VOLD,       KC_VOLU,      TD_AUDIO,    CK_PPSCR,    CK_FPSCR,     KC_DEL,
// KC_GRV,           KC_1,      KC_2,       KC_3,       KC_4,            KC_5,          _______,                 _______,        KC_6,             KC_7,          KC_8,        KC_9,        KC_0,    KC_VOLU,
// TD(TD_RCTL_F1),  KC_F2,     KC_F3,      KC_F4,      KC_F5,           KC_F6,          _______,                 _______,        KC_LEFT,       KC_DOWN,         KC_UP,     KC_RGHT,     _______,    KC_VOLD,
// TD(TD_LSFT_F7),  KC_F8,     KC_F9,     KC_F10,     KC_F11,          KC_F12,          _______,                 _______,        KC_PLUS,       KC_MINS,        KC_EQL,     KC_LBRC,     KC_RBRC,    KC_BSLS,
//                                       _______,    _______,         _______,          _______,                 _______,        _______,       _______,       _______
// ),

[_RAISE] = LAYOUT(
          KC_ESC,       KC_1,      KC_2,       KC_3,       KC_4,        KC_5,                                   KC_VOLD,       KC_VOLU,   TD_AUDIO,    CK_PPSCR,   CK_FPSCR,        KC_DEL,
          KC_GRV,       KC_1,      KC_2,       KC_3,       KC_4,        KC_5,                                      KC_6,          KC_7,       KC_8,        KC_9,       KC_0,       KC_VOLU,
  TD(TD_RCTL_F1),      KC_F2,     KC_F3,      KC_F4,      KC_F5,       KC_F6,                                   KC_LEFT,       KC_DOWN,      KC_UP,     KC_RGHT,    _______,       KC_VOLD,
  TD(TD_LSFT_F7),      KC_F8,     KC_F9,     KC_F10,     KC_F11,      KC_F12,     _______,      _______,        KC_PLUS,       KC_MINS,     KC_EQL,     KC_LBRC,    KC_RBRC,       KC_BSLS,
                     _______,   _______,    _______,    _______,     _______,                                   _______,       _______,      _______,   _______,    _______
),

// [_ADJUST] = LAYOUT(
// XXXXXXX,       XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,         XXXXXXX,          QK_BOOT,                  KC_NUM,         T_BASE,       T_GENSH,        T_GAME,     XXXXXXX,     XXXXXXX,    XXXXXXX,
// XXXXXXX,       XXXXXXX,   KC_INS,     KC_HOME,    KC_PGUP,         XXXXXXX,          XXXXXXX,                 KC_PSCR,        XXXXXXX,       KC_KP_7,       KC_KP_8,     KC_KP_9,     XXXXXXX,    XXXXXXX,
// XXXXXXX,       XXXXXXX,   KC_DEL,      KC_END,    KC_PGDN,         XXXXXXX,          XXXXXXX,                 KC_SCRL,         KC_DOT,       KC_KP_4,       KC_KP_5,     KC_KP_6,     XXXXXXX,    XXXXXXX,
// XXXXXXX,       XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,         XXXXXXX,          XXXXXXX,                 KC_PAUS,        KC_KP_0,       KC_KP_1,       KC_KP_2,     KC_KP_3,     XXXXXXX,    XXXXXXX,
//                                       _______,    _______,         _______,          _______,                 _______,        _______,       _______,       _______
// ),

[_ADJUST] = LAYOUT(
  XXXXXXX,       XXXXXXX,      XXXXXXX,       XXXXXXX,       XXXXXXX,        QK_BOOT,                                   KC_NUM,        T_BASE,      T_GENSH,         T_GAME,       XXXXXXX,       XXXXXXX,
  XXXXXXX,       XXXXXXX,       KC_INS,       KC_HOME,       KC_PGUP,        KC_PSCR,                                  KC_PSCR,       KC_KP_7,      KC_KP_8,        KC_KP_9,       XXXXXXX,       XXXXXXX,
  XXXXXXX,       XXXXXXX,       KC_DEL,        KC_END,       KC_PGDN,        KC_SCRL,                                   KC_DOT,       KC_KP_4,      KC_KP_5,        KC_KP_6,       XXXXXXX,       XXXXXXX,
  XXXXXXX,       XXXXXXX,      XXXXXXX,       XXXXXXX,       XXXXXXX,        KC_PAUS,      QK_BOOT,     XXXXXXX,       KC_KP_0,       KC_KP_1,      KC_KP_2,        KC_KP_3,       XXXXXXX,       XXXXXXX,
                 _______,      _______,       _______,       _______,        _______,                                  _______,       _______,      _______,        _______,       _______
),

[_GAME_GENSHIN] = LAYOUT(
   KC_ESC,       KC_1,      KC_2,       KC_3,       KC_4,        KC_5,                                  KC_6,       KC_7,       KC_8,        KC_9,       KC_0,        KC_GRV,
   KC_TAB,       KC_Q,      KC_W,       KC_E,       KC_R,        KC_T,                                  KC_Y,       KC_U,       KC_I,        KC_O,       KC_P,       KC_BSPC,
  KC_LCTL,       KC_A,      KC_S,       KC_D,       KC_F,        KC_G,                                  KC_H,       KC_J,       KC_K,        KC_L,    KC_SCLN,       KC_QUOT,
  KC_LSFT,       KC_Z,      KC_X,       KC_C,       KC_V,        KC_B, CK_TD_MODE,  TG(_GAME_GENSHIN),  KC_N,       KC_M,    KC_COMM,      KC_DOT,    KC_SLSH,       KC_PIPE,
              KC_LALT,    KC_LGUI, MO(_LOWER),    KC_SPC,  CK_TD_MODE,                         TG(_GAME_GENSHIN),  KC_ENT, MO(_RAISE),    KC_BSPC,     KC_RGUI
),

[_GAME] = LAYOUT(
   KC_ESC,       KC_1,      KC_2,       KC_3,       KC_4,        KC_5,                                  KC_6,       KC_7,       KC_8,        KC_9,       KC_0,        KC_GRV,
   KC_TAB,       KC_Q,      KC_W,       KC_E,       KC_R,        KC_T,                                  KC_Y,       KC_U,       KC_I,        KC_O,       KC_P,       KC_BSPC,
  KC_LCTL,       KC_A,      KC_S,       KC_D,       KC_F,        KC_G,                                  KC_H,       KC_J,       KC_K,        KC_L,    KC_SCLN,       KC_QUOT,
  KC_LSFT,       KC_Z,      KC_X,       KC_C,       KC_V,        KC_B, CK_TD_MODE,  TG(_GAME_GENSHIN),  KC_N,       KC_M,    KC_COMM,      KC_DOT,    KC_SLSH,       KC_PIPE,
              KC_LALT,    KC_LGUI, MO(_LOWER),    KC_SPC,  CK_TD_MODE,                         TG(_GAME_GENSHIN),  KC_ENT, MO(_RAISE),    KC_BSPC,     KC_RGUI
),

};


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

static bool combo_status_before_game_layer;

//OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//   if (!is_keyboard_master())
//     return OLED_ROTATION_270;
//   return OLED_ROTATION_90;
    return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

#define LINE_SIZE 24

const char *get_layer_name(void){
    static char layer_name_str[24];
    switch(layer_state){
        case _QWERTY:
            snprintf(layer_name_str, sizeof(layer_name_str), "Default");
            break;
        case (1 << _LOWER):
            snprintf(layer_name_str, sizeof(layer_name_str), "Lower");
            break;
        case (1 << _RAISE):
            snprintf(layer_name_str, sizeof(layer_name_str), "Raise");
            break;
        case (1 << _ADJUST):
            snprintf(layer_name_str, sizeof(layer_name_str), "Adjust");
            break;
        case (1 << _GAME_GENSHIN):
            snprintf(layer_name_str, sizeof(layer_name_str), "Genshin");
            break;
        case (1 << _GAME):
            snprintf(layer_name_str, sizeof(layer_name_str), "Game");
            break;
        default:
            snprintf(layer_name_str, sizeof(layer_name_str), "Undef-%d", layer_state);
            break;
    }
    return layer_name_str;
}

void write_layer_ln(void){
    static char layer_line[LINE_SIZE];
    const char *layer_name = get_layer_name();
    snprintf(
        layer_line,
        LINE_SIZE,
        "Layer:\n- %s",
        layer_name
    );
    oled_write_ln(layer_line, false);
}


bool try_write_combo_ln(void){
    static char combo_line[LINE_SIZE];
    bool is_enabled = is_combo_enabled();
    if (is_enabled) {
        oled_write_P(PSTR("\n"), false);
        snprintf(
            combo_line,
            sizeof(combo_line),
            "Combo: /"
        );
        oled_write_ln(combo_line, false);
    }
    return is_enabled;
}

bool try_write_tap_hold_ln(void){
    static char tap_hold_line[LINE_SIZE];
    bool is_enabled = tap_hold_enabled();
    if (is_enabled) {
        oled_write_P(PSTR("\n"), false);
        snprintf(
            tap_hold_line,
            sizeof(tap_hold_line),
            "TapHold: /"
        );
        oled_write_ln(tap_hold_line, false);
    }
    return is_enabled;
}

const char *read_mode_name(void){
    static char mode_name_line[LINE_SIZE];
    oled_write_P(PSTR("\n"), false);
    snprintf(
        mode_name_line,
        sizeof(mode_name_line),
        "Mode:\n- %s",
        get_current_mode_name()
    );
    return mode_name_line;
}

#ifdef RENDER_LOGO

void oled_render_logo(void) {
    const char *logo = get_logo(LOGO_TYPE);
    oled_write_raw_P(logo, logo_size);
}

uint16_t logo_timer = 0;
bool is_rendering_logo = false;

void write_logo_timer_elapsed(void){
    static char timer_line[LINE_SIZE];
    int elapsed = timer_elapsed(logo_timer);
    snprintf(
        timer_line,
        LINE_SIZE,
        "Timer:\n%d / %d",
        elapsed,
        LOGO_START_DURATION
    );
    oled_write_ln(timer_line, false);
}

void reset_logo_timer(void){
    logo_timer = timer_read();
    is_rendering_logo = false;
}

bool try_render_logo(void){
    if (
        is_rendering_logo                                       // if it's rendering, keep do it without checking time
        || timer_elapsed(logo_timer) > LOGO_START_DURATION
    ) {
#ifdef NO_LOGO_TIMEOUT
        oled_clear();
#endif
        oled_clear();
        oled_render_logo();  // TODO: turn on after setting new artwork
        // oled_off();

        is_rendering_logo = true;
        return true;
    }
    return false;
}
#endif

#ifdef ENABLE_CUSTOM_INTERACTION_TIMEOUT
uint16_t interaction_timer = 0;
bool is_interaction_timeout = false;

void reset_interaction_timer(void){
    interaction_timer = timer_read();
    is_interaction_timeout = false;
}

bool try_interaction_timeout(void){
    if (
        is_interaction_timeout   // if it's rendering, keep do it without checking time
        || timer_elapsed(interaction_timer) > INTERACTION_TIMEOUT_DURATION
    ) {
#ifdef NO_LOGO_TIMEOUT
        oled_clear();
#endif
        oled_clear();
        oled_off();

        is_interaction_timeout = true;
        return true;
    }
    return false;
}
#endif // ENABLE_CUSTOM_INTERACTION_TIMEOUT

#define MAX_LINE 6

bool oled_task_user(void) {

#ifdef ENABLE_CUSTOM_INTERACTION_TIMEOUT
    if (try_interaction_timeout()) {
        return false;
    }
#endif // ENABLE_CUSTOM_INTERACTION_TIMEOUT

    if (is_keyboard_master()) {

#ifdef RENDER_LOGO
        if(try_render_logo()){
            return false;
        }
#endif
        oled_on();

        oled_clear();

        int lines = 0;

        write_layer_ln();
        lines += 1;

        oled_write_ln(read_mode_name(), false);
        lines += 1;

        if(try_write_combo_ln()) {
            lines += 1;
        }

        if(try_write_tap_hold_ln()){
            lines += 1;
        }

#ifdef SET_KEYLOG
        if(lines < MAX_LINE) {
            oled_write_P(PSTR("\n"), false);
            oled_write_ln(read_keylog(), false);
            lines += 1;
        }
#endif

#ifdef RENDER_LOGO
        if(lines < MAX_LINE) {
            oled_write_P(PSTR("\n"), false);
            write_logo_timer_elapsed();
            lines += 1;
        }
#endif

    }
    else {
#ifdef RENDER_LOGO
#ifdef NO_LOGO_TIMEOUT
        oled_clear();
#endif
        // oled_render_logo();  // TODO: turn on after setting new artwork
        oled_clear();
        oled_off();
#endif
    }

    return false;
}
#endif // OLED_ENABLE

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record){

#ifdef OLED_ENABLE
#ifdef SET_KEYLOG
    set_keylog(keycode, record);
#endif

#ifdef RENDER_LOGO
    reset_logo_timer();
#endif
#endif

#ifdef ENABLE_CUSTOM_INTERACTION_TIMEOUT
    reset_interaction_timer();
#endif // ENABLE_CUSTOM_INTERACTION_TIMEOUT

    if (record->event.pressed) {
        switch (keycode){
            case TG(_GAME_GENSHIN):
                {
                    if (IS_LAYER_ON(_GAME_GENSHIN))
                    {
                        // restore combo status
                        set_custom_combo_enable(combo_status_before_game_layer);
                    } else {
                        // save combo status prior to entering game mode
                        combo_status_before_game_layer = is_custom_combo_enabled();
                        // disable combo
                        set_custom_combo_enable(false);
                    }
                }
                return false;
            default:
                break;
        }
    }

    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(MS_WHLU);
        } else {
            tap_code(MS_WHLD);
        }
    }
    return true;
}
#endif
