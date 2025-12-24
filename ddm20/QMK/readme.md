# ddm20 – Numpad 5×4 con RP2040-Zero

<img width="800" height="800" alt="image" src="https://github.com/user-attachments/assets/dca2135d-e29b-46c3-a18f-bff96e2d2309" />


`ddm20` es un numpad / macropad ortolineal de 5 filas × 4 columnas, basado en un **RP2040-Zero**, cableado a mano (*handwired*) y pensado para usarse como keypad numérico principal con una segunda capa de navegación y multimedia.

El repositorio incluye:

- Configuración completa para **QMK** (`keyboard.json`, `keymap.c`, `config.h`, `rules.mk`).
- Diseño de **carcasa imprimible en 3D** en la carpeta `case/`.
- Esquema de cableado (filas, columnas, diodos) y materiales utilizados.

---

## Especificaciones de hardware

- **Controlador**: RP2040-Zero (clon chino tipo Pro Micro RP2040).
- **Distribución**: ortho 5×4.
- **Matriz**: 5 filas × 4 columnas.
- **Switches**: Outemu **Tactile Maple Leaf**, 3 pines (en mi montaje he usado 16 unidades).
- **Diodos**: 1N4148 DO-35, **uno por tecla**.
- **Cableado**: cable de silicona **24 AWG** para filas y columnas.
- **Tornillería**: tornillos **M3 × 16 mm** para cerrar la caja.
- **Tipo de escaneado**:
  - `diode_direction`: `ROW2COL`
  - Filas y columnas definidas en `keyboard.json`.
<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/5d69d2a2-8430-4d4c-8aeb-968c5170d782" />

### Asignación de pines (filas y columnas)

Cableado físico desde el RP2040-Zero:

**Filas** (de arriba a abajo, mirando el teclado desde arriba):

| Fila | Descripción       | Pin RP2040 |
|------|-------------------|------------|
| F0   | Fila 1 (arriba)   | `GP2`      |
| F1   | Fila 2            | `GP3`      |
| F2   | Fila 3            | `GP4`      |
| F3   | Fila 4            | `GP5`      |
| F4   | Fila 5 (abajo)    | `GP6`      |

**Columnas** (de izquierda a derecha, con diodos):

Cada tecla está cableada como:

```text
FILA → switch → diodo (1N4148) → COLUMNA
```

| Columna | Descripción            | Pin RP2040 |
|---------|------------------------|------------|
| C0      | Columna 1 (izquierda)  | `GP9`      |
| C1      | Columna 2              | `GP10`     |
| C2      | Columna 3              | `GP11`     |
| C3      | Columna 4 (derecha)    | `GP12`     |

### Diodos

- **Modelo**: 1N4148 DO-35.
- **Montaje**: un diodo por tecla, todos con la misma orientación.
- Todos los diodos de una columna se unen por el lado de columna (tras el diodo) a su cable de columna correspondiente.

---

## Carcasa e impresión 3D

En la carpeta `case/` se incluyen los ficheros STL para imprimir la carcasa y la estructura del teclado.

El diseño base está tomado de:

**4x5 Macro Pad v3 (nice!nano version)** – MakerWorld

y adaptado para montar el RP2040-Zero y el cableado handwired de este proyecto:

https://makerworld.com/en/models/1730477-4x5-macro-pad-v3-nice-nano-version

---

## Configuración de QMK

### keyboard.json

Configuración principal del teclado:

- **Procesador**: RP2040
- **Bootloader**: rp2040

**Matriz**:

```json
"matrix_pins": {
    "cols": ["GP9", "GP10", "GP11", "GP12"],
    "rows": ["GP2", "GP3", "GP4", "GP5", "GP6"]
}
```

**Dirección de los diodos**:

```json
"diode_direction": "ROW2COL"
```

### rules.mk

```make
# Para no heredar el "Pro Micro RP2040" por defecto
BOARD = GENERIC_RP_RP2040

# Para sacar consola de depuración (muy útil para ver matriz)
CONSOLE_ENABLE = yes
COMMAND_ENABLE = yes

# Habilitar combos (para el combo de bootloader)
COMBO_ENABLE = yes
```

- `BOARD = GENERIC_RP_RP2040` fuerza el uso del board genérico de RP2040.
- `CONSOLE_ENABLE = yes` permite usar `qmk console` para ver la matriz y mensajes de debug.
- `COMMAND_ENABLE = yes` habilita comandos especiales de QMK (Magic/Command).
- `COMBO_ENABLE = yes` activa el soporte de combos (usados para entrar en bootloader con varias teclas).

### config.h

Fragmento relevante para combos:

```c
#ifdef COMBO_ENABLE
#    define COMBO_TERM 100    // Ventana de tiempo (ms) para detectar el combo
#endif
```

---

## Keymap

En `keymap.c` se define, entre otras cosas:

```c
// Mute global del micro en Windows 11: Win + Alt + K
#define KC_WIN_MIC_MUTE LAG(KC_K)
```

### Capa 0 – Numpad (por defecto)

```c
[0] = LAYOUT_ortho_5x4(
    TG(1),   KC_CALC, KC_PSLS, KC_PAST,
    KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_P1,   KC_P2,   KC_P3,   S(KC_0),   // "=" en distribución ES → Shift + 0
    KC_PENT, KC_P0,   KC_PDOT, KC_PENT
),
```

**Funciones destacadas**:

- `TG(1)`: activa/desactiva la capa 1.
- `KC_CALC`: abre la calculadora de Windows.
- Números y operaciones estándar de un keypad numérico.
- `S(KC_0)`: envía Shift + 0, que en distribución española escribe `=` (así se consigue la tecla =).

### Capa 1 – Multimedia y navegación

Versión final de la distribución:

```c
[1] = LAYOUT_ortho_5x4(
    TG(1),           KC_HOME,        KC_PGUP,        KC_VOLD,
    KC_WIN_MIC_MUTE, KC_END,         KC_PGDN,        KC_VOLU,
    XXXXXXX,         KC_BRID,        KC_BRIU,        KC_MUTE,
    KC_MPRV,         KC_UP,          KC_MNXT,        KC_MPLY,
    KC_LEFT,         KC_DOWN,        KC_RGHT,        KC_ENT
)
```

**Resumen de funciones**:

**Fila 0**:
- `TG(1)`: alterna la capa 1.
- `KC_HOME`, `KC_PGUP`, `KC_VOLD`: inicio de línea, página arriba, volumen abajo.

**Fila 1**:
- `KC_WIN_MIC_MUTE`: mute global de micro en Windows 11 (Win + Alt + K).
- `KC_END`, `KC_PGDN`, `KC_VOLU`: fin de línea, página abajo, volumen arriba.

**Fila 2**:
- `KC_BRID`, `KC_BRIU`: brillo abajo/arriba (en sistemas que soporten estos keycodes).
- `KC_MUTE`: mute general.

**Fila 3**:
- `KC_MPRV`, `KC_MNXT`, `KC_MPLY`: pista anterior, siguiente y Play/Pause (Spotify, YouTube, etc. vía teclas multimedia del sistema).
- `KC_UP`: cursor arriba.

**Fila 4**:
- `KC_LEFT`, `KC_DOWN`, `KC_RGHT`, `KC_ENT`: cursores y Enter en la misma posición que en la capa numérica.

---

## Combo para entrar en bootloader

Además de las formas habituales de entrar en bootloader del RP2040-Zero, este teclado define un combo en la capa 0:

**Pulsar a la vez**: `5` + `7` + `*` del keypad numérico  
→ envía `QK_BOOT` y el teclado entra en modo bootloader.

**Implementación en `keymap.c`**:

```c
// Identificadores de combos
enum custom_combos {
    BOOT_COMBO,
};

// Combo para entrar en bootloader: pulsar 5 + 7 + * (KC_P5, KC_P7, KC_PAST)
const uint16_t PROGMEM boot_combo[] = { KC_P5, KC_P7, KC_PAST, COMBO_END };

combo_t key_combos[] = {
    [BOOT_COMBO] = COMBO(boot_combo, QK_BOOT),
};
```

El comportamiento del combo está controlado por `COMBO_TERM` en `config.h` (100 ms por defecto).

---

## Num Lock automático al arrancar

En `keyboard_post_init_user` se fuerza Num Lock activo al iniciar el teclado:

```c
void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;    
    
    // Forzar Num Lock activo al arrancar
    if (!host_keyboard_led_state().num_lock) {
        tap_code(KC_NUM_LOCK);
    }
}
```

Esto evita tener que pulsar Num Lock manualmente al conectar el numpad en portátiles sin keypad integrado.

---

## Compilación y flasheo

### Compilar con QMK (recomendado)

Desde la raíz de `qmk_firmware`:

```bash
qmk compile -kb ddm20 -km default
```

Esto genera un `.uf2` en la carpeta `.build/`.

### Flasheo en RP2040-Zero

1. Mantener pulsado el botón **BOOT** del RP2040-Zero mientras se conecta al USB.
2. Aparece una unidad de almacenamiento tipo `RPI-RP2` / similar.
3. Copiar el fichero `.uf2` generado a esa unidad.
4. El dispositivo se reinicia automáticamente con el nuevo firmware.

---

## Depuración de la matriz

Con `CONSOLE_ENABLE = yes` y:

```c
void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;
    ...
}
```

se puede ver el estado de la matriz con:

```bash
qmk console
```

Esto fue especialmente útil durante el montaje para verificar:

- Continuidad de filas y columnas.
- Dirección correcta de diodos.
- Detección individual de cada tecla (fila + columna).

---

## Mantenimiento y extensiones

El keymap actual está pensado como numpad principal con una segunda capa de navegación y multimedia.

Es sencillo modificar `keymap.c` para:

- Añadir macros (por ejemplo, combinaciones de atajos de desarrollo).
- Cambiar la tecla de `KC_CALC` por otra función.
- Ajustar la capa 1 a otro flujo de trabajo (edición de vídeo, atajos de IDE, etc.).

---

## Autor

**Keyboard Maintainer**: Daniel Durán ([@dandmol](https://github.com/dandmol))

---

## Licencia

El firmware y la configuración de QMK (`keyboard.json`, `keymap.c`, `config.h`, `rules.mk`, etc.) son un derivado de QMK y se distribuyen bajo licencia **GPL-2.0-or-later**.

La documentación de este repositorio (README, texto explicativo, etc.) y las fotos del montaje se publican bajo licencia **Creative Commons Atribución 4.0 (CC BY 4.0)**, salvo que se indique lo contrario.

Los modelos 3D de la carpeta `case/` son una adaptación del modelo "4x5 Macro Pad v3 (nice!nano version)" publicado en MakerWorld bajo licencia **Creative Commons Atribución–No Comercial (CC BY-NC)**.  
Esta adaptación mantiene la misma condición de uso no comercial: no se permite el uso comercial de la carcasa ni de sus derivados.

Cualquier modificación, PR o fork para añadir más layouts, variantes de carcasa o mejoras es bienvenida, siempre que respete las licencias anteriores.
