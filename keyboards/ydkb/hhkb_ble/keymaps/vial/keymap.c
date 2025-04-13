#include QMK_KEYBOARD_H

#if 0
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {LAYOUT_all(KC_NO)};
#else
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
  [0] = {
    { KC_2,   KC_Q,   KC_W,   KC_S,   KC_A,   KC_Z,   KC_X,   KC_C,   },
    { KC_3,   KC_4,   KC_R,   KC_E,   KC_D,   KC_F,   KC_V,   KC_B,   },
    { KC_5,   KC_6,   KC_Y,   KC_T,   KC_G,   KC_H,   KC_N,   KC_NO,  },
    { KC_1,   KC_ESC, KC_TAB, KC_LCTL,KC_LSFT,KC_LALT,KC_LGUI,KC_SPC, },
    { KC_7,   KC_8,   KC_U,   KC_I,   KC_K,   KC_J,   KC_M,   KC_NO,  },
    { KC_BSLS,KC_GRV, KC_BSPC,KC_ENT, MO(1),  KC_RSFT,KC_RALT,KC_RGUI,},
    { KC_9,   KC_0,   KC_O,   KC_P,   KC_SCLN,KC_L,   KC_COMM,KC_NO,  },
    { KC_MINS,KC_EQL, KC_RBRC,KC_LBRC,KC_QUOT,KC_SLSH,KC_DOT, KC_CAPS,},
    { KC_LCTL,MO(1),  MO(1),  MO(1),  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,}
    },
  [1] = {
    { KC_F2,  USER00, KC_TRNS,KC_VOLU,KC_VOLD,USER03, KC_TRNS,KC_TRNS,},
    { KC_F3,  KC_F4,  KC_TRNS,USER02, KC_MUTE,KC_TRNS,KC_TRNS,USER01, },
    { KC_F5,  KC_F6,  KC_TRNS,KC_TRNS,KC_TRNS,KC_PAST,KC_PPLS,KC_TRNS,},
    { KC_F1,  KC_PWR, KC_CAPS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,},
    { KC_F7,  KC_F8,  USER04, KC_PSCR,KC_HOME,KC_PSLS,KC_PMNS,KC_TRNS,},
    { KC_INS, KC_DEL, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,},
    { KC_F9,  KC_F10, KC_SLCK,KC_PAUS,KC_LEFT,KC_PGUP,KC_END, KC_TRNS,},
    { KC_F11, KC_F12, KC_TRNS,KC_UP,  KC_RGHT,KC_DOWN,KC_PGDN,KC_TRNS,},
    { KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MUTE,KC_VOLD,KC_TRNS,KC_VOLU,}
    },
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_H && (get_mods() & MOD_MASK_CTRL)) {
        if (record->event.pressed) {
            // unregister_code(KC_LEFT_CTRL);
            // tap_code(KC_LEFT);
            // register_code(KC_LEFT_CTRL);

            // uint8_t mods = get_mods();  // 保存当前修饰键状态
            // del_mods(MOD_MASK_CTRL);    // 临时清除Ctrl
            // tap_code(KC_LEFT);          // 发送纯净的LEFT
            // set_mods(mods);             // 恢复原修饰键状态

            uint8_t mods = get_mods();  // 保存当前修饰键状态
            del_mods(MOD_MASK_CTRL);    // 临时清除Ctrl
            register_code(KC_LEFT);
            set_mods(mods);             // 恢复原修饰键状态
        } else {
            unregister_code(KC_LEFT);
        }
        return false;
    } else if (keycode == KC_J && (get_mods() & MOD_MASK_CTRL)) {
        if (record->event.pressed) {
            uint8_t mods = get_mods();  // 保存当前修饰键状态
            del_mods(MOD_MASK_CTRL);    // 临时清除Ctrl
            register_code(KC_DOWN);
            set_mods(mods);             // 恢复原修饰键状态
        } else {
            unregister_code(KC_DOWN);
        }
        return false;
    } else if (keycode == KC_K && (get_mods() & MOD_MASK_CTRL)) {
        if (record->event.pressed) {
            uint8_t mods = get_mods();  // 保存当前修饰键状态
            del_mods(MOD_MASK_CTRL);    // 临时清除Ctrl
            register_code(KC_UP);
            set_mods(mods);             // 恢复原修饰键状态
        } else {
            unregister_code(KC_UP);
        }
        return false;
    } else if (keycode == KC_L && (get_mods() & MOD_MASK_CTRL)) {
        if (record->event.pressed) {
            uint8_t mods = get_mods();  // 保存当前修饰键状态
            del_mods(MOD_MASK_CTRL);    // 临时清除Ctrl
            register_code(KC_RIGHT);
            set_mods(mods);             // 恢复原修饰键状态
        } else {
            unregister_code(KC_RIGHT);
        }
        return false;
    }
    return true;
}

#endif

