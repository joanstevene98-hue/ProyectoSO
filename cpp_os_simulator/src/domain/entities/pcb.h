#ifndef DOMAIN_ENTITIES_PCB_H
#define DOMAIN_ENTITIES_PCB_H

#include <string>

namespace domain::entities {

/**
 * @enum State
 * @brief Estados posibles de un proceso en el simulador
 * 
 * - New: Proceso creado pero no en cola ready
 * - Ready: Proceso esperando en cola para ejecutar
 * - Running: Proceso actualmente ejecutándose en CPU
 * - Waiting: Proceso bloqueado (esperando I/O, etc.)
 * - Terminated: Proceso finalizado
 */
enum class State { New, Ready, Running, Waiting, Terminated };

/**
 * @struct PCB
 * @brief Process Control Block - Estructura fundamental que representa un proceso
 * 
 * Contiene toda la información necesaria para:
 * - Identificar el proceso (PID, nombre)
 * - Gestionar su ejecución (burst_time, remaining_time)
 * - Seguimiento de estado (state, arrival_time)
 */
struct PCB {
    int pid;                    ///< Process ID (identificador único)
    std::string name;           ///< Nombre descriptivo del proceso
    int burst_time;             ///< Tiempo total de CPU requerido (unidades)
    int remaining_time;         ///< Tiempo de CPU restante por consumir
    State state;                ///< Estado actual del proceso
    int arrival_time;           ///< Tiempo de llegada al sistema (para simulaciones)

    /**
     * @brief Constructor de PCB
     * @param pid_ Identificador único del proceso
     * @param name_ Nombre descriptivo
     * @param burst Tiempo total de ejecución requerido
     * @param arrival Tiempo de llegada (default: 0)
     */
    PCB(int pid_, const std::string &name_, int burst, int arrival = 0)
        : pid(pid_), name(name_), burst_time(burst), remaining_time(burst), 
          state(State::New), arrival_time(arrival) {}
};

/**
 * @brief Convierte un estado a su representación en string
 * @param s Estado a convertir
 * @return String descriptivo del estado
 */
std::string state_to_string(State s);

/**
 * @brief Cambia el estado de un proceso e imprime la transición
 * @param p Proceso a actualizar
 * @param new_state Nuevo estado
 * 
 * Esta función registra cada transición de estado para:
 * - Debugging y trazabilidad
 * - Visualización de comportamiento del proceso
 * - Auditoría del ciclo de vida del proceso
 */
void change_state(PCB &p, State new_state);

} // namespace domain::entities

#endif // DOMAIN_ENTITIES_PCB_H
