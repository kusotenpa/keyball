#include QMK_KEYBOARD_H

#include "quantum.h"


#ifdef COMBO_ENABLE
const uint16_t PROGMEM cb_left[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM cb_right[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM cb_prev[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM cb_next1[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM cb_next2[] = {KC_BTN1, KC_BTN2, COMBO_END};

combo_t key_combos[] = {
  COMBO(cb_left, KC_LEFT),
  COMBO(cb_right, KC_RIGHT),
  COMBO(cb_prev, LCMD(LSFT(KC_LBRC))),
  COMBO(cb_next1, LCMD(LSFT(KC_RBRC))),
  COMBO(cb_next2, LCMD(LSFT(KC_RBRC))),
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_TAB,       KC_Q,        KC_W,      KC_E,      KC_R,      KC_T,                                        KC_Y     , KC_U     , KC_I     , KC_O     ,         KC_P     , KC_BSPC ,
    KC_LCTL,     KC_A,      KC_S,      KC_D,      KC_F,      KC_G,                                           KC_H     , KC_J ,    KC_K     , KC_L     , KC_SCLN  , KC_ENT  ,
    MT(MOD_LSFT,KC_ESC), KC_Z,         KC_X,      KC_C,     KC_V,   KC_B ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   ,         KC_SLSH  , KC_QUOT  ,
                 KC_LALT,    LT(3, KC_MINUS),   KC_LGUI,   KC_LNG2,  KC_LNG1,                  LM(1,MOD_LGUI),  LT(1,KC_SPC),   _______,   _______,    KC_GRV
  ),

  [1] = LAYOUT_universal(
    _______ ,  KC_EXLM   , KC_AT    , KC_PIPE   , KC_LCBR    , KC_RCBR    ,                                    _______, KC_1    , KC_2    , KC_3    , _______   , _______   ,
    KC_LGUI ,  KC_ASTR , KC_DLR  , KC_AMPR   , KC_LPRN   , KC_RPRN   ,                                         KC_0, KC_4  , KC_5     , KC_6   , _______  , KC_ENT   ,
    _______ ,  KC_HASH , KC_CIRC  , KC_PERC , KC_LBRC  , KC_RBRC  ,                                         KC_DOT  , KC_7    , KC_8     ,KC_9 , _______  , _______  ,
                         KC_BSLS,   KC_PPLS,  KC_EQL,    KC_UP,     KC_DOWN,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
      _______, _______     , _______   , _______     , _______  ,  _______,                                       _______,   _______  ,_______  , _______  ,_______  , _______  ,
      _______, _______     , _______    , _______     , _______  , _______,                                        _______, KC_BTN1  ,KC_BTN2,SCRL_MO  , _______  ,_______  ,
      _______, _______     , _______    , _______     ,_______,  _______,                                          _______,  _______, LGUI(KC_LBRC)   ,LGUI(KC_RBRC),_______,_______,
                  _______     , _______  , _______  ,         _______  , _______  ,                   _______   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , SSNP_FRE  , SCRL_MO  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , _______  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"
#include "custom_oled.c"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
  if (last_input_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return false;
    }

    if (!is_oled_on()) {
        return false;
    }

    if (is_keyboard_master()) {
        oledkit_render_info_user();
    } else {
         oled_render_custom();
    }

    return false;
}

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
