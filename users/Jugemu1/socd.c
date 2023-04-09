#include "eeconfig.h"
#include "eeprom.h"
#include "socd.h"

volatile bool is_enabled = false;

bool is_socd_enabled(void){
    return is_enabled = eeprom_read_byte(EECONFIG_SOCD_INDEX);
}

void set_socd_enabled(bool new_value){
    is_enabled = new_value;
    eeprom_update_byte(EECONFIG_SOCD_INDEX, new_value);
}

void toggle_socd(void){
    bool new_value = !is_enabled;
    set_socd_enabled(new_value);
}

void init_socd(void){
    set_socd_enabled(
        is_socd_enabled()
    );
}

typedef struct{
    uint8_t keycode;
} direction_data;

typedef struct {
    direction_data directions[2];
    bool is_cancelling;
} direction_pair_data;

typedef enum {
    A_D = 0,
    W_S,
    LEFT_RIGHT,
    UP_DOWN,
    LAST,
} direction_pair_index;

direction_pair_data direction_pair_data_list[] = {
    [A_D] = {
        {
            { KC_A, },
            { KC_D, },
        }
    },
    [W_S] = {
        {
            { KC_W, },
            { KC_S, },
        }
    },
    [LEFT_RIGHT] = {
        {
            { KC_LEFT, },
            { KC_RIGHT, },
        }
    },
    [UP_DOWN] = {
        {
            { KC_UP, },
            { KC_DOWN, },
        }
    },
};

bool is_socd_cancel(uint16_t pair_index, uint16_t keycode, keyrecord_t *record){

    direction_pair_data pair_data = direction_pair_data_list[pair_index];

    bool is_match_0 = pair_data.directions[0].keycode == keycode;
    bool is_match_1 = pair_data.directions[1].keycode == keycode;
    if(!is_match_0 && !is_match_1){
        return false;
    }

    uint8_t other_key = is_match_0 ? pair_data.directions[1].keycode : pair_data.directions[0].keycode;
    if(!is_key_pressed(keyboard_report, other_key)){
        return false;
    }

    if(record->event.pressed){      // when the new key is pressed
        register_code(keycode);
        del_key(keycode);
        send_keyboard_report();

        unregister_code(other_key);
        add_key(other_key);
        send_keyboard_report();

        direction_pair_data_list[pair_index].is_cancelling = true;      // record cancellation
        return true;
    }else{      // when the new key is released
        if(!is_key_pressed(keyboard_report, other_key)){
            register_code(other_key);
        }
        direction_pair_data_list[pair_index].is_cancelling = false;
        return false;
    }

    return false;
}

bool process_record_user_socd(uint16_t keycode, keyrecord_t *record){
    if(!is_socd_enabled()){
        return true;
    }

    for(int16_t i=0 ; i < LAST ; ++i){
        bool is_canceled = is_socd_cancel(i, keycode, record);
        if(is_canceled){
            return false;
        }
    }
    return true;
}
