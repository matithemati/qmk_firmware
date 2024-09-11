// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "../config.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3
    )
};

#ifdef OLED_ENABLE

// Draw to OLED
bool oled_task_user() {
    // Set cursor position
    oled_set_cursor(0, 1);

    // oled_write_ln_P(PSTR((char *) &number), false);
    oled_set_cursor(0, 20);
    oled_write_ln_P(PSTR("TEST"), false);
    return false;
}
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif

enum custom_keycodes {
    EC11_BUTTON = SAFE_RANGE,  // Define a custom keycode for the EC11 button
};

// bool encoder_update_user(uint8_t index, bool clockwise) {
//     if (index == 0) { /* First encoder */
//         if (clockwise) {
//             tap_code(KC_PGDN);
//         } else {
//             tap_code(KC_PGUP);
//         }
//     } 
//     return false;
// }

void matrix_scan_user(void) {
    // Check the state of the EC11 button
    if (readPin(EC11_BUTTON_PIN) == 0) {
        // Button is pressed
        register_code(KC_MUTE);  // Example action on button press
    } else {
        // Button is not pressed
        unregister_code(KC_MUTE);  // Example action on button release
    }
}