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
#ifdef KC_BLUETOOTH_ENABLE
#    include "transport.h"
#endif

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
     MJ_DRAG,                                 // toggle holding the left button
     MJ_MSET,                                 // the next mark key saves the position
     MJ_MK1, MJ_MK2, MJ_MK3, MJ_MK4, MJ_MK5,  // go to a saved position
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
     _______,         MJ_SZ1,   MJ_SZ2,  MJ_SZ3,    MJ_SZ4,   MJ_SZ5,   MJ_MK1,   MJ_MK2,   MJ_MK3,   MJ_MK4,   MJ_MK5,  _______,  _______,  _______,  _______,   _______,  _______,
     _______,        MS_BTN1,  MS_BTN3, MS_BTN2,   MJ_DRAG,  MS_WHLU,  _______,    MJ_TL,    MJ_UP,    MJ_TR,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
     _______,        MJ_SMLR,   MJ_REP, MJ_LRGR,   MJ_EDGE,  MS_WHLD,  _______,  MJ_LEFT,  MJ_DOWN,  MJ_RGHT,  _______,  _______,            _______,
     _______,        MJ_UNDO,  _______, _______,   MS_WHLL,  MS_WHLR,  MJ_MSET,    MJ_BL,  _______,    MJ_BR,  _______,                      _______,             _______,
     _______,        _______,  _______,                                MS_BTN1,                                _______,  _______,  _______,  _______,  _______,   _______,  _______),
};
// clang-format on

// Mouse mode. A jump is sent as a run of small, evenly spaced reports, so the
// OS pointer acceleration treats a given size the same way every time.
#define MJ_STEP 64         // largest move per report for normal jumps
#define MJ_EDGE_STEP 127   // largest move per report for edge and corner jumps
#define MJ_EDGE_DIST 12000 // far enough to reach the edge of any screen, even at low pointer speeds
#define MJ_INTERVAL_USB_MS 2  // time between reports over USB
#define MJ_INTERVAL_BT_MS 8   // and over Bluetooth, which can't keep up with USB
#define MJ_HOLD_DELAY_MS 250   // hold a direction this long before it starts repeating
#define MJ_HOLD_REPEAT_MS 50   // then jump again this often (or as soon as the last jump is sent)
#define MJ_COMBO_MS 50     // a second direction pressed this soon after the first turns that jump diagonal
#define MJ_HISTORY 16
#define MJ_QUEUE 4
#define MJ_MARKS 5
#define MJ_FLASH_MS 300    // how long a key flashes red when it can't do anything

static const uint16_t mj_sizes[] = {10, 50, 150, 450, 1350};
static uint16_t mj_size = 50;
static int8_t mj_dir_x, mj_dir_y;  // direction of the last normal jump
static bool mj_edge_next = false;
static bool mj_mark_next = false;  // the next 6-0 saves the position instead of going to it
static bool mj_drag = false;

// Normal jumps since the last edge or corner jump, for undo.
static int16_t mj_history[MJ_HISTORY][2];
static uint8_t mj_history_len = 0;

// Moves waiting to be sent. Edge and normal moves use different report sizes,
// and going to a mark is one of each, so they wait in line.
typedef struct {
  int32_t x, y;
  uint8_t step;
} mj_move_t;
static mj_move_t mj_moves[MJ_QUEUE];
static uint8_t mj_moves_len;
static uint16_t mj_timer;

// Where the cursor is, as an offset from the screen edges it was last sent to
// (edge -1 = left/top, 1 = right/bottom, 0 = not sent to one yet). The keyboard
// can't see a real mouse, so using one makes this wrong until the next corner.
typedef struct {
  int8_t edge_x, edge_y;
  int32_t x, y;
} mj_pos_t;
static mj_pos_t mj_pos;
static mj_pos_t mj_marks[MJ_MARKS];  // edge_x 0 = empty slot

// Held keys that keep jumping until they're released: directions as bits
// (combined into diagonals), and A, S or D, which set the size while held.
#define MJ_BIT(keycode) (1 << ((keycode) - MJ_UP))
static uint8_t mj_held;
static uint16_t mj_held_size_key;
static uint16_t mj_hold_timer;
static uint16_t mj_hold_wait;

// The last direction pressed, while it can still be turned diagonal.
static uint16_t mj_combo_key;
static uint16_t mj_combo_timer;

static uint16_t mj_flash_key;
static uint16_t mj_flash_timer;

// Only the timing changes with the connection. The reports stay the same size,
// so a jump lands the same distance over USB and Bluetooth.
static uint16_t mj_interval(void) {
#ifdef KC_BLUETOOTH_ENABLE
  if (get_transport() & TRANSPORT_WIRELESS) return MJ_INTERVAL_BT_MS;
#endif
  return MJ_INTERVAL_USB_MS;
}

static void mj_queue(int32_t dx, int32_t dy, uint8_t step) {
  if (!mj_moves_len) mj_timer = timer_read() - mj_interval();  // send the first report right away
  if (!mj_moves_len || (mj_moves[mj_moves_len - 1].step != step && mj_moves_len < MJ_QUEUE)) {
    mj_moves[mj_moves_len++] = (mj_move_t){0, 0, step};
  }
  mj_moves[mj_moves_len - 1].x += dx;
  mj_moves[mj_moves_len - 1].y += dy;
}

static void mj_history_push(int16_t dx, int16_t dy) {
  if (mj_history_len == MJ_HISTORY) {
    memmove(mj_history[0], mj_history[1], sizeof(mj_history[0]) * (MJ_HISTORY - 1));
    mj_history_len--;
  }
  mj_history[mj_history_len][0] = dx;
  mj_history[mj_history_len][1] = dy;
  mj_history_len++;
}

static void mj_move(int16_t dx, int16_t dy) {
  mj_pos.x += dx;
  mj_pos.y += dy;
  mj_queue(dx, dy, MJ_STEP);
}

static void mj_jump(int8_t dir_x, int8_t dir_y, uint16_t size) {
  int16_t dx = dir_x * size, dy = dir_y * size;
  mj_history_push(dx, dy);
  mj_dir_x = dir_x;
  mj_dir_y = dir_y;
  mj_combo_key = 0;
  mj_move(dx, dy);
}

// The screen edge stops the cursor, so these land in the same place every time.
// The keyboard can't tell how far the cursor really moved, so undo starts over.
static void mj_to_edge(int8_t dir_x, int8_t dir_y) {
  mj_history_len = 0;
  mj_combo_key = 0;
  if (dir_x) {
    mj_pos.edge_x = dir_x;
    mj_pos.x = 0;
  }
  if (dir_y) {
    mj_pos.edge_y = dir_y;
    mj_pos.y = 0;
  }
  mj_queue(dir_x * MJ_EDGE_DIST, dir_y * MJ_EDGE_DIST, MJ_EDGE_STEP);
}

static void mj_flash(uint16_t keycode) {
  mj_flash_key = keycode;
  mj_flash_timer = timer_read();
}

static void mj_mark(uint16_t keycode) {
  mj_pos_t *mark = &mj_marks[keycode - MJ_MK1];
  if (mj_mark_next) {
    mj_mark_next = false;
    if (mj_pos.edge_x && mj_pos.edge_y) {
      *mark = mj_pos;
    } else {
      mj_flash(keycode);  // no corner yet, so there's nothing to measure from
    }
  } else if (mark->edge_x) {
    mj_to_edge(mark->edge_x, mark->edge_y);
    mj_move(mark->x, mark->y);
  } else {
    mj_flash(keycode);
  }
}

// A, S and D jump at half, the same or double the current size without changing it.
static uint16_t mj_size_for(uint16_t keycode) {
  switch (keycode) {
    case MJ_SMLR: return mj_size / 2;
    case MJ_LRGR: return mj_size * 2;
    default:      return mj_size;
  }
}

// Held directions combine, so I + L goes up and right. Opposites cancel out.
static void mj_held_dir(int8_t *x, int8_t *y) {
  *x = !!(mj_held & MJ_BIT(MJ_RGHT)) - !!(mj_held & MJ_BIT(MJ_LEFT));
  *y = !!(mj_held & MJ_BIT(MJ_DOWN)) - !!(mj_held & MJ_BIT(MJ_UP));
}

// Jump the way the held directions point, or the way the last jump went.
static void mj_repeat(void) {
  int8_t x, y;
  mj_held_dir(&x, &y);
  if (!x && !y) {
    x = mj_dir_x;
    y = mj_dir_y;
  }
  if (x || y) mj_jump(x, y, mj_size_for(mj_held_size_key));
}

static void mj_hold_start(void) {
  mj_hold_timer = timer_read();
  mj_hold_wait = MJ_HOLD_DELAY_MS;
}

static void mj_press_direction(uint16_t keycode) {
  static const int8_t dirs[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};  // MJ_UP .. MJ_RGHT
  int8_t x = dirs[keycode - MJ_UP][0], y = dirs[keycode - MJ_UP][1];

  // An edge jump goes once and doesn't repeat.
  if (mj_edge_next) {
    mj_edge_next = false;
    mj_to_edge(x, y);
    return;
  }

  mj_held |= MJ_BIT(keycode);
  mj_hold_start();

  // Two directions pressed together: add this one to the jump that's already
  // going, so the pair makes one diagonal jump instead of two.
  bool vertical = keycode <= MJ_DOWN;
  if (mj_combo_key && (mj_combo_key <= MJ_DOWN) != vertical && timer_elapsed(mj_combo_timer) < MJ_COMBO_MS) {
    int16_t size = mj_size_for(mj_held_size_key);
    mj_history[mj_history_len - 1][0] += x * size;
    mj_history[mj_history_len - 1][1] += y * size;
    if (x) mj_dir_x = x;
    if (y) mj_dir_y = y;
    mj_combo_key = 0;
    mj_move(x * size, y * size);
    return;
  }

  int8_t held_x, held_y;
  mj_held_dir(&held_x, &held_y);
  if (held_x || held_y) {
    x = held_x;
    y = held_y;
  }
  mj_jump(x, y, mj_size_for(mj_held_size_key));
  if (!x || !y) {
    mj_combo_key = keycode;
    mj_combo_timer = timer_read();
  }
}

static void mj_set_drag(bool on) {
  mj_drag = on;
  if (on) {
    mousekey_on(MS_BTN1);
  } else {
    mousekey_off(MS_BTN1);
  }
  mousekey_send();
}

static int8_t mj_take(int32_t *pending, uint8_t step) {
  int32_t d = *pending;
  if (d > step) d = step;
  if (d < -step) d = -step;
  *pending -= d;
  return d;
}

static void mj_hold_task(void) {
  if ((!mj_held && !mj_held_size_key) || mj_moves_len || timer_elapsed(mj_hold_timer) < mj_hold_wait) return;
  mj_hold_timer = timer_read();
  mj_hold_wait = MJ_HOLD_REPEAT_MS;
  mj_repeat();
}

void housekeeping_task_user(void) {
  // Clear these before the 16-bit timers wrap and make them look new again.
  if (mj_combo_key && timer_elapsed(mj_combo_timer) >= MJ_COMBO_MS) mj_combo_key = 0;
  if (mj_flash_key && timer_elapsed(mj_flash_timer) >= MJ_FLASH_MS) mj_flash_key = 0;
  mj_hold_task();
  if (!mj_moves_len || timer_elapsed(mj_timer) < mj_interval()) return;
  mj_timer = timer_read();
  mj_move_t *move = &mj_moves[0];
  report_mouse_t report = mousekey_get_report();  // keeps held buttons, e.g. a drag
  report.x = mj_take(&move->x, move->step);
  report.y = mj_take(&move->y, move->step);
  report.v = 0;
  report.h = 0;
  host_mouse_send(&report);
  if (!move->x && !move->y) {
    mj_moves_len--;
    memmove(&mj_moves[0], &mj_moves[1], sizeof(mj_moves[0]) * mj_moves_len);
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  if (!layer_state_cmp(state, MOUSE)) {
    mj_edge_next = false;
    mj_mark_next = false;
    mj_held = 0;
    mj_held_size_key = 0;
    if (mj_drag) mj_set_drag(false);
  }
  return state;
}

static bool process_mouse_jump(uint16_t keycode, keyrecord_t *record) {
  // Clicking ends a drag lock, since the click releases the button anyway.
  if (keycode == MS_BTN1 && record->event.pressed) mj_drag = false;

  if (keycode < MJ_UP || keycode > MJ_MK5) return true;
  if (!record->event.pressed) {
    if (keycode >= MJ_UP && keycode <= MJ_RGHT) mj_held &= ~MJ_BIT(keycode);
    if (keycode == mj_held_size_key) mj_held_size_key = 0;
    return false;
  }

  switch (keycode) {
    case MJ_UP:
    case MJ_DOWN:
    case MJ_LEFT:
    case MJ_RGHT:
      mj_press_direction(keycode);
      break;
    case MJ_TL:   mj_to_edge(-1, -1); break;
    case MJ_TR:   mj_to_edge(1, -1); break;
    case MJ_BL:   mj_to_edge(-1, 1); break;
    case MJ_BR:   mj_to_edge(1, 1); break;
    case MJ_EDGE: mj_edge_next = !mj_edge_next; break;
    case MJ_SMLR:
    case MJ_REP:
    case MJ_LRGR:
      mj_held_size_key = keycode;
      mj_hold_start();
      mj_repeat();
      break;
    case MJ_UNDO:
      if (mj_history_len) {
        mj_history_len--;
        mj_combo_key = 0;
        mj_move(-mj_history[mj_history_len][0], -mj_history[mj_history_len][1]);
      }
      break;
    case MJ_DRAG: mj_set_drag(!mj_drag); break;
    case MJ_MSET: mj_mark_next = !mj_mark_next; break;
    case MJ_MK1 ... MJ_MK5:
      mj_mark(keycode);
      break;
    default:  // MJ_SZ1 .. MJ_SZ5
      mj_size = mj_sizes[keycode - MJ_SZ1];
      break;
  }
  return false;
}

// Off any layer but BASE, light only the keys that do something there, coloured
// by what they do. A bright key is active, switched on, or the current setting.
static rgb_t key_color(uint8_t hue, uint8_t sat, bool bright) {
  uint8_t val = rgb_matrix_get_val();
  return hsv_to_rgb((hsv_t){hue, sat, bright ? val : val / 5});
}

static rgb_t mj_key_color(uint16_t keycode) {
  if (keycode == mj_flash_key) return key_color(0, 255, true);
  switch (keycode) {
    case MJ_UP ... MJ_RGHT: return key_color(0, 0, true);                    // white
    case MJ_TL ... MJ_BR:   return key_color(128, 255, true);                // cyan
    case MJ_SZ1 ... MJ_SZ5: return key_color(170, 255, mj_sizes[keycode - MJ_SZ1] == mj_size);  // blue
    case MJ_SMLR ... MJ_LRGR: return key_color(191, 255, true);              // purple
    case MJ_EDGE:           return key_color(21, 255, mj_edge_next);         // orange
    case MS_BTN1 ... MS_BTN3: return key_color(85, 255, true);               // green
    case MJ_DRAG:           return key_color(0, 255, mj_drag);               // red
    case MS_WHLU ... MS_WHLR: return key_color(110, 255, false);             // teal
    case MJ_UNDO:           return key_color(43, 255, true);                 // yellow
    case MJ_MSET:           return key_color(213, 255, mj_mark_next);        // magenta
    case MJ_MK1 ... MJ_MK5: return key_color(213, 255, mj_marks[keycode - MJ_MK1].edge_x);
    default:                return (rgb_t){0, 0, 0};
  }
}

static rgb_t layer_key_color(uint16_t keycode, bool bright) {
  switch (keycode) {
    case KC_RGHT ... KC_UP:
    case KC_HOME:
    case KC_END:
    case KC_PGUP:
    case KC_PGDN:           return key_color(0, 0, bright);                   // white: navigation
    case KC_ENT:
    case KC_ESC:
    case KC_BSPC:
    case KC_DEL:
    case KC_INS:
    case KC_APP:            return key_color(43, 255, bright);                // yellow: editing
    case KC_1 ... KC_0:     return key_color(150, 255, bright);               // azure: numbers
    case KC_F1 ... KC_F12:
    case KC_F13 ... KC_F24: return key_color(170, 255, bright);               // blue: function keys
    case QK_DYNAMIC_MACRO_RECORD_START_1 ... QK_DYNAMIC_MACRO_PLAY_2:
                            return key_color(213, 255, bright);               // magenta: macros
    case QK_REP:            return key_color(191, 255, bright);               // purple: repeat
    case MOD_SPC:           return key_color(21, 255, bright);                // orange: launcher
    case MS_BTN1 ... MS_BTN3: return key_color(85, 255, bright);              // green: clicks
    case MS_WHLU ... MS_WHLR: return key_color(110, 255, false);              // teal: scroll
    case KC_MUTE ... KC_VOLD:
    case KC_MNXT ... KC_MPLY: return key_color(21, 255, bright);              // orange: media
    case BT_HST1 ... BT_HST3:
    case BAT_LVL:
    case NK_TOGG:           return key_color(64, 255, bright);                // lime: connection
    case QK_UNDERGLOW_TOGGLE ... QK_UNDERGLOW_SPEED_DOWN:
                            return key_color(rgb_matrix_get_hue(), rgb_matrix_get_sat(), true);  // the current colour
    case RND_CASE:          return key_color(0, 255, random_case_enabled);    // red, bright when on
    case L33T_SPK:          return key_color(0, 255, leet_speak_enabled);
    default:                return key_color(0, 0, false);                    // dim white: anything else
  }
}

// What a key does on the active layers, looking down through transparent keys.
// Keys from a lower layer (CAPS under CAPS_SPACE) are dim. Plain BASE keys are
// off, except the keys holding layers on (cyan).
static rgb_t layer_color_at(uint8_t layer, keypos_t pos) {
  for (int8_t l = layer; l >= BASE; l--) {
    if (l != BASE && !layer_state_is(l)) continue;
    uint16_t keycode = keymap_key_to_keycode(l, pos);
    if (keycode == KC_TRNS) continue;
    if (IS_QK_MOMENTARY(keycode)) return key_color(128, 255, true);
    if (l == BASE || keycode == KC_NO) break;
    return layer_key_color(keycode, l == layer);
  }
  return (rgb_t){0, 0, 0};
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  uint8_t layer = get_highest_layer(layer_state);
  if (layer == BASE) return true;
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
      uint8_t led = g_led_config.matrix_co[row][col];
      if (led == NO_LED || led < led_min || led >= led_max) continue;
      keypos_t pos = {.row = row, .col = col};
      // Mouse mode shows only its own keys, so the jump keys stand out.
      rgb_t color = layer == MOUSE ? mj_key_color(keymap_key_to_keycode(MOUSE, pos)) : layer_color_at(layer, pos);
      rgb_matrix_set_color(led, color.r, color.g, color.b);
    }
  }
  return true;
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
