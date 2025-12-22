// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Mute global del micro en Windows 11: Win + Alt + K
#define KC_WIN_MIC_MUTE LAG(KC_K)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬────┬───┬───┐
     * │TG1│Calc│ / │ * │
     * ├───┼────┼───┼───┤
     * │ 7 │ 8  │ 9 │ - │
     * ├───┼────┼───┼───┤
     * │ 4 │ 5  │ 6 │ + │
     * ├───┼────┼───┼───┤
     * │ 1 │ 2  │ 3 │ = │
     * ├───┼────┼───┼───┤
     * │Ent│ 0  │ . │ENT│
     * └───┴────┴───┴───┘
     */
    // Layer 0: Default Layer: NumPad
    [0] = LAYOUT_ortho_5x4(
        TG(1),   KC_CALC, KC_PSLS, KC_PAST,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   S(KC_0),
        KC_PENT, KC_P0,   KC_PDOT, KC_PENT
    ),

    /*
     * Layer 1
     * ┌────┬────┬────┬────┐
     * │TG1 │V-  │V+  │Mute│
     * ├────┼────┼────┼────┤
     * │Home│PgUp│Br- │Br+ │
     * ├────┼────┼────┼────┤
     * │End │PgDn│    │Mic │
     * ├────┼────┼────┼────┤
     * │    │ ↑  │    │boot│
     * ├────┼────┼────┼────┤
     * │ ←  │ ↓  │ →  │Ent │
     * └────┴────┴────┴────┘
     */
    // Layer 1: Media and Navigation
    [1] = LAYOUT_ortho_5x4(
        TG(1),   KC_VOLD,        KC_VOLU,        KC_MUTE,
        KC_HOME, KC_PGUP,        KC_BRID,        KC_BRIU,
        KC_END,  KC_PGDN,        XXXXXXX,        KC_WIN_MIC_MUTE,
        XXXXXXX, KC_UP,          XXXXXXX,        QK_BOOT,
        KC_LEFT, KC_DOWN,        KC_RGHT,        KC_ENT
    )
};

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;    
    
    // Forzar Num Lock activo al arrancar
    if (!host_keyboard_led_state().num_lock) {
        tap_code(KC_NUM_LOCK);
    }

}
