#include QMK_KEYBOARD_H
#include "jugemu.h"
#include <stdio.h>
#include "custom_combo.h"
#include "tap_hold.h"

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _GAME_GENSHIN,
    _GAME,
    _READING,
};

#define T_BASE DF(_QWERTY)
#define T_GENSH TG(_GAME_GENSHIN)
#define T_GAME TG(_GAME)
#define T_READING TG(_READING)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LCTL  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------| MODE  |    |TG_GAME|------+------+------+------+------+------|
    * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| VOLU |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `----------------------------'           '------''--------------------'
    */

    [_QWERTY] = LAYOUT(
    KC_ESC,        KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
    KC_TAB,        KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    KC_LCTL,       KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
    KC_LSFT,       KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,CK_TD_MODE, TG(_GAME_GENSHIN),  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                            KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC,            KC_ENT, MO(_RAISE), KC_BSPC, KC_RGUI
    ),
    /* LOWER
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      | VOLD | VOLU | AUDIO|      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LCTL `|   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
    * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
    * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `----------------------------'           '------''--------------------'
    */
    [_LOWER] = LAYOUT(
    _______,          KC_VOLD, KC_VOLU,TD_AUDIO, _______, _______,                   _______, _______, _______,_______, _______, _______,
    KC_F1,              KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    TD(TD_LCTL_GRV),  KC_EXLM,   KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
    _______,          _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                                        _______, _______, _______, _______, _______,  _______, _______, _______
    ),
    /* RAISE
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |      |      |      |      |      |                    | VOLD | VOLU | AUDIO|PPSCR |FPSCR | DEL  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | VOLU |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LCTLF1|  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------| Left | Down |  Up  |Right |      | VOLD |
    * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
    * |LSFTF7|  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `----------------------------'           '------''--------------------'
    */

    [_RAISE] = LAYOUT(
    _______,         _______, _______, _______, _______, _______,                       KC_VOLD, KC_VOLU,TD_AUDIO,CK_PPSCR,  CK_FPSCR,  KC_DEL,
    KC_GRV,             KC_1,     KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,      KC_0, KC_VOLU,
    TD(TD_RCTL_F1),    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_LEFT, KC_DOWN,   KC_UP,   KC_RGHT, _______, KC_VOLD,
    TD(TD_LSFT_F7),    KC_F8,    KC_F9,  KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS,  KC_EQL, KC_LBRC,   KC_RBRC, KC_BSLS,
                                        _______, _______, _______,   _______, _______,  _______, _______, _______
    ),

    /* ADJUST
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |      |      |      |      |READIN|                    |QWERTY|GENSHN| GAME |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |      |insert| home | pgup |      |                    |      |  7   |  8   |   9  |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |      |delete| end  | pgdn |      |-------.    ,-------|   .  |  4   |  5   |   6  |      |      |
    * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
    * |      |      |      |      |      |      |-------|    |-------|   0  |  1   |  2   |   3  |      |      |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `----------------------------'           '------''--------------------'
    */
    [_ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,T_READING,                   T_BASE, T_GENSH,  T_GAME, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,  KC_INS, KC_HOME, KC_PGUP, XXXXXXX,                   XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,  KC_DEL,  KC_END, KC_PGDN, XXXXXXX,                    KC_DOT, KC_KP_4, KC_KP_5, KC_KP_6, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, XXXXXXX, XXXXXXX,
                                _______, _______, _______, _______, _______,  _______, _______, _______
    ),
    /* GAME_GENSHIN
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * | ESC  |   1  |   2  |   3  |   4  |   M  |                    | VOLD | VOLU | AUDIO|   9  |FPSCR |AUDIO |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |VOLU  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | LCTL |   A  |   S  |   D  |   F  |   J  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |VOLD  |
    * |------+------+------+------+------+------| MODE  |    |TGLayer|------+------+------+------+------+------|
    * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LCTL |Space | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `----------------------------'           '------''--------------------'
    */

    [_GAME_GENSHIN] = LAYOUT(
    KC_ESC,    KC_1,   KC_2,    KC_3,    KC_4,    KC_M,                                  KC_VOLD,    KC_VOLU,TD_AUDIO,    KC_9,   CK_FPSCR,   TD_AUDIO,
    KC_TAB,    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                  KC_Y,    KC_U,    KC_I,    KC_O,       KC_P,    KC_VOLU,
    KC_LALT,   KC_A,   KC_S,    KC_D,    KC_F,    KC_J,                                  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_VOLD,
    KC_LSFT,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, CK_TD_MODE,   TG(_GAME_GENSHIN), KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    KC_RSFT,
                                 KC_LALT, KC_LCTL, KC_SPC, KC_SPC,         KC_ENT, MO(_RAISE), KC_BSPC, KC_RGUI
    ),

    /* GAME
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LCTL  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------| MODE  |    |TG_GAME|------+------+------+------+------+------|
    * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| VOLU |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `----------------------------'           '------''--------------------'
    */

    [_GAME] = LAYOUT(
    KC_ESC,        KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                _______, _______,  _______,   _______,    KC_0,    KC_GRV,
    KC_TAB,        KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                   KC_Y,    KC_U,    KC_UP,      KC_O,    KC_P,    KC_MINS,
    KC_LCTL,       KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                   KC_H, KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_SCLN, KC_QUOT,
    KC_LSFT,       KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  CK_TD_MODE,        T_GAME,       KC_N,    KC_M,  KC_COMM,    KC_DOT, KC_SLSH, KC_RSFT,
                              KC_LALT,   KC_LGUI,MO(_LOWER), KC_SPC,            KC_ENT, MO(_RAISE), KC_BSPC, KC_RGUI
    ),

    [_READING] = LAYOUT(
    KC_ESC,     KC_HOME,XXXXXXX,     KC_END,    KC_4,      KC_5,                               _______, _______,  _______,   _______,    KC_0,    KC_GRV,
    KC_TAB,     KC_PGUP,  KC_UP,    KC_PGDN,    KC_R,      KC_T,                                   KC_Y,    KC_U,    KC_UP,      KC_O,    KC_P,    KC_MINS,
    KC_LCTL,    KC_LEFT,KC_DOWN,   KC_RIGHT,    KC_F,      KC_G,                                   KC_H, KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_SCLN, KC_QUOT,
    KC_LSFT,       KC_Z,   KC_X,       KC_C,    KC_V,    KC_ENT, CK_TD_MODE,      T_READING,       KC_N,    KC_M,  KC_COMM,    KC_DOT, KC_SLSH, KC_RSFT,
                                    KC_LALT, KC_LGUI,MO(_LOWER),     KC_SPC,         KC_ENT, MO(_RAISE), KC_BSPC, KC_RGUI
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
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
            snprintf(layer_name_str, sizeof(layer_name_str), "Game Genshin");
            break;
        case (1 << _GAME):
            snprintf(layer_name_str, sizeof(layer_name_str), "Game");
            break;
        case (1 << _READING):
            snprintf(layer_name_str, sizeof(layer_name_str), "Reading");
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
        "Layer : %s",
        layer_name
    );
    oled_write_ln(layer_line, false);
}


bool try_write_combo_ln(void){
    static char combo_line[LINE_SIZE];
    bool is_enabled = is_combo_enabled();
    if (is_enabled) {
        snprintf(
            combo_line,
            sizeof(combo_line),
            "Combo : Enabled"
        );
        oled_write_ln(combo_line, false);
    }
    return is_enabled;
}

bool try_write_tap_hold_ln(void){
    static char tap_hold_line[LINE_SIZE];
    bool is_enabled = tap_hold_enabled();
    if (is_enabled) {
        snprintf(
            tap_hold_line,
            sizeof(tap_hold_line),
            "TapHold : Enabled"
        );
        oled_write_ln(tap_hold_line, false);
    }
    return is_enabled;
}

const char *read_mode_name(void){
    static char mode_name_line[LINE_SIZE];
    snprintf(
        mode_name_line,
        sizeof(mode_name_line),
        "Mode : %s",
        get_current_mode_name()
    );
    return mode_name_line;
}

#ifdef RENDER_LOGO

void oled_render_logo(void) {
    static const char PROGMEM my_logo[] = {
        // 'Axe', 128x32px
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x80, 0x80, 0x80, 0xc0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
        // 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        // 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        // 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        // 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
        // 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
        // 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3e,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        // 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
        // 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

        // 'Axe_3', 128x32px
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
        // 0x80, 0xc0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
        // 0xf8, 0xf8, 0xf8, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        // 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        // 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
        // 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f,
        // 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        // 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
        // 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
        // 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3e, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xff,
        // 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        // 0xff, 0xff, 0xff, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x80, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
        // 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01,
        // 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x1f, 0x1f, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
        // 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        // 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f,
        // 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00

        // 'Berserk', 128x32px
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x01, 0xf7, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x9f, 0x00, 0x03, 0xe3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x0f, 0x80, 0x07, 0xc0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x07, 0xc0, 0x0f, 0x80, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x03, 0xe0, 0x1f, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x01, 0xf0, 0x3e, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x78, 0x3c, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0xf8, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x7e, 0xf8, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xfc, 0x7c, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x01, 0xf8, 0x3e, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x07, 0xe0, 0x1f, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x0f, 0xc0, 0x0f, 0xc0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xbf, 0x80, 0x07, 0xe1, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x01, 0xf7, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

        // 'Berserk', 128x32px
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xf0,
        // 0x78, 0x38, 0x3c, 0x7c, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x1e, 0x3e, 0x7c, 0x7c,
        // 0xf8, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x8c, 0x86, 0x87, 0x83, 0x81, 0x81, 0x80, 0x80,
        // 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x83, 0x87, 0x87, 0x8f, 0xbe, 0xfc, 0xf8, 0xf0, 0xe0, 0xe0,
        // 0xf0, 0xf0, 0xfc, 0xfe, 0x9f, 0x8f, 0x87, 0x83, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        // 0x80, 0x81, 0x83, 0x87, 0x8f, 0x9e, 0xbc, 0xf8, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x33, 0x63, 0xe3, 0xc3, 0x83, 0x03, 0x03,
        // 0x03, 0x03, 0x03, 0x03, 0x03, 0x83, 0x83, 0xc3, 0xe3, 0xf3, 0xfb, 0x7b, 0x7f, 0x3f, 0x1f, 0x0f,
        // 0x1f, 0x3f, 0x7f, 0xff, 0xf3, 0xe3, 0xc3, 0x83, 0x83, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
        // 0x03, 0x83, 0xc3, 0xc3, 0xe3, 0xf3, 0x7b, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e,
        // 0x1e, 0x3c, 0x3e, 0x3e, 0x1f, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x0f, 0x1f, 0x3e, 0x3c, 0x78, 0x7c, 0x3c, 0x1e,
        // 0x0f, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#ifdef IS_LEFT

// 'ougi1 - left', 128x32px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07,
0x83, 0xc1, 0xe0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xc0,
0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xc0, 0xe0, 0xf8, 0xfc, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x7f, 0x7f, 0x7f,
0x7f, 0x3f, 0x3f, 0x3f, 0x3e, 0x3e, 0x3c, 0x00, 0x38, 0x38, 0x30, 0x30, 0x30, 0x20, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0x3f, 0x83, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xcc, 0xec, 0xe0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0,
0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xe0, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0x03, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf1, 0xe1, 0xc1, 0x81, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#else

// 'ougi1 - right', 128x32px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0,
0xc0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xf8, 0xf0, 0xe0, 0xc1, 0x83,
0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x20, 0x30, 0x30, 0x30, 0x38, 0x38, 0x00, 0x3c, 0x3e, 0x3e, 0x3f, 0x3f, 0x3f, 0x7f,
0x7f, 0x7f, 0x7f, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xfc, 0xf8, 0xe0, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0,
0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xe0, 0xec, 0xcc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x83, 0x3f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x81, 0xc1, 0xe1, 0xf1, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#endif
    };
    oled_write_raw_P(my_logo, sizeof(my_logo));
}

uint16_t logo_timer = 0;
bool is_rendering_logo = false;

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
        oled_render_logo();
        is_rendering_logo = true;
        return true;
    }
    return false;
}
#endif

#define MAX_LINE 4

bool oled_task_user(void) {
    if (is_keyboard_master()) {

#ifdef RENDER_LOGO
        if(try_render_logo()){
            return false;
        }
#endif

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
            oled_write_ln(read_keylog(), false);
            lines += 1;
        }

        if(lines < MAX_LINE) {
            oled_write_ln(read_keylogs(), false);
            lines += 1;
        }
#endif
    }
    else {
#ifdef RENDER_LOGO
#ifdef NO_LOGO_TIMEOUT
        oled_clear();
#endif
        oled_render_logo();
#endif
        return true;
    }

    return false;
}
#endif // OLED_ENABLE

static bool combo_status_before_game_layer;

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record){
#ifdef OLED_ENABLE
#ifdef SET_KEYLOG
    set_keylog(keycode, record);
#endif

#ifdef RENDER_LOGO
    reset_logo_timer();
#endif
#endif

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
