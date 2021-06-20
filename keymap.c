#include QMK_KEYBOARD_H
#include "version.h"
#include "bootmagic.h"

#define QWERTY 0    // qwerty layer
#define FN 1        // function layer

enum custom_keycodes {
    QWRTY = SAFE_RANGE, // can always be here
    FNX,
    VRSN
};

/* false: Caps Lock LED is off
   true: Caps Lock LED is on */
bool CAPS_LED = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Qwerty layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | Copy |           | Paste|   6  |   7  |   8  |   9  |   0  | BckSpc |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  | Vol  |           |  {   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------| Up   |           |  [   |------+------+------+------+------+--------|
 * |  Caps  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------| Vol  |           |  }   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | Down |           |  ]   |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl | LGui | LAlt | Left | Right|                                       | Down |  Up  |   -  |   =  | RCtrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | ESC  | Ins  |       | PScr |  Fn1 |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space| Mute |------|       |------|  Del   |Enter |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[QWERTY] = LAYOUT_ergodox(  // layer 0 : qwerty
        // left hand
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,  KC_COPY,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,  KC_VOLU,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,  KC_VOLD,
        KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LEFT,  KC_RGHT,
                                                       KC_ESC,   KC_INS,
                                                                 KC_HOME,
                                              KC_SPC,  KC_MUTE,  KC_END,
        // right hand
             KC_PASTE,  KC_6,  KC_7,     KC_8,     KC_9,     KC_0,      KC_BSPC,
             KC_LBRC,   KC_Y,  KC_U,     KC_I,     KC_O,     KC_P,      KC_BSLS,
                        KC_H,  KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOTE,
             KC_RBRC,   KC_N,  KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,   KC_RSFT,
                               KC_DOWN,  KC_UP,    KC_MINS,  KC_EQL,    KC_RCTL,
             KC_PSCR,   FNX,
             KC_PGUP,
             KC_PGDN,   KC_DEL,  KC_ENT
),
/* Keymap 2: Function Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Esc      |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 | BckSpc |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | Tab     |      |      | Prev | Play | Next | Xcpy |           | Play |      |  7   |   8  |   9  |NumLck|Version |
 * |---------+------+------+------+------+------|      |           | Mcr1 |------+------+------+------+------+--------|
 * | CAPS    |      |  Up  |      |VolDn | VolUp|------|           |------|      |  4   |   5  |   6  |      | Enter  |
 * |---------+------+------+------+------+------| Xpst |           | Play |------+------+------+------+------+--------|
 * |  Shift  | Left | Down | Rght |      |      |      |           | Mcr2 |      |  1   |   2  |   3  |      | Shift  |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  CTRL | Win  | Alt  |      |      |                                       |  0   |   .  |Enter | Alt  | Ctrl |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      | Fn1  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Rec  | Rec  |      |       |      | Stp  |      |
 *                                 | Mcr  | Mcr  |------|       |------| Rec  |      |
 *                                 |  1   |  2   |      |       |      | Mcr  |      |
 *                                 `--------------------'       `--------------------'
 */
// Functions
[FN] = LAYOUT_ergodox(
       // left hand
       KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,
       KC_TAB,   KC_TRNS,  KC_TRNS,  KC_MPRV,  KC_MPLY,  KC_MNXT,  C(S(KC_C)),
       KC_CAPS,  KC_TRNS,  KC_UP,    KC_TRNS,  KC_VOLD,  KC_VOLU,
       KC_LSFT,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS,  KC_TRNS,  C(S(KC_V)),
       KC_LCTL,  KC_LGUI,  KC_LALT,  KC_TRNS,  KC_TRNS,
                                                         KC_TRNS,  KC_TRNS,
                                                                   KC_TRNS,
                                               DM_REC1,  DM_REC2,  KC_TRNS,
       // right hand
       KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_BSPC,
       DM_PLY1,  KC_TRNS,  KC_P7,    KC_P8,    KC_P9,    KC_NLCK,  VRSN,
                 KC_TRNS,  KC_P4,    KC_P5,    KC_P6,    KC_TRNS,  KC_ENT,
       DM_PLY2,  KC_TRNS,  KC_P1,    KC_P2,    KC_P3,    KC_TRNS,  KC_RSFT,
                           KC_P0,    KC_PDOT,  KC_PENT,  KC_TRNS,  KC_RCTL,
       KC_TRNS,  QWRTY,
       KC_TRNS,
       KC_TRNS,  DM_RSTP,  KC_TRNS
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case VRSN:
        if (record->event.pressed) {
          SEND_STRING ("");
        }
        return false;
        break;
      case QWRTY:
        if (record->event.pressed) {
          set_single_persistent_default_layer(QWERTY);
        }
        return false;
        break;
      case FNX:
        if (record->event.pressed) {
          set_single_persistent_default_layer(FN);
        }
        return false;
        break;
      case KC_CAPS:
        if (record->event.pressed) {
          // Turn LED1 On/Off for Caps Lock
          if (CAPS_LED) {
            ergodox_right_led_1_off();
            CAPS_LED = false;
          } else {
            ergodox_right_led_1_on();
            CAPS_LED = true;
          }
        }
        return true;
        break;
    }
    return true;
};

// Set LED according to the default layer
void default_layer_led_set(void) {
    switch (biton32(eeconfig_read_default_layer())) {
      case QWERTY:
        // LED3 for QWERTY
        ergodox_right_led_3_on();
        break;
    };
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    default_layer_led_set();
};

uint32_t layer_state_set_user(uint32_t state) {
    ergodox_led_all_off();
    switch (biton32(state)) {
      case FN:
          // Red led on Pro Micro for Fn layer
          ergodox_board_led_on();
          break;
    };

    if (CAPS_LED) {
      ergodox_right_led_1_on();
    }

    default_layer_led_set();

    return state;
};

void suspend_power_down_user(void) {
    ergodox_led_all_off();
};

void suspend_wakeup_init_user(void) {
    default_layer_led_set();
};
