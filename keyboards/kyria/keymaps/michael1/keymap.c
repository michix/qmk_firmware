/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

/* Combos */
enum combo_events {
  ZC_COPY,
  XC_PASTE
};

const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [ZC_COPY] = COMBO_ACTION(copy_combo),
  [XC_PASTE] = COMBO_ACTION(paste_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case ZC_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;
    case XC_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
  }
}

/* Tap dancing */
/*enum {*/
    /*TD_A_ALTGRA,*/
    /*TD_O_ALTGRO,*/
    /*TD_U_ALTGRU,*/
    /*TD_C_COPY,*/
    /*TD_V_PASTE,*/
    /*TD_Z_UNDO*/
/*};*/

/*qk_tap_dance_action_t tap_dance_actions[] = {*/
    /*[TD_A_ALTGRA] = ACTION_TAP_DANCE_DOUBLE(KC_A, RALT(KC_A)),*/
    /*[TD_O_ALTGRO] = ACTION_TAP_DANCE_DOUBLE(KC_O, RALT(KC_O)),*/
    /*[TD_U_ALTGRU] = ACTION_TAP_DANCE_DOUBLE(KC_U, RALT(KC_U)),*/
    /*[TD_C_COPY] = ACTION_TAP_DANCE_DOUBLE(KC_C, LCTL(KC_C)),*/
    /*[TD_V_PASTE] = ACTION_TAP_DANCE_DOUBLE(KC_V, LCTL(KC_V)),*/
    /*[TD_Z_UNDO] = ACTION_TAP_DANCE_DOUBLE(KC_Z, LCTL(KC_Z))*/
/*};*/

/* Layer color effects */
enum layers {
    _QWERTY = 0,
    _LAYER1,
    _LAYER2,
    _LAYER3,
    _LAYER4
};

void keyboard_post_init_user(void) {
    rgblight_sethsv(HSV_GREEN);
    rgblight_mode(RGBLIGHT_MODE_BREATHING);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(state)) {
        case _QWERTY:
            rgblight_sethsv(HSV_GREEN);
            rgblight_mode(RGBLIGHT_MODE_BREATHING);
            break;
        case _LAYER1:
            rgblight_sethsv(HSV_SPRINGGREEN);
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _LAYER2:
            rgblight_sethsv(HSV_AZURE);
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _LAYER3:
            rgblight_sethsv(HSV_ORANGE);
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _LAYER4:
            rgblight_sethsv(HSV_PURPLE);
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        default:
            rgblight_sethsv(HSV_RED);
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
    }
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  NO    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  ESC   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |        |LShift|  ALT | GUI  | CTRL |ALTGR |                              |ALTGR | CTRL |  GUI |  ALT |RShift|  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   `    |   Z  |   X  |   C  |   V  |   B  | ESC  |      |  |      | ' "  |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * | ALTGR  |      |      |      |ALTGR |      |      |      |  |      |      |      |ALTGR |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | Teams|Space |Enter | TAB  |  |  `   |Del   |Backsp|Teams |      |
 *                        |      | Share|Layr2 |Layr4 |Layer3|  |Layer3|Layr4 |Layr1 |Mute  |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,               KC_Y, KC_U, KC_I, KC_O, KC_P, KC_NO,
      KC_ESC, HOME_A, HOME_S, HOME_D, HOME_F, HOME_G,     HOME_H, HOME_J, HOME_K, HOME_L, HOME_SCLN, KC_QUOT,
      RALT_T(KC_GRV), KC_Z, KC_X, KC_C, HOME_V, KC_B, KC_ESC, _______, _______, KC_QUOT, KC_N, HOME_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,

      RGB_MODE_FORWARD,  RCS(KC_E), LT(_LAYER2, KC_SPC), LT(_LAYER4, KC_ENT), LT(_LAYER3, KC_TAB),
      LT(_LAYER3, KC_GRV), LT(_LAYER4, KC_DEL), LT(_LAYER1, KC_BSPACE), RCS(KC_M), RGB_MODE_REVERSE
    ),
/*
 * Layer1: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  #   |  $   |  %   |                              |  ^   |  &   |  *   |  (   |  )   |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  {   |  [   |  ]   |  }   |  NO  |                              |  <-  |  v   |  ^   |  ->  |  NO  |  NO    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  (   |  <   |  >   |  )   |  NO  |      |      |  |      |      | HOME |PGDOWN|PGUP  | END  |  \   |   NO   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LAYER1] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, KC_BSLS,
      _______, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, KC_NO,                                                    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_NO,   KC_NO,
      _______, KC_LPRN, LSFT(KC_COMM), LSFT(KC_DOT), KC_RPRN, KC_NO, _______, _______, _______, _______, KC_HOME, KC_PGDOWN,  KC_PGUP, KC_END,   KC_BSLS, KC_NO,
                                 _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______
    ),
/*
 * Layer2: Numbers
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  {   |  [   |  ]   |  }   |  =   |                              |  -   |  4   |  5   |  6   |  +   |  NO    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  (   |  <   |  >   |  )   |  |   |      |      |  |      |      |  .   |  1   |  2   |  3   |  /   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |Enter |  0   |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LAYER2] = LAYOUT(
      _______, KC_1, KC_2,  KC_3, KC_4,  KC_5,                                                  KC_6, KC_7, KC_8, KC_9,  KC_0, _______,
      _______, HOME2_A, HOME2_S, HOME2_D, HOME2_F, KC_EQUAL,                                     KC_MINS, HOME2_J, HOME2_K,  HOME2_L, HOME2_SCLN, KC_NO,
      _______, KC_LPRN, LSFT(KC_COMM), LSFT(KC_DOT), KC_RPRN, KC_PIPE, _______, _______, _______, _______, KC_DOT, KC_1,  KC_2, KC_3, KC_SLSH, _______,
                                 _______, _______, _______, _______, _______,  _______,  KC_ENT, KC_0, _______, _______
    ),
/*
 * Layer3: Function Keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |  F6  |  F7  |  F8  |  F9  | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F11 |  F12 |      |      |      |                              |  -   |  F4  |  F5  |  F6  |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |  F1  |  F2  |  F3  |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LAYER3] = LAYOUT(
      _______, KC_F1, KC_F2,  KC_F3, KC_F4,  KC_F5,                                                  KC_F6, KC_F7, KC_F8, KC_F9,  KC_F10, _______,
      _______, KC_F11, KC_F12, _______, _______, _______,                                     _______, KC_F4, KC_F5,  KC_F6, _______,   _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F1,  KC_F2, KC_F3, _______, _______,
                                 _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______
    ),
/*
 * Layer4: media, mouse
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | Btn5 | Btn3 | Btn2 | Btn1 | Btn4 |                              | Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | Mute |      | VolDn| VolUp|      |      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LAYER4] = LAYOUT(
      _______, _______, 	  _______,    _______,    _______,    _______,                                        _______,    _______,    _______,    _______,    _______,    _______,
      _______, KC_MS_BTN5, KC_MS_BTN4, KC_MS_BTN2, KC_MS_BTN1, KC_MS_BTN3,                                     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
      _______, KC_MUTE, _______, KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

void set_led_color(uint8_t hue, uint8_t sat, uint8_t val) {
    /*rgblight_sethsv_range(hue, sat, val, 0, RGBLED_NUM/2);*/
    /*rgblight_set(); // Utility functions do not call rgblight_set() automatically, so they need to be called explicitly.*/
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.3\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LAYER1:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case _LAYER2:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case _LAYER3:
            oled_write_P(PSTR("F-Keys\n"), false);
            break;
        case _LAYER4:
            oled_write_P(PSTR("Media/Mouse\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    /*oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);*/
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return true;
}
#endif
