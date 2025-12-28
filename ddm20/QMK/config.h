#pragma once

// Configuración específica del teclado ddm20

// LED indicador de capa en GP1
#define LED_LAYER_PIN GP1

#ifdef COMBO_ENABLE
    // Tiempo máximo (en ms) entre pulsaciones para que cuente como combo.
    // Si pulsas las teclas con más separación que esto, se enviarán como teclas normales.
#    define COMBO_TERM 100
#endif
