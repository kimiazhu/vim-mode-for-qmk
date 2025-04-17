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

static uint8_t saved_mods;
static bool handle_ctrl_direction(uint16_t trigger, uint16_t direction, keyrecord_t *record) {
    if (record->event.pressed) {
        saved_mods = get_mods();
        del_mods(MOD_MASK_CTRL);
        register_code(direction);
    } else {
        unregister_code(direction);
        set_mods(saved_mods);
    }
    return false;
}

#define HANDLE_CTRL_DIRECTION(trigger, direction) \
    else if (keycode == trigger && (get_mods() & MOD_MASK_CTRL)) { \
        if (record->event.pressed) { \
            uint8_t mods = get_mods(); \
            del_mods(MOD_MASK_CTRL); \
            register_code(direction); \
            set_mods(mods); \
        } else { \
            unregister_code(direction); \
        } \
        return false; \
    }


// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     if (0) {}  // 初始条件，仅为语法占位
//     HANDLE_CTRL_DIRECTION(KC_H, KC_LEFT)
//     HANDLE_CTRL_DIRECTION(KC_J, KC_DOWN)
//     HANDLE_CTRL_DIRECTION(KC_K, KC_UP)
//     HANDLE_CTRL_DIRECTION(KC_L, KC_RIGHT)
//     return true;
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t held_mods = 0;
    // 用来标记是否有组合键被激活，如果仅仅是修饰键被按下并释放，这时候应该直接发送给系统，
    // 比如 GUI 键单独按下释放用于激活系统菜单，SHIFT 单独按下释放用于切换输入法
    static bool is_combination_active = false;

    // 检查是否是修饰键
    // if (IS_MODIFIER_KEYCODE(keycode)) {
    if (keycode >= KC_LCTL && keycode <= KC_RGUI) {
        if (record->event.pressed) {
            held_mods |= MOD_BIT(keycode); // 记录按下的修饰键
        } else {
            held_mods &= ~MOD_BIT(keycode); // 清除释放的修饰键
            if (!is_combination_active) {
                // 如果没有组合键被激活，直接发送给系统
                tap_code(keycode);
            }

            if (!held_mods) {
                // 所有的 mods 组合键都释放了
                is_combination_active = false;
            }
            unregister_mods(MOD_BIT(keycode)); // 释放修饰键
        }

        // 特殊检查，如果是左 shift，直接发送给系统，因为可能是要切换中英输入法
        if (keycode == KC_LSFT) {
            if (record->event.pressed) {
                register_code(KC_LSFT); // 发送左 shift
            } else {
                unregister_code(KC_LSFT); // 释放左 shift
            }
        } else if (keycode == KC_RALT) {
            if (record->event.pressed) {
                unregister_mods(MOD_MASK_CSAG);
                // clear_mods(); // 清除所有修饰键
                held_mods = 0; // 清除 held_mods
            }
        }
        return false; // 拦截修饰键，不发送给系统
    } else {
        if (record->event.pressed && held_mods) {
            is_combination_active = true; // 组合键被激活
            register_mods(held_mods); // 临时激活修饰键
            register_code(keycode);  // 发送普通键
            return false; // 拦截原始按键事件
        } else {
            if (!record->event.pressed) {
                unregister_code(keycode); // 释放普通键
                // 这里之所以清除所有，是为了确保不会因为按键释放顺序导致错误，如果是用比如:
                // 如果只是 unregister_mods(held_mods) 的话，假设用户按下 CTRL+C，
                // 用户释放比较快，导致 CTRL 先释放了，再释放 C，这时候会导致 CTRL 无法正常释放，因为先释放的
                // CTRL 会改变 held_mods 的值。所以这里干脆直接把所有 mods 都 unregister。
                unregister_mods(MOD_MASK_CSAG); // 释放所有修饰键
                // unregister_mods(held_mods); // 释放修饰键
                return false;
            }
        }
    }
    return true; // 允许其他按键正常处理
}

#endif

