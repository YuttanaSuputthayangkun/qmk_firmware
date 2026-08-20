#pragma once

// how long before a tap becomes a hold
#undef TAPPING_TERM
#define TAPPING_TERM 200

// makes tap and hold keys work better for fast typers who don't want
// tapping term set above 500
// #define PERMISSIVE_HOLD

// tap anyway, even after TAPPING_TERM, if there was no other key
// interruption between press and release
// #define RETRO_TAPPING

// // how many taps before triggering the toggle
// #undef ONESHOT_TAP_TOGGLE
// #define ONESHOT_TAP_TOGGLE 2

// // how long before oneshot modifier key times out (currently only shift)
// #undef ONESHOT_TIMEOUT
// #define ONESHOT_TIMEOUT 2000

#define COMBO_TERM 15 // window in milliseconds to trigger combo
#define COMBO_TERM_PER_COMBO
#define COMBO_MUST_HOLD_MODS

#define EECONFIG_MODE_INDEX (uint8_t *)19
#define EECONFIG_COMBO_INDEX (uint8_t *)20
#define EECONFIG_TAP_HOLD_INDEX (uint8_t *)21

#define ARROW_LAYER 2

#define TAP_HOLD_ENABLE

#define ENABLE_CUSTOM_OLED_BY_DEFAULT

#define ENCODER_RESOLUTIOns_left { 1, 1 }
#define ENCODER_RESOLUTIONS_RIGHT { 1, 1 }

// OLED

#define RENDER_LOGO
#define LOGO_START_DURATION 10000
#define LOGO_TYPE logo_type_ougi_1      // refered to enum in oled_logo.c
// #define SET_KEYLOG defined(OLED_ENABLE) && defined(DEBUG_OLED_ENABLE)

#define ENABLE_CUSTOM_INTERACTION_TIMEOUT
#define INTERACTION_TIMEOUT_DURATION 180000

// logo resources:
// https://javl.github.io/image2cpp
// https://docs.splitkb.com/product-guides/oled-displays
// https://joric.github.io/qle
// https://www.toolpkg.com/dither

#undef ARROW_LAYER
#define ARROW_LAYER 2

#define OLED_BRIGHTNESS 20
// #define OLED_TIMEOUT 60000
// #define OLED_FADE_OUT