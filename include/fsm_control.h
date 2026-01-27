#ifndef FSM_CONTROL_H
#define FSM_CONTROL_H

#include <stdint.h>  // Tipos de enteros de tamaño fijo (uint8_t, int32_t, etc.)
#include <stdbool.h> // Tipo booleano: true / false

/* ---------------- Estados ---------------- */
/* Enumeración de los posibles estados de la FSM */
typedef enum {
    FSM_SAFE = 0,    // Estado seguro: todo normal
    FSM_DANGER,      // Estado de peligro: alerta activa
    FSM_STATE_MAX    // Valor auxiliar: número total de estados
} fsm_state_t;

/* ---------------- Eventos ---------------- */
/* Enumeración de los posibles eventos que la FSM puede recibir */
typedef enum {
    EV_NONE = 0,     // Sin evento
    EV_SAFE,         // Evento que indica condición segura
    EV_DANGER,       // Evento que indica peligro
    EV_TIMEOUT,      // Evento de temporizador (para cambios automáticos de estado)
    FSM_EVENT_MAX    // Valor auxiliar: número total de eventos
} fsm_event_t;

/* ------------- Interfaz ---------- */

/* Inicializa la FSM
 * Debe establecer el estado inicial (probablemente FSM_SAFE)
 * y cualquier variable interna necesaria.
 */
void fsm_init(void);

/* Inyecta un evento en la FSM
 * 'ev' es el evento que la FSM debe procesar.
 * Dependiendo del estado actual y del evento, la FSM puede cambiar de estado.
 */
void fsm_dispatch(fsm_event_t ev);

/* Devuelve el estado actual de la FSM
 * Útil para depuración, trazabilidad o interfaces de usuario.
 */
fsm_state_t fsm_get_state(void);

#endif /* FSM_CONTROL_H */
