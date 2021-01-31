/* Copyright 2020 wcaokaze
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

enum layer_names {
  _DVORAK = 0,
  _NORMAL_SPC,
  _NUM,
  _SYMBOL,
  _FN
};

enum encoder_number {
  _1ST = 0,
  _2ND,
};

enum custom_keycodes {
   S_ARW = SAFE_RANGE,
   D_ARW
};

#define TG_SPC TG(_NORMAL_SPC)
#define SYM_SPC LT(_SYMBOL, KC_SPC)
#define BS_SFT SFT_T(KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT(
      KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_LSFT,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_SLSH, KC_BSLS,
      KC_TAB , KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   , KC_LSFT,     KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_MINS, KC_EQL ,
      KC_LCTL, KC_A   , KC_O   , KC_E   , KC_U   , KC_I   , KC_KANA,     KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_LBRC, KC_RBRC,
      KC_LSFT, KC_Z   , KC_Q   , KC_J   , KC_K   , KC_X   ,              KC_B   , KC_M   , KC_W   , KC_V   , KC_SCLN, S_ARW  , TG(_NUM),
      MO(_FN)      , KC_LALT   , KC_SPC     , SYM_SPC     , KC_ESC ,     BS_SFT , KC_ENT     , MO(_FN)     , KC_RGUI
  ),

  [_NORMAL_SPC] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, KC_SPC ,     _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______, _______,
      _______      , _______   , _______    , KC_SPC      , _______,     _______, _______    , _______     , _______
  ),

  [_NUM] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,     _______, KC_P7  , KC_P8  , KC_P9  , _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,     _______, KC_P4  , KC_P5  , KC_P6  , _______, _______, _______,
      _______, _______, _______, _______, _______, _______,              KC_P0  , KC_P1  , KC_P2  , KC_P3  , _______, _______, _______,
      _______      , _______   , _______    , _______     , _______,     _______, _______    , _______     , _______
  ),

  [_SYMBOL] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
      _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_QUES, _______,
      _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, D_ARW  , _______,
      _______      , _______   , _______    , _______     , _______,     KC_BSPC, _______    , _______     , _______
  ),

  [_FN] = LAYOUT(
      _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
      _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_PSCR, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,              _______, KC_HOME, KC_END , _______, _______, D_ARW, _______,
      _______      , _______   , _______    , _______     , TG_SPC ,     KC_DEL , _______    , _______     , _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
      case S_ARW:
         if (record->event.pressed) {
            SEND_STRING("->");
         }
         return true;
      case D_ARW:
         if (record->event.pressed) {
            SEND_STRING("=>");
         }
         return true;
      default:
         return true;
   }
}

void encoder_update_user(uint8_t index, bool clockwise) {
  switch (index) {
    case _1ST:
      if (clockwise) {
        tap_code(KC_M);
      } else {
        tap_code(KC_B);
      }
      break;
    case _2ND:
      if (clockwise) {
        tap_code(KC_V);
      } else {
        tap_code(KC_W);
      }
      break;
  }
}

