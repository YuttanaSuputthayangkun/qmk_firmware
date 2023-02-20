/* Copyright 2021 wuquestudio
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

#include "jugemu.h"
#include "custom_combo.h"
#include "tap_hold.h"

#include QMK_KEYBOARD_H

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _READING,
    _CONFIG,
    _GAME,
    _WIN,
    _MAC,
};

#define T_BASE DF(_QWERTY)
#define T_READ TG(_READING)
#define T_GAME TG(_GAME)
#define T_WIN TG(_WIN)
#define T_MAC TG(_MAC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // [0] = LAYOUT_all(
    //     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,    KC_INS, KC_PGUP,
    //     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_DEL, KC_PGDN,
    //     KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    //     KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,             KC_UP,
    //     KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           KC_SPC,           KC_SPC,           KC_RALT, MO(1),   KC_RCTL,             KC_LEFT, KC_DOWN, KC_RGHT
    // ),
    // [1] = LAYOUT_all(
    //     KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,    _______, QK_BOOT,
    //     _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______,             _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
    //     _______, _______, _______,          _______,          _______,          _______,          _______, _______, _______,             _______, _______, _______
    // ),
    [_QWERTY] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,  TD_AUDIO, KC_VOLU,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,         CK_TD_MODE, KC_VOLD,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,MO(_CONFIG),          KC_UP,
        KC_LCTL, KC_LGUI,KC_LALT,  MO(_LOWER),        KC_SPC,    MO(_RAISE),           KC_RALT, MO(1),   KC_RCTL,             KC_LEFT, KC_DOWN, KC_RGHT
        // KC_LCTL, KC_LGUI,KC_LALT,       KC_SPC,    MO(_LOWER),    MO(_RAISE),           KC_RALT, MO(1),   KC_RCTL,             KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_LOWER] = LAYOUT_all(
        _______,  KC_VOLD,    KC_VOLU,   TD_AUDIO,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,  _______, _______,    _______, _______,
        KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,     KC_F10,     KC_F11,     KC_F12,    _______, _______,             _______, _______,
        TD(TD_LCTL_GRV), KC_EXLM,KC_AT,   KC_HASH,     KC_DLR,    KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_TILD,          _______,
        _______,  _______,    _______,    _______,    _______,    _______,    XXXXXXX,    KC_UNDS,    KC_PLUS,    KC_LCBR,    KC_RCBR,    KC_PIPE, _______, _______,             _______,
        _______,  _______,    _______,          _______,              _______,            MO(_ADJUST),          _______, _______, _______,             _______, _______, _______
    ),
    [_RAISE] = LAYOUT_all(
        _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, _______,  _______, _______,    _______, _______,
        KC_GRV,      KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,    KC_VOLU, _______, _______,             _______, _______,
        TD(TD_RCTL_F1),KC_F2,   KC_F3,      KC_F4,      KC_F5,      KC_F6,    KC_LEFT,    KC_DOWN,      KC_UP,    KC_RGHT,    _______,    KC_VOLD,          _______,
 (TD_LSFT_F7),_______, KC_F8,   KC_F9,     KC_F10,     KC_F11,     KC_F12,    KC_PLUS,    KC_MINS,     KC_EQL,    KC_LBRC,    KC_RBRC,    KC_BSLS,  _______,             _______,
        _______,  _______,    _______,          MO(_ADJUST),          _______,          _______,          _______, _______, _______,             _______, _______, _______
        // _______,  _______,    _______,       _______,      MO(_ADJUST),          _______,          _______, _______, _______,             _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_all(
        QK_BOOT, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,     T_READ,     T_BASE,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  KC_INS,  KC_HOME,  KC_PGUP,    XXXXXXX,    XXXXXXX,    KC_KP_7,    KC_KP_8,    KC_KP_9,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  KC_DEL,   KC_END,  KC_PGDN,    XXXXXXX,     KC_DOT,    KC_KP_4,    KC_KP_5,    KC_KP_6,    XXXXXXX, XXXXXXX,          XXXXXXX,
 XXXXXXX, _______, XXXXXXX,XXXXXXX, XXXXXXX,  XXXXXXX,    XXXXXXX,    KC_KP_0,    KC_KP_1,    KC_KP_2,    KC_KP_3,    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______,          _______,           _______,           _______,           _______, MO(1),   _______,             XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_READING] = LAYOUT_all(
        KC_ESC,   KC_HOME,    KC_2,  KC_END,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,  TD_AUDIO, KC_VOLU,
        KC_TAB,   KC_PGUP,   KC_UP, KC_PGDN,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,            _______, KC_VOLD,
        KC_CAPS,  KC_LEFT, KC_DOWN,KC_RIGHT,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT,  KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, _______,               KC_UP,
        _______, _______, _______,          _______,          _______,          _______,              _______, _______,  T_READ,             _______, _______, _______
    ),
    [_CONFIG] = LAYOUT_all(
        QK_BOOT,   T_WIN,   T_MAC,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,   _______, T_GAME,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______,             _______, T_READ,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______, _______, _______,          _______,          _______,          _______,          _______, _______, _______,             _______, _______, _______
    ),
    [_GAME] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______, _______,    _______, _______,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, _______,             _______, _______,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          _______,
        KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, _______,               KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           KC_SPC,           KC_SPC,           KC_RALT, _______,  T_GAME,             KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_WIN] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______, KC_LGUI, KC_LALT,          _______,          _______,          _______,          _______, _______, _______,             _______, _______, _______
    ),
    [_MAC] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______,
        _______, KC_LALT, KC_LGUI,          _______,          _______,          _______,          _______, _______, _______,             _______, _______, _______
    )
};

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record){
    return true;
}
