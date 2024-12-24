#include QMK_KEYBOARD_H
#include "version.h"

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  ST_MACRO_0,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_PSCR,                                        KC_EQUAL,       KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSPC,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_AUDIO_MUTE,                                  KC_AUDIO_VOL_UP,KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,
    KC_CAPS,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_ENTER,
    SC_LSPO,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_MINUS,                                       KC_AUDIO_VOL_DOWN,KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       SC_RSPC,
    KC_LEFT_CTRL,   KC_LEFT_GUI,    KC_LEFT_ALT,    KC_UP,          KC_DOWN,                                                                                                        KC_HYPR,        KC_GRAVE,       KC_LEFT,        KC_RIGHT,       KC_MEH,
                                                                                                    KC_LBRC,        ST_MACRO_0,     KC_PAGE_UP,     KC_RBRC,
                                                                                                                    KC_HOME,        KC_PGDN,
                                                                                    KC_SPACE,       KC_QUOTE,       KC_END,         KC_INSERT,      KC_DELETE,      KC_SPACE
  ),
};


const uint16_t PROGMEM combo0[] = { KC_HYPR, KC_1, COMBO_END};
const uint16_t PROGMEM combo1[] = { KC_HYPR, KC_2, COMBO_END};
const uint16_t PROGMEM combo2[] = { KC_HYPR, KC_3, COMBO_END};
const uint16_t PROGMEM combo3[] = { KC_HYPR, KC_4, COMBO_END};
const uint16_t PROGMEM combo4[] = { KC_HYPR, KC_5, COMBO_END};
const uint16_t PROGMEM combo5[] = { KC_HYPR, KC_EQUAL, COMBO_END};
const uint16_t PROGMEM combo6[] = { KC_HYPR, KC_6, COMBO_END};
const uint16_t PROGMEM combo7[] = { KC_HYPR, KC_7, COMBO_END};
const uint16_t PROGMEM combo8[] = { KC_HYPR, KC_8, COMBO_END};
const uint16_t PROGMEM combo9[] = { KC_HYPR, KC_9, COMBO_END};
const uint16_t PROGMEM combo10[] = { KC_HYPR, KC_0, COMBO_END};
const uint16_t PROGMEM combo11[] = { KC_HYPR, KC_PSCR, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_F1),
    COMBO(combo1, KC_F2),
    COMBO(combo2, KC_F3),
    COMBO(combo3, KC_F4),
    COMBO(combo4, KC_F5),
    COMBO(combo5, KC_F12),
    COMBO(combo6, KC_F6),
    COMBO(combo7, KC_F7),
    COMBO(combo8, KC_F8),
    COMBO(combo9, KC_F9),
    COMBO(combo10, KC_F10),
    COMBO(combo11, KC_F11),
};


extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {188,255,255}, {0,245,245}, {0,245,245}, {188,255,255}, {152,255,255} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_3) ));
    }
    break;

    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

uint8_t layer_state_set_user(uint8_t state) {
    uint8_t layer = biton(state);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};



