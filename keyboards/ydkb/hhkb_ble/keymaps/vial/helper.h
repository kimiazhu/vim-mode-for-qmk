//#include QMK_KEYBOARD_H
#ifndef MOD_NULL
    #define MODS_NULL 0
#endif

// 调用这个方法之前，先用 IS_LAYER_ON(3) 判断一下当前是否在 macOS 层
bool handle_mac(uint16_t keycode, keyrecord_t *record, uint16_t curr_key, uint8_t curr_mods, uint16_t to, uint8_t to_mods) {
    if (record->event.pressed) {
        if (keycode == curr_key && (curr_mods == MOD_BIT(KC_LSFT))) {
            if (to_mods) {
                register_mods(to_mods);
            }
            register_code(to);
            return false;
        }
    } else {
        if (keycode == curr_key && (curr_mods == MOD_BIT(KC_LSFT))) {
            unregister_code(to);
            if (to_mods) {
                unregister_mods(to_mods);
            }
            return false;
        }
    }
    return true;
}

#define MOVE_to_LAYER(layer) \
    else if (keycode == KC_##layer && held_mods == MOD_BIT(KC_RALT)) { \
        layer_move(layer); \
        curr_layer = layer; \
    }

#define HANDLE_DOWN_WIN(trigger, expected_mods, to, to_mods) \
    else if (IS_LAYER_ON(2) && (trigger == keycode) && (held_mods == expected_mods)) { \
        if (to_mods) { \
            register_mods(to_mods); \
        } \
        register_code(to); \
        is_active = true; \
    }
#define HANDLE_UP_WIN(trigger, expected_mods, to, to_mods) \
    else if (keycode == trigger && is_active) { \
        unregister_code(to); \
        if (to_mods) { \
            unregister_mods(MOD_MASK_CSAG); \
        } \
        is_active = false; \
    }


#define HANDLE_DOWN_MAC(trigger, expected_mods, to, to_mods) \
    else if (IS_LAYER_ON(3) && (trigger == keycode) && (held_mods == expected_mods)) { \
        if (to_mods) { \
            register_mods(to_mods); \
        } \
        register_code(to); \
        is_active = true; \
    }
#define HANDLE_UP_MAC(trigger, expected_mods, to, to_mods) \
    else if (keycode == trigger && is_active) { \
        unregister_code(to); \
        if (to_mods) { \
            unregister_mods(MOD_MASK_CSAG); \
        } \
        is_active = false; \
    }

#define HANDLE_DOWN_BOTH(trigger, expected_mods, to, to_mods) \
    else if ((IS_LAYER_ON(3) || IS_LAYER_ON(2)) && (trigger == keycode) && (held_mods == expected_mods)) { \
        if (to_mods) { \
            register_mods(to_mods); \
        } \
        register_code(to); \
        is_active = true; \
    }
#define HANDLE_UP_BOTH(trigger, expected_mods, to, to_mods) \
    else if (keycode == trigger && is_active) { \
        unregister_code(to); \
        if (to_mods) { \
            unregister_mods(MOD_MASK_CSAG); \
        } \
        is_active = false; \
    }
