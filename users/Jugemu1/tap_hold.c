#include "tap_hold.h"
#include "eeconfig.h"
#include "eeprom.h"
#include "keycodes.h"

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
    set_tap_hold(
        tap_hold_enabled()
    );
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
