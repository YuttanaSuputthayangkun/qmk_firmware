/* Copyright 2020 Koichi Katano
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "jugemu.h"

enum layer_names {
    _BASE = 0,
    _FN,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// lower mod
#define LM_TAB LT(_LOWER, KC_TAB)
#define LM_Z LT(_LOWER, KC_Z)

// raise mod
#define LM_QUOT LT(_RAISE, KC_QUOT)
#define LM_SLSH LT(_RAISE, KC_SLSH)

// raise mod activated
#define LM_GRV LT(_ADJUST, KC_GRV)
#define LM_F8 LT(_ADJUST, KC_F8)

// lower mod activated
#define LM_TILD LT(_ADJUST, KC_TILD)
// #define LM_UP LT(_ADJUST, KC_UP)
#define LM_RCBR LT(_ADJUST, KC_RCBR)

#define MO_LOW MO(_LOWER)
#define MO_RIS MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_60_ansi_split_bs_rshift(
        KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,     KC_EQL,     KC_GRV,    KC_BSPC,
        LM_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,    KC_RBRC,                KC_BSLS,
        KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LM_QUOT,                             KC_ENT,
        KC_LSFT,    LM_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  LM_SLSH,                           KC_UP,    MO(_FN),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                           _______,   KC_LEFT,   KC_DOWN,   KC_RIGHT
    ),
    [_FN] = LAYOUT_60_ansi_split_bs_rshift(
        QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,KC_VOLD, KC_VOLU,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         TD_AUDIO,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       CK_TD_MODE, _______,
        _______, _______, _______,                            _______,                                     _______, _______, _______, _______
    ),

    // [_FN] = LAYOUT_60_ansi_split_bs_rshift(
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
    //     _______, _______, _______,                            _______,                                     _______, _______, _______, _______
    // ),


    [_LOWER] = LAYOUT_60_ansi_split_bs_rshift(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,          _______,
TD(TD_LCTL_GRV), KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, LM_TILD,                   _______,
        _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, LM_RCBR,                   _______, _______,
        _______, _______, _______,                            _______,                                     _______, _______, _______, _______
    ),

    // [_RAISE] = LAYOUT(
    // _______,         _______, _______, _______, _______, _______,                       KC_VOLD, KC_VOLU,TD_AUDIO,CK_PPSCR,  CK_FPSCR,  KC_DEL,
    // KC_GRV,             KC_1,     KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,      KC_0, KC_VOLU,
    // TD(TD_RCTL_F1),    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_LEFT, KC_DOWN,   KC_UP,   KC_RGHT, _______, KC_VOLD,
    // TD(TD_LSFT_F7),    KC_F8,    KC_F9,  KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS,  KC_EQL, KC_LBRC,   KC_RBRC, _______,
    //                                     _______, _______, _______,   _______, _______,  _______, _______, _______
    // ),

    [_RAISE] = LAYOUT_60_ansi_split_bs_rshift(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
         LM_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, _______,          KC_VOLU,
 TD(TD_RCTL_F1),   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______,                   KC_VOLD,
 TD(TD_LSFT_F7),   LM_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_PLUS, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC,                   _______, _______,
        _______, _______, _______,                            _______,                                     _______, _______, _______, _______
    ),

    // [_ADJUST] = LAYOUT(
    // XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, T_EROGE,T_READING,                   T_BASE, T_GENSH,  T_GAME, XXXXXXX, XXXXXXX, XXXXXXX,
    // XXXXXXX, XXXXXXX,  KC_INS, KC_HOME, KC_PGUP, XXXXXXX,                   XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, XXXXXXX, XXXXXXX,
    // XXXXXXX, XXXXXXX,  KC_DEL,  KC_END, KC_PGDN, XXXXXXX,                    KC_DOT, KC_KP_4, KC_KP_5, KC_KP_6, XXXXXXX, XXXXXXX,
    // XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, XXXXXXX, XXXXXXX,
    //                             _______, _______, _______, _______, _______,  _______, _______, _______
    // ),

    [_ADJUST] = LAYOUT_60_ansi_split_bs_rshift(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  KC_INS, KC_HOME, KC_PGUP, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, _______, _______, _______,          _______,
        _______, _______,  KC_DEL,  KC_END, KC_PGDN, _______,  KC_DOT, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, _______,                   _______, _______,
        _______, _______, _______,                            _______,                                     _______, _______, _______, _______
    ),
};

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record){
    return true;
}
