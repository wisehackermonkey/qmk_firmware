#include QMK_KEYBOARD_H

enum custom_keycodes {
    CM_1 = SAFE_RANGE,
    CM_2,
    CM_3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Layer 0 (default): macros
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │ CM1 │ CM2 │ CM3 │ BSP │ ESC │ ENT │
     * └─────┴─────┴─────┴─────┴─────┴─────┘
     */
    [0] = LAYOUT_ortho_1x6(
        CM_1,   CM_2,   CM_3,   KC_BACKSPACE,   KC_ESCAPE,   KC_ENTER
    ),

    /*
     * Layer 1 (hold key 1 while plugging in): number keys
     * ┌───┬───┬───┬───┬───┬───┐
     * │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │
     * └───┴───┴───┴───┴───┴───┘
     */
    [1] = LAYOUT_ortho_1x6(
        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6
    )
};

void keyboard_post_init_user(void) {
    // Scan the matrix a few times so debouncing settles and we see held keys
    for (uint8_t i = 0; i < 5; i++) {
        wait_ms(10);
        matrix_scan();
    }

    // If key [0,0] is held at power-on, use layer 1 as the base layer
    if (matrix_is_on(0, 0)) {
        default_layer_set(1UL << 1);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Only fire on key press (not release)
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case CM_1:
            SEND_STRING(SS_TAP(X_UP) SS_DELAY(100) SS_TAP(X_ENTER) SS_DELAY(200));
            return false;

        case CM_2:
            SEND_STRING(SS_TAP(X_UP) SS_DELAY(100) SS_TAP(X_RIGHT) SS_TAP(X_ENTER) SS_DELAY(200));
            return false;

        case CM_3:
            SEND_STRING(SS_TAP(X_UP) SS_DELAY(100) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_TAP(X_ENTER) SS_DELAY(200));
            return false;
    }
    return true;
}