#ifndef ADAPTERS_OUTBOUND_MEMORY_FIRST_FIT_H
#define ADAPTERS_OUTBOUND_MEMORY_FIRST_FIT_H

#include "../../../domain/ports/memory/memory_port.h"
#include "../../../domain/entities/memory/block.h"
#include <vector>
#include <map>

namespace adapters::outbound::memory {

/**
 * @class FirstFitMemory
 * @brief Implementación de gestor de memoria con algoritmo First-Fit
 * 
 * Algoritmo First-Fit:
 * 1. Recorre memoria de izquierda a derecha
 * 2. Asigna al PRIMER bloque libre que sea lo suficientemente grande
 * 3. Ventaja: Simple y rápido
 * 4. Desventaja: Genera fragmentación externa
 * 
 * Estructura de memoria:
 * - Representado como vector de int donde:
 *   - -1 = bloque libre
 *   - PID = bloque asignado a ese proceso
 * 
 * Ejemplos:
 * - [-1, -1, -1, 1, 1, 2, -1, 3, -1]  (memoria con fragmentación)
 * - [1, 1, 1, 2, 2, 3, 3, -1, -1]      (memoria sin fragmentación)
 * 
 * Complejidad:
 * - allocate(): O(n) donde n = tamaño total memoria
 * - free(): O(n)
 * - dump(): O(n) para visualización
 */
class FirstFitMemory : public domain::ports::memory::MemoryManagerPort {
private:
    int total_size;                                           ///< Tamaño total de memoria simulada
    std::vector<int> mem;                                     ///< Array: -1=libre, PID=asignado
    std::map<int, domain::entities::memory::Block> allocations;  ///< Registro: PID -> Block

public:
    /**
     * @brief Constructor
     * @param total Tamaño total de memoria en unidades
     */
    explicit FirstFitMemory(int total);
    
    /**
     * @brief Asigna memoria a un proceso
     * @param pid ID del proceso
     * @param size Tamaño requerido en unidades
     * @return Dirección inicial si exitoso, nullopt si falla
     * 
     * Algoritmo:
     * 1. Buscar primer bloque contiguo >= size
     * 2. Marcar como asignado (mem[i] = pid)
     * 3. Registrar en allocations map
     * 4. Retornar dirección inicial
     * 
     * Tiempo: O(n) en peor caso
     */
    domain::ports::memory::AllocationResult allocate(int pid, int size) override;
    
    /**
     * @brief Libera memoria asignada a un proceso
     * @param pid ID del proceso a liberar
     * @return true si exitoso, false si proceso no estaba asignado
     * 
     * Algoritmo:
     * 1. Buscar proceso en allocations
     * 2. Marcar bloques como libres (-1)
     * 3. Remover del registro
     * 
     * Nota: No realiza compactación (extensión futura)
     */
    bool free(int pid) override;
    
    /**
     * @brief Visualiza estado actual de memoria
     * 
     * Formato: [Memory Dump] 1112223...
     * - Punto (.) = bloque libre
     * - Número = PID del proceso asignado
     * 
     * Útil para entender fragmentación y estado general
     */
    void dump() override;
};

} // namespace adapters::outbound::memory

#endif // ADAPTERS_OUTBOUND_MEMORY_FIRST_FIT_H
