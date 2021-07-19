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

#pragma once

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 150
  #define RGBLIGHT_LAYERS
  //#define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_EFFECT_BREATHING
#endif

#define EE_HANDS

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 170

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
//#define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

#define COMBO_COUNT 2
#define COMBO_TERM 300

// Left-hand home row mods
#define HOME_A LSFT_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LCTL_T(KC_F)
#define HOME2_A KC_LCBR
#define HOME2_S LALT_T(KC_LBRC)
#define HOME2_D LGUI_T(KC_RBRC)
#define HOME2_F KC_RCBR
#define HOME_G RALT_T(KC_G)
#define HOME_V RALT_T(KC_V)

// Right-hand home row mods
#define HOME_J RCTL_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RSFT_T(KC_SCLN)
#define HOME2_J RCTL_T(KC_4)
#define HOME2_K RGUI_T(KC_5)
#define HOME2_L LALT_T(KC_6)
#define HOME2_SCLN RSFT_T(KC_KP_PLUS)
#define HOME_H RALT_T(KC_H)
#define HOME_M RALT_T(KC_M)

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
#define SPLIT_USB_DETECT
#define NO_USB_STARTUP_CHECK
