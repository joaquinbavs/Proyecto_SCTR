#include "fsm_control.h"  // Incluye la definición de la FSM (estados, eventos, API)
#include "led.h"          // Funciones para controlar el LED (led_on, led_off, led_toggle)
#include "buzzer.h"       // Funciones para controlar el buzzer (buzzer_on, buzzer_off, buzzer_toggle)

/* ---------------- Tipo de transición ---------------- */
/* Definimos un puntero a función para las transiciones de estado.
 * Cada transición devuelve el nuevo estado después de ejecutar sus acciones.
 */
typedef fsm_state_t (*fsm_transition_t)(void);

/* ---------------- Estado actual ---------------- */
/* Variable estática que guarda el estado actual de la FSM */
static fsm_state_t current_state;

/* ---------------- Acciones / transiciones ---------- */

/* SAFE → DANGER
 * Se ejecuta cuando estamos en estado seguro y llega un evento de peligro.
 * Enciende LED y buzzer, luego devuelve FSM_DANGER como nuevo estado.
 */
static fsm_state_t trans_safe_to_danger(void)
{
    led_on();
    buzzer_on();
    return FSM_DANGER;
}

/* DANGER → SAFE
 * Se ejecuta cuando estamos en estado de peligro y llega un evento de seguridad.
 * Apaga LED y buzzer, luego devuelve FSM_SAFE como nuevo estado.
 */
static fsm_state_t trans_danger_to_safe(void)
{
    led_off();
    buzzer_off();
    return FSM_SAFE;
}

/* SAFE → SAFE (timeout: parpadeo)
 * Se ejecuta cuando estamos en estado seguro y ocurre un timeout.
 * Alterna (toggle) el LED y el buzzer para indicar actividad.
 * Permanece en FSM_SAFE.
 */
static fsm_state_t trans_safe_timeout(void)
{
    led_toggle();
    buzzer_toggle();
    return FSM_SAFE;
}

/* ---------------- Tabla de transición ---------------- */
/* Matriz que define qué función de transición ejecutar según el estado actual y el evento recibido.
 * La fila representa el estado actual.
 * La columna representa el evento recibido.
 * Si no hay transición para un evento en un estado, el valor es NULL.
 */
static const fsm_transition_t
fsm_table[FSM_STATE_MAX][FSM_EVENT_MAX] =
{
    [FSM_SAFE] = {
        [EV_DANGER]  = trans_safe_to_danger, // SAFE + DANGER → trans_safe_to_danger
        [EV_TIMEOUT] = trans_safe_timeout    // SAFE + TIMEOUT → trans_safe_timeout
    },
    [FSM_DANGER] = {
        [EV_SAFE] = trans_danger_to_safe     // DANGER + SAFE → trans_danger_to_safe
    }
};

/* ---------------- API ---------------- */

/* Inicializa la FSM
 * Coloca la FSM en el estado inicial (SAFE)
 * y asegura que LED y buzzer estén apagados.
 */
void fsm_init(void)
{
    current_state = FSM_SAFE;
    led_off();
    buzzer_off();
}

/* Inyecta un evento en la FSM
 * Verifica si el evento es válido, obtiene la función de transición
 * correspondiente desde la tabla y la ejecuta.
 */
void fsm_dispatch(fsm_event_t ev)
{
    if (ev >= FSM_EVENT_MAX) {
        return; // Evento inválido, no hacemos nada
    }

    // Obtener la función de transición desde la tabla
    fsm_transition_t tr = fsm_table[current_state][ev];

    // Si existe una transición definida, ejecutar y actualizar estado
    if (tr != NULL) {
        current_state = tr();
    }
}

/* Devuelve el estado actual de la FSM */
fsm_state_t fsm_get_state(void)
{
    return current_state;
}
