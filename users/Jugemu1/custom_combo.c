#include "jugemu.h"
#include "eeconfig.h"
#include "eeprom.h"
#include "tap_hold.h"

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
    CMB_WR,
    CMB_WF,
    CMB_QZ,
    CMB_ZW,
    CMB_WT,
    CMB_WG,

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
const uint16_t PROGMEM cmb_wr[]   = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM cmb_wf[]   = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM cmb_qz[]   = {KC_Q, KC_Z, COMBO_END};
const uint16_t PROGMEM cmb_zw[]   = {KC_Z, KC_W, COMBO_END};
const uint16_t PROGMEM cmb_wt[]   = {KC_W, KC_T, COMBO_END};
const uint16_t PROGMEM cmb_wg[]   = {KC_W, KC_G, COMBO_END};

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
    [CMB_WR] = COMBO(cmb_wr, KC_PGUP),
    [CMB_WF] = COMBO(cmb_wf, KC_PGDN),
    [CMB_QZ] = COMBO(cmb_qz, KC_INSERT),
    [CMB_ZW] = COMBO(cmb_zw, KC_DEL),
    [CMB_WT] = COMBO(cmb_wt, KC_HOME),
    [CMB_WG] = COMBO(cmb_wg, KC_END),
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

        // left
        case CMB_WR:
        case CMB_WF:
        case CMB_QZ:
        case CMB_ZW:
        case CMB_WT:
        case CMB_WG:
            return 30;

        // right
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
