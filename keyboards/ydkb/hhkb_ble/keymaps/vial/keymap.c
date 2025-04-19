#include QMK_KEYBOARD_H
#include "./helper.h"

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
static bool is_direction_down = false;
static bool is_active = false; // 标记一组快捷键生效，用于按键释放的时候触发 unregister_code

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t held_mods = 0;
    // 用来标记是否有组合键被激活，如果仅仅是修饰键被按下并释放，这时候应该直接发送给系统，
    // 比如 GUI 键单独按下释放用于激活系统菜单，SHIFT 单独按下释放用于切换输入法
    static bool is_combination_active = false;
    static int curr_layer = 0;

    // 检查是否是修饰键
    if (keycode >= KC_LCTL && keycode <= KC_RGUI) {
        if (record->event.pressed) {
            held_mods |= MOD_BIT(keycode);
        } else {
            held_mods &= ~MOD_BIT(keycode);

            if (!is_combination_active) {
                if (keycode == KC_RALT) {
                    // RALT 作为一个特殊键，长按加数字用于激活指定层，短按时用于清除所有修饰键和层信息
                    unregister_mods(MOD_MASK_CSAG);
                    clear_mods();
                    layer_clear();
                    curr_layer = 0;
                    held_mods = 0;
                } else {
                    tap_code(keycode);
                }
            }

            if (!held_mods) {
                // 所有的 mods 组合键都释放了
                is_combination_active = false;
            }
        }
        return false;
    } else {
        if (record->event.pressed && held_mods) {
            is_combination_active = true;
            // 在下面定义自己的组合键，2 层是 windows，3 层是 macOS
            if (0) {}
            MOVE_to_LAYER(1)
            MOVE_to_LAYER(2)
            MOVE_to_LAYER(3)
            else {
                if (0) {} // 初始条件，仅为语法占位
                HANDLE_DOWN_BOTH(KC_H, MOD_BIT(KC_LCTL), KC_LEFT, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_J, MOD_BIT(KC_LCTL), KC_DOWN, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_K, MOD_BIT(KC_LCTL), KC_UP, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_L, MOD_BIT(KC_LCTL), KC_RIGHT, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_H, MOD_BIT(KC_LALT), KC_LEFT, MOD_BIT(KC_LCTL)) // 终端后退一个单词
                HANDLE_DOWN_BOTH(KC_L, MOD_BIT(KC_LALT), KC_RIGHT, MOD_BIT(KC_LCTL)) // 终端前进一个单词
                HANDLE_DOWN_BOTH(KC_ESC, MOD_BIT(KC_LSFT), KC_GRV, MOD_BIT(KC_LSFT))
                HANDLE_DOWN_BOTH(KC_ESC, MOD_BIT(KC_LCTL), KC_GRV, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_BSPC, MOD_BIT(KC_LSFT), KC_BSLS, MOD_BIT(KC_LSFT))
                HANDLE_DOWN_BOTH(KC_BSPC, MOD_BIT(KC_LCTL), KC_BSLS, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_E, MOD_BIT(KC_LCTL), KC_END, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_QUOT, MOD_BIT(KC_LCTL), KC_BSPC, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_SCLN, MOD_BIT(KC_LCTL), KC_RETN, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_B, MOD_BIT(KC_LCTL), KC_BSPC, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_ESC, MOD_BIT(KC_LALT), KC_GRV, MOD_BIT(KC_LALT))
                HANDLE_DOWN_BOTH(KC_U, MOD_BIT(KC_LALT), KC_PGUP, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_D, MOD_BIT(KC_LALT), KC_PGDN, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_J, MOD_BIT(KC_LALT), KC_PGUP, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_K, MOD_BIT(KC_LALT), KC_PGDN, MODS_NULL)
                HANDLE_DOWN_BOTH(KC_D, MOD_BIT(KC_LCTL), KC_DEL, MODS_NULL)
                HANDLE_DOWN_MAC(KC_R, MOD_BIT(KC_LCTL), KC_R, MOD_BIT(KC_LGUI)) // reload browser
                HANDLE_DOWN_WIN(KC_A, MOD_BIT(KC_LCTL), KC_HOME, MODS_NULL)
                HANDLE_DOWN_WIN(KC_A, MOD_BIT(KC_LGUI), KC_A, MOD_BIT(KC_LCTL)) // win+A -> 全选
                HANDLE_DOWN_WIN(KC_Q, MOD_BIT(KC_LGUI), KC_F4, MOD_BIT(KC_LALT)) // win+Q -> 关闭窗口
                HANDLE_DOWN_WIN(KC_N, MOD_BIT(KC_LCTL), KC_F2, MODS_NULL) // ctrl+n -> rename
                HANDLE_DOWN_WIN(KC_C, MOD_BIT(KC_LGUI), KC_C, MOD_BIT(KC_LCTL)) // win+c -> copy
                HANDLE_DOWN_WIN(KC_V, MOD_BIT(KC_LGUI), KC_V, MOD_BIT(KC_LCTL)) // win+v -> paste
                else {
                    register_mods(held_mods);
                    register_code(keycode);
                }
            }
            return false;
        } else {
            if (!record->event.pressed) {
                if (keycode == MO(1)) {unregister_code(MO(1));layer_move(curr_layer);}
                HANDLE_UP_BOTH(KC_H, MOD_BIT(KC_LCTL), KC_LEFT, MODS_NULL)
                HANDLE_UP_BOTH(KC_J, MOD_BIT(KC_LCTL), KC_DOWN, MODS_NULL)
                HANDLE_UP_BOTH(KC_K, MOD_BIT(KC_LCTL), KC_UP, MODS_NULL)
                HANDLE_UP_BOTH(KC_L, MOD_BIT(KC_LCTL), KC_RIGHT, MODS_NULL)
                HANDLE_UP_BOTH(KC_H, MOD_BIT(KC_LALT), KC_LEFT, MOD_BIT(KC_LCTL)) // 终端后退一个单词
                HANDLE_UP_BOTH(KC_L, MOD_BIT(KC_LALT), KC_RIGHT, MOD_BIT(KC_LCTL)) // 终端前进一个单词
                HANDLE_UP_BOTH(KC_ESC, MOD_BIT(KC_LSFT), KC_GRV, MOD_BIT(KC_LSFT))
                HANDLE_UP_BOTH(KC_ESC, MOD_BIT(KC_LCTL), KC_GRV, MODS_NULL)
                HANDLE_UP_BOTH(KC_BSPC, MOD_BIT(KC_LSFT), KC_BSLS, MOD_BIT(KC_LSFT))
                HANDLE_UP_BOTH(KC_BSPC, MOD_BIT(KC_LCTL), KC_BSLS, MODS_NULL)
                HANDLE_UP_BOTH(KC_E, MOD_BIT(KC_LCTL), KC_END, MODS_NULL)
                HANDLE_UP_BOTH(KC_QUOT, MOD_BIT(KC_LCTL), KC_BSPC, MODS_NULL)
                HANDLE_UP_BOTH(KC_SCLN, MOD_BIT(KC_LCTL), KC_RETN, MODS_NULL)
                HANDLE_UP_BOTH(KC_B, MOD_BIT(KC_LCTL), KC_BSPC, MODS_NULL)
                HANDLE_UP_BOTH(KC_ESC, MOD_BIT(KC_LALT), KC_GRV, MOD_BIT(KC_LALT))
                HANDLE_UP_BOTH(KC_U, MOD_BIT(KC_LALT), KC_PGUP, MODS_NULL)
                HANDLE_UP_BOTH(KC_D, MOD_BIT(KC_LALT), KC_PGDN, MODS_NULL)
                HANDLE_UP_BOTH(KC_J, MOD_BIT(KC_LALT), KC_PGUP, MODS_NULL)
                HANDLE_UP_BOTH(KC_K, MOD_BIT(KC_LALT), KC_PGDN, MODS_NULL)
                HANDLE_UP_BOTH(KC_D, MOD_BIT(KC_LCTL), KC_DEL, MODS_NULL)
                HANDLE_UP_MAC(KC_R, MOD_BIT(KC_LCTL), KC_R, MOD_BIT(KC_LGUI))
                HANDLE_UP_WIN(KC_A, MOD_BIT(KC_LCTL), KC_HOME, MODS_NULL)
                HANDLE_UP_WIN(KC_A, MOD_BIT(KC_LGUI), KC_A, MOD_BIT(KC_LCTL)) // win+A -> 全选
                HANDLE_UP_WIN(KC_Q, MOD_BIT(KC_LGUI), KC_F4, MOD_BIT(KC_LALT)) // win+Q -> 关闭窗口
                HANDLE_UP_WIN(KC_N, MOD_BIT(KC_LCTL), KC_F2, MODS_NULL) // ctrl+n -> rename
                HANDLE_UP_WIN(KC_C, MOD_BIT(KC_LGUI), KC_C, MOD_BIT(KC_LCTL)) // win+c -> copy
                HANDLE_UP_WIN(KC_V, MOD_BIT(KC_LGUI), KC_V, MOD_BIT(KC_LCTL)) // win+v -> paste
                else {
                    unregister_code(keycode);
                    // 这里之所以清除所有，是为了确保不会因为按键释放顺序导致错误，如果是用比如:
                    // 如果只是 unregister_mods(held_mods) 的话，假设用户按下 CTRL+C，
                    // 用户释放比较快，导致 CTRL 先释放了，再释放 C，这时候会导致 CTRL 无法正常释放，因为先释放的
                    // CTRL 会改变 held_mods 的值。所以这里干脆直接把所有 mods 都 unregister。
                    unregister_mods(MOD_MASK_CSAG);
                    clear_mods();
                    // unregister_mods(held_mods);
                }
                return false;
            }
        }
    }
    return true;
}

#endif
