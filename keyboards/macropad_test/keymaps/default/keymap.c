#include QMK_KEYBOARD_H
#include "config.h"
#include "raw_hid.h"

char oled_data[32] = {0};  // Adjust size as needed

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3
    )
};

// Function that runs when the device starts up
void startup_user(void) {
    // Wait for the device to stabilize
    matrix_init();

    // Scan the matrix to get the key states
    matrix_scan();

    // Check if the boot key is pressed
    if (matrix_is_on(0, 0)) {  // Replace with the correct row/column for BOOT_KEY
        reset_keyboard();  // Enter bootloader mode
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length > sizeof(oled_data) - 1) {
        length = sizeof(oled_data) - 1;  // Ensure we do not overflow the buffer
    }

    // Clear the buffer
    memset(oled_data, 0, sizeof(oled_data));

    // Copy the received data to the OLED buffer
    memcpy(oled_data, data, length);

    // Optionally send a response
    if (data[0] == 'A') {
        uint8_t response[length];
        memset(response, 0, length);
        response[0] = 'B';
        raw_hid_send(response, length);
    }
}

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        // oled_clear();
        
        // Display the HID data on the OLED
        oled_write_ln("Now playing:", false);
        oled_write_ln(oled_data, false);  // Display the data stored in oled_data

        return false;
    }
#endif

bool dip_switch_update_user(uint8_t index, bool active) { 
    switch (index) {
        case 0:
        if(active) { 
            tap_code(KC_MUTE);
        }
        break;
    }
    return false;
}