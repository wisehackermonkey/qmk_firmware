#include QMK_KEYBOARD_H

enum custom_keycodes {
    CM_1 = SAFE_RANGE,
    CM_2,
    CM_3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌─────┬─────┬─────┬───┬───┬───┐
     * │ CM1 │ CM2 │ CM3 │ 4 │ 5 │ 6 │
     * └─────┴─────┴─────┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_1x6(
        CM_1,   CM_2,   CM_3,   KC_BACKSPACE,   KC_ESCAPE,   KC_ENTER
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Only fire on key press (not release)
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case CM_1:
            SEND_STRING(SS_TAP(X_UP) SS_DELAY(100) SS_TAP(X_ENTER));
            return false;

        case CM_2:
            SEND_STRING(SS_TAP(X_UP) SS_DELAY(100) SS_TAP(X_RIGHT) SS_TAP(X_ENTER));
            return false;

        case CM_3:
            SEND_STRING(SS_TAP(X_UP) SS_DELAY(100) SS_TAP(X_RIGHT) SS_TAP(X_RIGHT) SS_TAP(X_ENTER));
            return false;
    }
    return true;
}