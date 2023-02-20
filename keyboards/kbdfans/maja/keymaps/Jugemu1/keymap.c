#include QMK_KEYBOARD_H

#include "jugemu.h"
#include "custom_combo.h"
#include "tap_hold.h"

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _READING,
};

#define T_BASE DF(_QWERTY)
#define T_READING TG(_READING)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
		[_QWERTY] = LAYOUT( /* Base */
			QK_GESC,       KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   TD_AUDIO,
		    KC_TAB,        KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS,   KC_VOLU,
			KC_LCTL,       KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,    KC_VOLD,
		    KC_LSFT,       KC_Z,     KC_X,     KC_C,  KC_V,  KC_B,  XXXXXXX, KC_N,  KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
		    KC_LCTL,                 KC_LALT,  KC_SPC,      MO(_LOWER),          MO(_RAISE),           KC_LGUI,            KC_LEFT, KC_DOWN,   KC_RIGHT),

		// [1] = LAYOUT( /* FN */
		// 	QK_GESC,       KC_F1,    KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  QK_BOOT,  KC_HOME,
		//     KC_TRNS,       RGB_TOG,  RGB_MOD, RGB_HUI,RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_PSCR, KC_SCRL,  KC_PAUS, QK_BOOT,  KC_PGUP,
		// 	CTL_T(KC_CAPS),RGB_SPI,  RGB_SPD, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          EE_CLR,   KC_PGDN,
		//     KC_LSFT,       KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_VOLU, KC_MUTE,
		//     KC_TRNS,                 KC_TRNS, KC_TRNS,         KC_TRNS,           KC_TRNS,         KC_TRNS,                    KC_MPRV, KC_VOLD,  KC_MNXT),

		[_LOWER] = LAYOUT(
            _______,       KC_VOLD,  KC_VOLU,  TD_AUDIO,    _______,    _______,          _______,    _______,    _______,    _______,    _______,    _______,    _______,  _______,   _______,
            KC_F1,         KC_F2,    KC_F3,    KC_F4,       KC_F5,      KC_F6,            KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     _______,  _______,   _______,
            TD(TD_LCTL_GRV),KC_EXLM, KC_AT,    KC_HASH,     KC_DLR,     KC_PERC,          KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_TILD,              _______,   _______,
            _______,       _______,  _______,  _______,     _______,    _______, XXXXXXX, KC_UNDS,    KC_PLUS,    KC_LCBR,    KC_RCBR,    KC_PIPE,    _______,    _______,
		    _______,                 _______,  _______,     _______,             MO(_ADJUST),        _______,                                         _______,    _______,  _______),

		[_RAISE] = LAYOUT(
            _______,       _______,  _______,  _______,     _______,    _______,          _______,    _______,    _______,    _______,    _______,    _______,    _______,  _______,   _______,
            KC_GRV,        KC_1,     KC_2,     KC_3,        KC_4,       KC_5,             KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_VOLU,    _______,  _______,   _______,
            TD(TD_RCTL_F1),KC_F2,    KC_F3,    KC_F4,       KC_F5,      KC_F6,            KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    _______,    KC_VOLD,              _______,   _______,
            (TD_LSFT_F7),  KC_F8,    KC_F9,    KC_F10,      KC_F11,     KC_F12,  XXXXXXX, KC_PLUS,    KC_MINS,    KC_EQL,     KC_LBRC,    KC_RBRC,    KC_BSLS,    _______,
		    _______,                 _______,  _______,     MO(_ADJUST),         _______,        _______,                                             _______,    _______,  _______),

		[_ADJUST] = LAYOUT(
            QK_BOOT,       XXXXXXX,  XXXXXXX,  XXXXXXX,     T_READING,  T_BASE,           XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,   CK_TD_MODE,
            XXXXXXX,       XXXXXXX,  KC_INS,   KC_HOME,     KC_PGUP,    XXXXXXX,          XXXXXXX,    KC_KP_7,    KC_KP_8,    KC_KP_9,    XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,   XXXXXXX,
            TD(TD_RCTL_F1),KC_F2,    KC_F3,    KC_F4,       KC_F5,      KC_F6,            KC_DOT,     KC_KP_4,    KC_KP_5,    KC_KP_6,    XXXXXXX,    XXXXXXX,              _______,   _______,
            (TD_LSFT_F7),  KC_F8,    KC_F9,    KC_F10,      KC_F11,     KC_F12,  XXXXXXX, KC_KP_0,    KC_KP_1,    KC_KP_2,    KC_KP_3,    XXXXXXX,    XXXXXXX,    _______,
		    _______,                 _______,  _______,     _______,             _______,        _______,                                             _______,    _______,  _______),

		[_READING] = LAYOUT(
			KC_ESC,        KC_HOME,  KC_2,     KC_END,   KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_HOME,
		    KC_TAB,        KC_PGUP,  KC_UP,    KC_PGDN,  KC_HOME,KC_T, KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS,   KC_PGUP,
			CTL_T(KC_CAPS),KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_END,KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,    KC_PGDN,
		    KC_LSFT,       KC_Z,     KC_X,     KC_C,     KC_V,  KC_B,  T_READING,KC_N, KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
		    _______,                 _______,  _______,     _______,         _______,        _______,                                         _______,    _______,  _______),
 };

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record){
    return true;
}
