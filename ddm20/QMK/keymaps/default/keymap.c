// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Mute global del micro en Windows 11: Win + Alt + K
#define KC_WIN_MIC_MUTE LAG(KC_K)

// ----- COMBOS -----
enum custom_combos {
    BOOT_COMBO,
};

#ifdef COMBO_ENABLE
// 5 + 7 + * -> entra en bootloader
const uint16_t PROGMEM boot_combo[] = { KC_P5, KC_P7, KC_PAST, COMBO_END };

combo_t key_combos[] = {
    [BOOT_COMBO] = COMBO(boot_combo, QK_BOOT),
};
#endif

// ----- KEYMAPS -----
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
    // Layer 0: NumPad
    [0] = LAYOUT_ortho_5x4(
        TG(1),   KC_CALC, KC_PSLS, KC_PAST,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   S(KC_0),   // "=" en ES -> Shift + 0
        KC_PENT, KC_P0,   KC_PDOT, KC_PENT
    ),

    /*
     * Layer 1 – Media / Navegación
     *
     * ┌────────┬─────┬─────┬─────┐
     * │ TG1    │Home │PgUp │V-   │
     * ├────────┼─────┼─────┼─────┤
     * │ MicMute│End  │PgDn │V+   │
     * ├────────┼─────┼─────┼─────┤
     * │        │Br-  │Br+  │Mute │
     * ├────────┼─────┼─────┼─────┤
     * │ Prev   │ ↑   │Next │Play │
     * ├────────┼─────┼─────┼─────┤
     * │ ←      │ ↓   │ →   │Ent  │
     * └────────┴─────┴─────┴─────┘
     */
    [1] = LAYOUT_ortho_5x4(
        TG(1),           KC_HOME,        KC_PGUP,        KC_VOLD,
        KC_WIN_MIC_MUTE, KC_END,         KC_PGDN,        KC_VOLU,
        XXXXXXX,         KC_BRID,        KC_BRIU,        KC_MUTE,
        KC_MPRV,         KC_UP,          KC_MNXT,        KC_MPLY,
        KC_LEFT,         KC_DOWN,        KC_RGHT,        KC_ENT
    )
};

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;

    // Configurar el pin del LED de capa como salida y apagarlo de inicio
    setPinOutput(LED_LAYER_PIN);
    writePin(LED_LAYER_PIN, 0);  // 0 = apagado

    // Forzar Num Lock activo al arrancar
    if (!host_keyboard_led_state().num_lock) {
        tap_code(KC_NUM_LOCK);
    }
}

// Encender LED si la capa 1 está activa (TO(1), TG(1), MO(1), etc.)
layer_state_t layer_state_set_user(layer_state_t state) {
    bool layer1_on = layer_state_cmp(state, 1);
    writePin(LED_LAYER_PIN, layer1_on ? 1 : 0);

    return state;
}
