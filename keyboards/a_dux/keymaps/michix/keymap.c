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
  CB_COPY,
  CB_PASTE,
  CB_TAB
};

const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_W, KC_R, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [CB_COPY] = COMBO_ACTION(copy_combo),
  [CB_PASTE] = COMBO_ACTION(paste_combo),
  [CB_TAB] = COMBO_ACTION(tab_combo)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CB_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;
    case CB_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
    case CB_TAB:
      if (pressed) {
        tap_code16(KC_TAB);
      }
      break;
  }
}

/* Tap dancing */
enum {
    TD_Q_ESC
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
};

/* Layer color effects */
enum layers {
    _QWERTY = 0,
    _LAYER1,
    _LAYER2,
    _LAYER3,
    _LAYER4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  NO    |
 * |        |    <TAB>    |      |      |      |                              |   Y  |   U  |   I  |   O  |   P  |  NO    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   Q    |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  P     |
 * | 2:ESC  |LShift|  ALT | GUI  | CTRL |ALTGR |                              |ALTGR | CTRL |  GUI |  ALT |RShift|        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |   Z    |   Z  |   X  |   C  |   V  |   B  |      |      |  |      |      |   N  |   M  | ,  < | . >  | /  ? | /  ?   |
 * |        |      |      |      |ALTGR |      |      |      |  |      |      |      |ALTGR |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | ESC  |Space |Enter |      |  |      |Del   |Backsp|Teams |      |
 *                        |      |      |Layr2 |Layr4 |      |  |      |Layr3 |Layr1 |Mute  |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      TD(TD_Q_ESC), KC_W, KC_E, KC_R, KC_T,               KC_Y, KC_U, KC_I, KC_O, KC_P,
      HOME_A, HOME_S, HOME_D, HOME_F, HOME_G,     HOME_H, HOME_J, HOME_K, HOME_L, HOME_SCLN,
      KC_Z, KC_X, KC_C, HOME_V, KC_B,             KC_N, HOME_M, KC_COMM, KC_DOT, KC_SLSH,

      LT(_LAYER2, KC_SPC), LT(_LAYER4, KC_ENT),
      LT(_LAYER3, KC_DEL), LT(_LAYER1, KC_BSPACE)
    ),
/*
 * Layer1: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  #   |  $   |  %   |                              |  ^   |  &   |  *   |  (   |  )   |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   !    |  {   |  [   |  ]   |  }   |  '"  |                              |  <-  |  v   |  ^   |  ->  |  NO  |  | \   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  (   |  <   |  >   |  )   |  `   |      |      |  |      |      | HOME |PGDOWN|PGUP  | END  |  \   |   NO   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LAYER1] = LAYOUT(
      KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                                  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN,
      KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, KC_QUOT,                                                  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_RSHIFT,
      KC_LPRN, LSFT(KC_COMM), LSFT(KC_DOT), KC_RPRN, KC_GRV,                                        KC_HOME, KC_PGDOWN,  KC_PGUP, KC_END, KC_BSLS,
                                           _______, _______,                                        _______, _______
    ),
/*
 * Layer2: Numbers
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   1    |  {   |  [   |  ]   |  }   |  =   |                              |  -   |  4   |  5   |  6   |  +   |   0    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  (   |  <   |  >   |  )   |  |   |      |      |  |      | '"   |  .   |  1   |  2   |  3   |  /   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |Enter |  0   |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LAYER2] = LAYOUT(
      KC_1, KC_2,  KC_3, KC_4,  KC_5,                                                   KC_6, KC_7, KC_8, KC_9,  KC_0,
      HOME2_A, HOME2_S, HOME2_D, HOME2_F, KC_EQUAL,                                     KC_MINS, HOME2_J, HOME2_K,  HOME2_L, HOME2_SCLN,
      KC_LPRN, LSFT(KC_COMM), LSFT(KC_DOT), KC_RPRN, KC_PIPE,                           KC_DOT, KC_1,  KC_2, KC_3, KC_SLSH,
                                 _______, _______,                                      KC_ENT, KC_0
    ),
/*
 * Layer3: Function Keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |  F6  |  F7  |  F8  |  F9  | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  F1    |  F11 |  F12 |      |      |      |                              |  -   |  F4  |  F5  |  F6  |      |  F10   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |  F1  |  F2  |  F3  |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LAYER3] = LAYOUT(
      KC_F1, KC_F2,  KC_F3, KC_F4,  KC_F5,                                                  KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
      KC_F11, KC_F12, _______, _______, _______,                                            _______, KC_F4, KC_F5,  KC_F6, _______,
      _______, _______, _______, _______, _______,                                          _______, KC_F1,  KC_F2, KC_F3, _______,
                                 _______, _______,                                          _______, _______
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
      _______,	_______, _______, _______, _______,                                        _______, _______, _______, _______, _______,
      KC_MS_BTN5, KC_MS_BTN4, KC_MS_BTN2, KC_MS_BTN1, KC_MS_BTN3,                          KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,
      KC_MUTE, _______, KC_VOLD, KC_VOLU, _______,                                         KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, _______,
                                 _______, _______,                                         _______, _______
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

