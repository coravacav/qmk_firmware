/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"

// clang-format off
enum layers{
  BASE,
  CAPS,
  CAPS_SPACE,
  FN,
};

enum custom_keycodes {
     MOD_SPC = SAFE_RANGE,
     RND_CASE,
     L33T_SPK,
};

static bool random_case_enabled = false;
static bool leet_speak_enabled = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_tkl_ansi(
     KC_ESC,         KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_PSCR,   KC_CTANA, UG_NEXT,
     KC_GRV,         KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,    KC_HOME,  KC_PGUP,
     KC_TAB,         KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,    KC_END,   KC_PGDN,
     MO(CAPS),       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
     KC_LSFT,        KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      KC_RSFT,             KC_UP,
     KC_LCTL,        KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RGUI,  MO(FN),   KC_RCTL,  KC_LEFT,   KC_DOWN,  KC_RGHT),

[CAPS] = LAYOUT_tkl_ansi(
     _______,         KC_F13,   KC_F14,  KC_F15,    KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24,            _______,   _______,  _______,
     _______,        KC_BSPC,   KC_DEL,  KC_ENT,   _______,  _______,  _______,  DM_REC1,  DM_REC2,  DM_RSTP,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
     _______,        MS_BTN1,   KC_F20, MS_BTN2,   KC_PGUP,  MS_WHLU,   KC_INS,  KC_BSPC,    KC_UP,   KC_DEL,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
     _______,        KC_HOME,   KC_END, MOD_SPC,   KC_PGDN,  MS_WHLD,   KC_ESC,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_ENT,  _______,            _______,
     _______,        DM_PLY1,  DM_PLY2,  KC_APP,   _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,             _______,
     _______,        _______,  _______,                                MO(CAPS_SPACE),                         _______,  _______,  _______,  _______,  _______,   _______,  _______),

[CAPS_SPACE] = LAYOUT_tkl_ansi(
     _______,        _______,  _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   _______,  _______,
     _______,        XXXXXXX,  XXXXXXX, XXXXXXX,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
     _______,        KC_BSPC,    KC_UP,  KC_DEL,   XXXXXXX,  _______,  _______,     KC_7,     KC_8,     KC_9,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
     _______,        KC_LEFT,  KC_DOWN, KC_RGHT,    KC_ENT,  _______,  _______,     KC_4,     KC_5,     KC_6,     KC_0,  _______,            _______,
     _______,        _______,  _______, _______,   _______,  _______,  _______,     KC_1,     KC_2,     KC_3,  _______,                      _______,             _______,
     _______,        _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,   _______,  _______),

[FN] = LAYOUT_tkl_ansi(
     XXXXXXX,          KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,            KC_MUTE,  XXXXXXX,   XXXXXXX,
     XXXXXXX,        BT_HST1,  BT_HST2,  BT_HST3,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MPLY,  KC_MSTP,   KC_VOLU,
     UG_TOGG,        UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MPRV,  KC_MNXT,   KC_VOLD,
     XXXXXXX,        UG_PREV , UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
     XXXXXXX,        RND_CASE, L33T_SPK, XXXXXXX,  XXXXXXX,  BAT_LVL,  NK_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,            XXXXXXX,
     XXXXXXX,        XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX),
};

bool is_alpha(uint16_t keycode) {
  return keycode >= KC_A && keycode <= KC_Z;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MOD_SPC:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_SPC);
      } else {
        unregister_code(KC_SPC);
        unregister_code(KC_LGUI);
      }
      return false;
    case RND_CASE:
      if (record->event.pressed) {
        random_case_enabled = !random_case_enabled;
      }
      return false;
    case L33T_SPK:
      if (record->event.pressed) {
        leet_speak_enabled = !leet_speak_enabled;
      }
      return false;
  }

  if (random_case_enabled && record->event.pressed && is_alpha(keycode)) {
    // If a letter key is pressed and random casing is enabled, send it with random casing
    if (rand() % 2) {
      register_code(KC_LSFT);
    }
    register_code(keycode);
    unregister_code(keycode);
    unregister_code(KC_LSFT);
    return false;
  }

  if (leet_speak_enabled && record->event.pressed && is_alpha(keycode)) {
    // If a letter key is pressed and random casing is enabled, send it with leet speak
    switch (keycode) {
      case KC_A:
        register_code(KC_4);
        unregister_code(KC_4);
        break;
      case KC_B:
        register_code(KC_8);
        unregister_code(KC_8);
        break;
      case KC_C:
        register_code(KC_3);
        unregister_code(KC_3);
        break;
      case KC_E:
        register_code(KC_3);
        unregister_code(KC_3);
        break;
      case KC_G:
        register_code(KC_6);
        unregister_code(KC_6);
        break;
      case KC_I:
        register_code(KC_1);
        unregister_code(KC_1);
        break;
      case KC_L:
        register_code(KC_1);
        unregister_code(KC_1);
        break;
      case KC_O:
        register_code(KC_0);
        unregister_code(KC_0);
        break;
      case KC_S:
        register_code(KC_5);
        unregister_code(KC_5);
        break;
      case KC_T:
        register_code(KC_7);
        unregister_code(KC_7);
        break;
      case KC_Z:
        register_code(KC_2);
        unregister_code(KC_2);
        break;
      default:
        register_code(keycode);
        unregister_code(keycode);
        break;
    }
    return false;
  }


  return true;
}

// The Mac/Win switch is never used. Keychron's code sets the default layer from
// it (layer 0 or 2), so pin it to BASE whatever the switch says.
layer_state_t default_layer_state_set_user(layer_state_t state) {
  return 1UL << BASE;
}
