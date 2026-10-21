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
  MOUSE,
};

enum custom_keycodes {
     MOD_SPC = SAFE_RANGE,
     RND_CASE,
     L33T_SPK,
     // Mouse mode (Caps + '): jump the cursor instead of gliding it.
     MJ_UP, MJ_DOWN, MJ_LEFT, MJ_RGHT,        // jump by the current size
     MJ_TL, MJ_TR, MJ_BL, MJ_BR,              // snap to a screen corner
     MJ_EDGE,                                 // next jump goes to the screen edge
     MJ_SMLR, MJ_REP, MJ_LRGR,                // repeat last jump at half / same / double size
     MJ_UNDO,                                 // undo the last jump
     MJ_SZ1, MJ_SZ2, MJ_SZ3, MJ_SZ4, MJ_SZ5,  // set the jump size
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
     _______,        KC_HOME,   KC_END, MOD_SPC,   KC_PGDN,  MS_WHLD,   KC_ESC,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_ENT,  MO(MOUSE),          _______,
     _______,        DM_PLY1,  DM_PLY2,  KC_APP,   QK_REP,   QK_REP,   QK_REP,   QK_REP,   _______,  _______,  _______,                      _______,             _______,
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

[MOUSE] = LAYOUT_tkl_ansi(
     _______,        _______,  _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   _______,  _______,
     _______,         MJ_SZ1,   MJ_SZ2,  MJ_SZ3,    MJ_SZ4,   MJ_SZ5,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
     _______,        MS_BTN1,  MS_BTN3, MS_BTN2,   _______,  MS_WHLU,  _______,    MJ_TL,    MJ_UP,    MJ_TR,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
     _______,        MJ_SMLR,   MJ_REP, MJ_LRGR,   MJ_EDGE,  MS_WHLD,  _______,  MJ_LEFT,  MJ_DOWN,  MJ_RGHT,  _______,  _______,            _______,
     _______,        MJ_UNDO,  _______, _______,   _______,  _______,  _______,    MJ_BL,  _______,    MJ_BR,  _______,                      _______,             _______,
     _______,        _______,  _______,                                MS_BTN1,                                _______,  _______,  _______,  _______,  _______,   _______,  _______),
};
// clang-format on

// Mouse mode. A jump is sent as a run of small, evenly spaced reports, so the
// OS pointer acceleration treats a given size the same way every time.
#define MJ_STEP 16         // largest move per report for normal jumps
#define MJ_EDGE_STEP 127   // largest move per report for edge and corner jumps
#define MJ_EDGE_DIST 3000  // far enough to reach the edge of any screen
#define MJ_INTERVAL_MS 8   // time between reports
#define MJ_SIZE_MAX 2000
#define MJ_HISTORY 16

static const uint16_t mj_sizes[] = {10, 25, 50, 100, 250};
static uint16_t mj_size = 50;
static int8_t mj_dir_x, mj_dir_y;  // direction of the last normal jump
static bool mj_edge_next = false;

// Normal jumps since the last edge or corner jump, for undo.
static int16_t mj_history[MJ_HISTORY][2];
static uint8_t mj_history_len = 0;

static int32_t mj_pending_x, mj_pending_y;
static uint8_t mj_step;
static uint16_t mj_timer;

static void mj_queue(int32_t dx, int32_t dy, uint8_t step) {
  if (!mj_pending_x && !mj_pending_y) {
    mj_step = step;
    mj_timer = timer_read() - MJ_INTERVAL_MS;  // send the first report right away
  }
  mj_pending_x += dx;
  mj_pending_y += dy;
}

static void mj_jump(int8_t dir_x, int8_t dir_y) {
  int16_t dx = dir_x * mj_size, dy = dir_y * mj_size;
  if (mj_history_len == MJ_HISTORY) {
    memmove(mj_history[0], mj_history[1], sizeof(mj_history[0]) * (MJ_HISTORY - 1));
    mj_history_len--;
  }
  mj_history[mj_history_len][0] = dx;
  mj_history[mj_history_len][1] = dy;
  mj_history_len++;
  mj_dir_x = dir_x;
  mj_dir_y = dir_y;
  mj_queue(dx, dy, MJ_STEP);
}

// The screen edge stops the cursor, so these land in the same place every time.
// The keyboard can't tell how far the cursor really moved, so undo starts over.
static void mj_to_edge(int8_t dir_x, int8_t dir_y) {
  mj_history_len = 0;
  mj_queue(dir_x * MJ_EDGE_DIST, dir_y * MJ_EDGE_DIST, MJ_EDGE_STEP);
}

static void mj_direction(int8_t dir_x, int8_t dir_y) {
  if (mj_edge_next) {
    mj_edge_next = false;
    mj_to_edge(dir_x, dir_y);
  } else {
    mj_jump(dir_x, dir_y);
  }
}

static void mj_repeat(void) {
  if (mj_dir_x || mj_dir_y) mj_jump(mj_dir_x, mj_dir_y);
}

static int8_t mj_take(int32_t *pending) {
  int32_t d = *pending;
  if (d > mj_step) d = mj_step;
  if (d < -mj_step) d = -mj_step;
  *pending -= d;
  return d;
}

void housekeeping_task_user(void) {
  if ((!mj_pending_x && !mj_pending_y) || timer_elapsed(mj_timer) < MJ_INTERVAL_MS) return;
  mj_timer = timer_read();
  report_mouse_t report = mousekey_get_report();  // keeps held buttons, e.g. a drag
  report.x = mj_take(&mj_pending_x);
  report.y = mj_take(&mj_pending_y);
  report.v = 0;
  report.h = 0;
  host_mouse_send(&report);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  if (!layer_state_cmp(state, MOUSE)) mj_edge_next = false;
  return state;
}

static bool process_mouse_jump(uint16_t keycode, keyrecord_t *record) {
  if (keycode < MJ_UP || keycode > MJ_SZ5) return true;
  if (!record->event.pressed) return false;

  switch (keycode) {
    case MJ_UP:   mj_direction(0, -1); break;
    case MJ_DOWN: mj_direction(0, 1); break;
    case MJ_LEFT: mj_direction(-1, 0); break;
    case MJ_RGHT: mj_direction(1, 0); break;
    case MJ_TL:   mj_to_edge(-1, -1); break;
    case MJ_TR:   mj_to_edge(1, -1); break;
    case MJ_BL:   mj_to_edge(-1, 1); break;
    case MJ_BR:   mj_to_edge(1, 1); break;
    case MJ_EDGE: mj_edge_next = !mj_edge_next; break;
    case MJ_SMLR:
      if (mj_size > 1) mj_size /= 2;
      mj_repeat();
      break;
    case MJ_REP: mj_repeat(); break;
    case MJ_LRGR:
      if (mj_size * 2 <= MJ_SIZE_MAX) mj_size *= 2;
      mj_repeat();
      break;
    case MJ_UNDO:
      if (mj_history_len) {
        mj_history_len--;
        mj_queue(-mj_history[mj_history_len][0], -mj_history[mj_history_len][1], MJ_STEP);
      }
      break;
    default:  // MJ_SZ1 .. MJ_SZ5
      mj_size = mj_sizes[keycode - MJ_SZ1];
      break;
  }
  return false;
}

bool is_alpha(uint16_t keycode) {
  return keycode >= KC_A && keycode <= KC_Z;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_mouse_jump(keycode, record)) return false;

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
