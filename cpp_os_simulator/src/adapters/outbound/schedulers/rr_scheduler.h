#ifndef ADAPTERS_OUTBOUND_RR_SCHEDULER_H
#define ADAPTERS_OUTBOUND_RR_SCHEDULER_H

#include "../../../domain/ports/scheduler_port.h"
#include "../../../domain/entities/pcb.h"
#include <deque>

namespace adapters::outbound::schedulers {

/**
 * @class RR_Scheduler
 * @brief Implementación de planificador Round-Robin (RR)
 * 
 * Algoritmo de planificación preemptive que:
 * 1. Otorga a cada proceso un quantum (time slice) fijo
 * 2. Si el proceso no termina en su quantum, vuelve al final de la cola
 * 3. Garantiza fairness: todos reciben tiempo de ejecución
 * 
 * Complejidad:
 * - Encolado: O(1)
 * - Ejecución: O(n × ceil(burst_time/quantum))
 * 
 * Ventajas:
 * - Fairness (ningún proceso starva indefinidamente)
 * - Respuesta rápida a nuevos procesos
 * 
 * Desventajas:
 * - Context switching overhead (simulado)
 * - Más cambios de contexto que FIFO
 */
class RR_Scheduler : public domain::ports::SchedulerPort {
    std::deque<domain::entities::PCB> q;  ///< Cola de procesos (ready queue)
    int quantum;                           ///< Quantum (time slice) para cada proceso

public:
    /**
     * @brief Constructor
     * @param q_ Quantum (unidades de tiempo por turno)
     */
    explicit RR_Scheduler(int q_) : quantum(q_) {}
    
    /**
     * @brief Añade un proceso a la cola ready
     * @param p Proceso a añadir
     */
    void addProcess(const domain::entities::PCB &p) override;
    
    /**
     * @brief Ejecuta todos los procesos con algoritmo RR
     * 
     * Algoritmo:
     * 1. Mientras haya procesos en la cola:
     *    a) Sacar proceso del frente
     *    b) Ejecutar por min(quantum, remaining_time)
     *    c) Si remaining_time > 0: reinsertar al final
     *    d) Else: marcar como Terminated
     */
    void run() override;
};

} // namespace adapters::outbound::schedulers

#endif // ADAPTERS_OUTBOUND_RR_SCHEDULER_H
