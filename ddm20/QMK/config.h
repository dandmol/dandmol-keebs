#pragma once

// Configuración específica del teclado ddm5x4

#ifdef COMBO_ENABLE
    // Tiempo máximo (en ms) entre pulsaciones para que cuente como combo.
    // Si pulsas las teclas con más separación que esto, se enviarán como teclas normales.
#    define COMBO_TERM 100
#endif
