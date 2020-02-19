#include "lets_split.h"
#include "flip_keymap.h"
#include "action_layer.h"
#include "eeconfig.h"
#include <stdlib.h>

extern keymap_config_t keymap_config;

extern rgblight_config_t rgblight_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _NUMPAD 5
#define _ADJUST 16

int randomInt(int max) {
  return rand() % max; // returns a pseudo-random integer between 0 and RAND_MAX
}

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  NUMPAD,
  ADJUST,
  ORANGE,
  RED,
  BLUE,
  GREY,
  GREEN,
  GOLD, 
  SOLID,
  DYNAMIC_MACRO_RANGE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// this is called when dynamic macro buffer is full
void backlight_toggle(void) {
  // INSERT CODE HERE: for example, call function to turn on indicator LED.

  rgblight_mode(5);
  rgblight_sethsv(350, rgblight_config.sat, rgblight_config.val);
}

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty But each side is swapped (hardware issue)
 * ,-----------------------------------------------------------------------------------.
 * | tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Adjust|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Ctrl  | GUI  |Alt   |Raise |Lower |Space |Space |esc   |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,  \
  ADJUST,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,  \
  KC_LCTL, KC_LGUI, KC_LALT, RAISE,   LOWER,   KC_SPC,  KC_SPC,  KC_ESC,  _______, _______, _______, DYN_REC_STOP  \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Adjust|   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Ctrl  | GUI  |Alt   |Raise |Lower |Space |Space |esc   | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,     \
  ADJUST,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,    \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,   \
  KC_LCTL, KC_LGUI, KC_LALT, RAISE,   LOWER,   KC_SPC,  KC_SPC,  KC_ESC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Adjust|   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Ctrl  | GUI  |Alt   |Raise |Lower |Space |Space |esc   | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = KEYMAP( \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,   \
  ADJUST,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,   \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,    \
  KC_LCTL, KC_LGUI, KC_LALT, RAISE,   LOWER,   KC_SPC,  KC_SPC,  KC_ESC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  `   |      |      |      |      |      |      |   -  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   _  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,         KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,  \
  KC_GRV,  _______, _______, _______, _______, _______, DYN_REC_START1,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,    \
  _______, _______, _______, _______, _______, _______, DYN_MACRO_PLAY1, KC_UNDS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,   \
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | esc  |  F9  |  F10 |  F11 |  F12 |      |      |   7  |   8  |   9  |   +  |   -  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  | F7   | F8   |      |      |   2  |  5   |   8  |   /  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  | F4   |      |      |  1   |   2  |   3  |   *  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             | 0    |  0   |   .  |Enter |Qwerty|
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_ESC ,   KC_F9,   KC_F10,   KC_F11,  KC_F12, _______, _______,  KC_7,    KC_8,    KC_9, KC_PLUS, KC_MINS,         \
  _______,   KC_F5,    KC_F6,    KC_F7,   KC_F8, _______, _______,  KC_4,    KC_5,    KC_6, KC_SLSH, _______,    \
  _______,   KC_F1,    KC_F2,    KC_F3,   KC_F4, _______, _______,  KC_1,    KC_2,    KC_3, KC_ASTR, _______,    \
  _______, _______,  _______,  _______, _______, _______, _______,  KC_0,    KC_0,  KC_DOT,  KC_ENT, _______   \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |  up  |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |AGnorm|AGswap|      |      |left  |down  |right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |RGBTOG|RGBMOD|RGBHUD|RGBHUI|RGBSAD|      |RGBSAI|RGBVAD|RGBVAI|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |Qwerty|Colemk|Dvorak|      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  _______,   RESET,   _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, KC_DEL, \
  _______, _______,   _______, AG_NORM, AG_SWAP, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
  _______, RGB_TOG,   RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, _______, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
  GOLD,      GREEN,   GREY,    BLUE,    RED,     ORANGE,  SOLID,   _______, QWERTY,  COLEMAK, DVORAK,  _______ \
)


};

bool TOG_STATUS = false;
int RGB_current_mode;
int RGB_current_hue;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    rgblight_mode(RGB_current_mode);
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
        rgblight_mode(RGB_current_mode);
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
        rgblight_mode(RGB_current_mode);
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
        rgblight_mode(RGB_current_mode);
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(16);
          rgblight_sethsv(220, rgblight_config.sat, rgblight_config.val);
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(15);
          rgblight_sethsv(359, rgblight_config.sat, rgblight_config.val);
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
        TOG_STATUS = false;
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case KC_LSFT:
      if (record->event.pressed) {
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(5);
          rgblight_sethsv(29, rgblight_config.sat, rgblight_config.val);
        }
      } else {
        rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        TOG_STATUS = false;
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
      }
      break;
    case KC_LALT:
      if (record->event.pressed) {
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(1);
          rgblight_sethsv(55, rgblight_config.sat, rgblight_config.val);
        }
      } else {
        rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        TOG_STATUS = false;
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
      }
      break;
    case KC_LGUI:
      if (record->event.pressed) {
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(1);
          rgblight_sethsv(280, rgblight_config.sat, rgblight_config.val);
        }
      } else {
        rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        TOG_STATUS = false;
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
      }
      break;
    case KC_LCTL:
      if (record->event.pressed) {
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(1);
          rgblight_sethsv(100, rgblight_config.sat, rgblight_config.val);
        }
      } else {
        rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        TOG_STATUS = false;
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
      }
      break;
    case KC_BSPC:
    case KC_LEFT:
    case KC_RGHT:
    case KC_UP:
    case KC_DOWN:
    case KC_DEL:
    case KC_TAB:
    case KC_ENT:
    case KC_SPC:
      if (record->event.pressed) {
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          rgblight_mode(1);
          rgblight_sethsv(randomInt(359), rgblight_config.sat, rgblight_config.val);
        }
      } else {
        rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        TOG_STATUS = false;
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
      }
      break;
   case KC_A:
  case KC_B:
  case KC_C:
  case KC_D:
  case KC_E:
  case KC_F:
  case KC_G:
  case KC_H:
  case KC_I:
  case KC_K:
  case KC_L:
  case KC_M:
  case KC_N:
  case KC_O:
  case KC_P:
  case KC_Q:
  case KC_R:
  case KC_S:
  case KC_T:
  case KC_U:
  case KC_V:
  case KC_W:
  case KC_X:
  case KC_Y:
  case KC_Z:
      break;
    case RGB_MOD:
      if (record->event.pressed) {
        rgblight_mode(RGB_current_mode);
        rgblight_step();
        RGB_current_mode = rgblight_config.mode;
        if(RGB_current_mode == 1){
          rgblight_mode(RGB_current_mode);
        }
      }
      return false;
      break;
    case RGB_HUD:
      RGB_current_hue = rgblight_config.hue;
      break;
    case RGB_HUI:
      RGB_current_hue = rgblight_config.hue;
      break;
    case RED:
      rgblight_mode(5);
      RGB_current_mode = rgblight_config.mode;
      return false;
      break;
    case BLUE:
      rgblight_mode(8);
      RGB_current_mode = rgblight_config.mode;
      return false;
      break;
    case GREEN:
      rgblight_mode(14);
      RGB_current_mode = rgblight_config.mode;
      return false;
      break;
    case GREY:
      rgblight_mode(16);
      RGB_current_mode = rgblight_config.mode;
      return false;
      break;
    case ORANGE:
      rgblight_mode(15);
      RGB_current_mode = rgblight_config.mode;
      return false;
      break;
    case GOLD:
      rgblight_mode(21);
      RGB_current_mode = rgblight_config.mode;
      return false;
      break;
    case SOLID:
      rgblight_mode(1);
      RGB_current_mode = rgblight_config.mode;
      return false;
      break;
  }
  return true;
}