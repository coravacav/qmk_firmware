#include QMK_KEYBOARD_H

#define _Default 0
#define _Function 1
#define _Caps 2
#define _Numpad 3
#define _Space 4

// https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_Default] = LAYOUT(
        KC_ESC,        KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,        KC_F11,  KC_F12,           KC_PSCR, KC_SLCK, KC_PAUS, \
        KC_GRV,        KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,          KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,        KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,          KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, \
        MO(_Caps),     KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,       KC_QUOT,          KC_ENT,                             \
        KC_LSFT,       KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                KC_RSFT,                   KC_UP,            \
        KC_LCTL,       KC_LGUI,  KC_LALT, KC_SPC,                                               KC_RALT, MO(_Function), KC_RGUI,          KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[_Function] = LAYOUT(
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,          KC_MUTE, XXXXXXX, XXXXXXX, \
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, KC_MSTP, KC_VOLU, \
        XXXXXXX,       RGB_SPD,  RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, KC_VOLD, \
        KC_CAPS,       RGB_RMOD, RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,          XXXXXXX,                            \
        XXXXXXX,       RGB_TOG,  XXXXXXX, XXXXXXX, DEBUG,   RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX,          XXXXXXX,          \
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX,                                              XXXXXXX, XXXXXXX,       KC_BTN1,          KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX
    ),
	[_Caps] = LAYOUT(
        XXXXXXX,       KC_F13,   KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,        KC_F23,  KC_F24,           XXXXXXX, XXXXXXX, DM_RSTP, \
        MO(_Numpad),   KC_BSPC,  KC_DEL,  KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX,       KC_BTN1,  XXXXXXX, KC_BTN2, KC_PGUP, XXXXXXX, XXXXXXX, KC_BSPC, KC_UP,   KC_DEL,  XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX,       KC_HOME,  KC_END,  XXXXXXX, KC_PGDN, XXXXXXX, KC_ESC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT,        XXXXXXX,          XXXXXXX,                            \
        KC_LSFT,       XXXXXXX,  KC_MINS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_LCBR, KC_RCBR, XXXXXXX,                         XXXXXXX,          _______,          \
        _______,       _______,  _______, MO(_Space),                                           DM_REC1, DM_REC2,       DM_PLY1,          DM_PLY2, _______, _______, _______
    ),
	[_Numpad] = LAYOUT(
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,          XXXXXXX,                            \
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX,          XXXXXXX,          \
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX,                                              XXXXXXX, XXXXXXX,       XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
	[_Space] = LAYOUT(
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX,       KC_BSPC,  KC_UP,   KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  XXXXXXX, XXXXXXX, \
        XXXXXXX,       KC_LEFT,  KC_DOWN, KC_RGHT, KC_ENT,  XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_0,          XXXXXXX,          XXXXXXX,                            \
        XXXXXXX,       KC_DOT,   KC_COMM, KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX,                         XXXXXXX,          XXXXXXX,          \
        XXXXXXX,       XXXXXXX,  XXXXXXX, XXXXXXX,                                              XXXXXXX, XXXXXXX,       XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};
