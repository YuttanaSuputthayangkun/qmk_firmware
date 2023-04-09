#pragma once

#include QMK_KEYBOARD_H
#include "jugemu.h"

bool is_socd_enabled(void);
void toggle_socd(void);
bool process_record_user_socd(uint16_t keycode, keyrecord_t *record);
void init_socd(void);
