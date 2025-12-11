# DOCUMENTO TÉCNICO PROFESIONAL
## Simulador de Mini-Kernel en C++ (Arquitectura Hexagonal)

---

## ÍNDICE
1. [Resumen Ejecutivo](#resumen-ejecutivo)
2. [Descripción General del Sistema](#descripción-general-del-sistema)
3. [Arquitectura y Decisiones de Diseño](#arquitectura-y-decisiones-de-diseño)
4. [Módulos Implementados](#módulos-implementados)
5. [Algoritmos y Estructuras de Datos](#algoritmos-y-estructuras-de-datos)
6. [Integración de Componentes](#integración-de-componentes)
7. [Pruebas y Resultados](#pruebas-y-resultados)
8. [Instalación y Uso](#instalación-y-uso)
9. [Retos y Decisiones](#retos-y-decisiones)
10. [Extensiones Futuras](#extensiones-futuras)

---

## RESUMEN EJECUTIVO

Este documento describe el **Simulador de Mini-Kernel**, un sistema educativo que implementa los cuatro componentes fundamentales de un sistema operativo moderno:
- **Gestión de Procesos**: Planificadores FIFO y Round-Robin
- **Gestión de Memoria**: Asignador First-Fit con fragmentación
- **Gestión de Archivos**: Sistema de archivos en memoria
- **Gestión de E/S**: Simulador de dispositivos con interrupciones

El proyecto está implementado en **C++17** siguiendo la **Arquitectura Hexagonal**, lo que garantiza separación clara entre lógica de negocio (Domain), casos de uso (Application) e implementaciones técnicas (Adapters).

---

## DESCRIPCIÓN GENERAL DEL SISTEMA

### Propósito
El simulador permite estudiar y comprender el funcionamiento interno de un kernel de SO a través de:
- Visualización de transiciones de estado de procesos
- Cálculo y monitoreo de fragmentación de memoria
- Operaciones de archivos y gestión de E/S
- Escenarios integrados que demuestran la coordinación entre módulos

### Fases Implementadas

| Fase | Módulo | Alcance |
|------|--------|---------|
| 1 | Gestión de Procesos | PCB, FIFO, Round-Robin con transiciones de estado |
| 2 | Gestión de Memoria | First-Fit allocation/deallocation con fragmentación |
| 3 | Gestión de Archivos y E/S | FCB, operaciones CRUD de archivos, dispositivos simulados |
| 4 | Integración y Pruebas | 3 escenarios integrados, suite de unit tests |

---

## ARQUITECTURA Y DECISIONES DE DISEÑO

### Patrón Hexagonal (Ports & Adapters)

La arquitectura está dividida en tres capas:

```
┌─────────────────────────────────────────┐
│     ADAPTERS INBOUND (CLI Runners)      │
│  - main.cpp, memory_cli.cpp, etc.      │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│    APPLICATION LAYER (Use Cases)        │
│  - run_scheduler, manage_memory, etc.   │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│  DOMAIN LAYER (Núcleo de Negocio)       │
│  - Entities (PCB, FCB, Memory Block)    │
│  - Ports (Interfaces/Contratos)         │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│ ADAPTERS OUTBOUND (Implementaciones)    │
│  - Schedulers, Memory, FS, I/O Devices  │
└─────────────────────────────────────────┘
```

### Ventajas de este Diseño

1. **Independencia de Implementación**: Cambiar algoritmo de scheduling sin afectar la lógica de aplicación
2. **Testabilidad**: Fácil crear mocks de interfaces para pruebas
3. **Mantenibilidad**: Cada módulo tiene responsabilidad única
4. **Escalabilidad**: Agregar nuevos adaptadores sin cambiar el núcleo

### Decisiones Clave

| Decisión | Justificación |
|----------|---------------|
| C++17 | Soporte de structured bindings, optional<>, namespaces anidados |
| Hexagonal | Separación clara entre lógica de dominio e implementación |
| First-Fit | Simple pero suficiente para demostración; evita complejidad innecesaria |
| Round-Robin | Fairness demostrado; común en sistemas educativos |
| CMake | Builds portables entre plataformas (Windows, Linux, macOS) |

---

## MÓDULOS IMPLEMENTADOS

### I. GESTIÓN DE PROCESOS (Fase 1)

**Ubicación**: `src/domain/entities/pcb.h`, `src/adapters/outbound/schedulers/`

**PCB (Process Control Block)**
```cpp
struct PCB {
    int pid;                    // Identificador único
    std::string name;           // Nombre descriptivo
    int burst_time;             // Tiempo total de CPU requerido
    int remaining_time;         // Tiempo restante
    State state;                // Actual: New, Ready, Running, Waiting, Terminated
    int arrival_time;           // Para simulaciones futuras
};
```

**Estados Implementados**
```
New → Ready → Running → [Terminated / Ready] → Terminated
```

**Algoritmos de Planificación**

1. **FIFO (First In, First Out)**
   - Complejidad: O(1) por operación
   - Equidad: Baja (starving posible)
   - Uso: Baseline simple

2. **Round-Robin (RR)**
   - Complejidad: O(n) donde n es # procesos
   - Quantum: Configurable (default = 3 unidades)
   - Equidad: Alta (todos reciben tiempo)

**Transiciones de Estado**
```cpp
void change_state(PCB &p, State new_state);
```
Registra log de cada transición para debugging y visualización.

---

### II. GESTIÓN DE MEMORIA (Fase 2)

**Ubicación**: `src/adapters/outbound/memory/first_fit_memory.cpp`

**Estructura de Memoria**
```cpp
std::vector<int> mem;  // Array simulado donde mem[i] = -1 (libre) o PID (asignado)
std::map<int, Block> allocations;  // Registro de asignaciones
```

**Algoritmo First-Fit**
```
1. Escanear memoria de izquierda a derecha
2. Encontrar primer bloque contiguo de tamaño >= solicitado
3. Marcar como asignado y retornar dirección
4. Si no hay espacio: retornar nullopt
```

**Fragmentación**
- **Externa**: Espacios libres no contiguos no utilizables
- Demostración: Al asignar/liberar múltiples procesos, el dump visual muestra fragmentos

**Métodos Principales**
```cpp
AllocationResult allocate(int pid, int size);  // O(n)
bool free(int pid);                             // O(n)
void dump();                                    // Visualización
```

**Ejemplo de Dump**
```
[Memory Dump] 111..222..333.....
             (PID 1 - 3 unidades)
             (PID 2 - 3 unidades, con hueco)
             (PID 3 - 3 unidades, con hueco)
```

---

### III. GESTIÓN DE ARCHIVOS Y E/S (Fase 3)

**Ubicación**: `src/adapters/outbound/fs/`, `src/adapters/outbound/devices/`

**FCB (File Control Block)**
```cpp
struct FCB {
    std::string name;
    int size;           // Bytes (simulado)
    int start_block;    // Dirección de inicio
    bool open;          // Estado
};
```

**Operaciones Implementadas**

| Operación | Descripción | Complejidad |
|-----------|-------------|------------|
| `create(name)` | Crear nuevo archivo | O(1) |
| `open(name)` | Abrir archivo, obtener handle | O(log n) |
| `close(handle)` | Cerrar archivo por handle | O(1) |
| `remove(name)` | Eliminar (solo si no está open) | O(n) |
| `ls()` | Listar archivos y estado | O(n) |

**Dispositivos de E/S**
```cpp
struct IORequest {
    int pid;
    std::string data;
};

// Simulación de dispositivos (disco, red, etc.)
std::map<std::string, std::queue<IORequest>> queues;
```

**Simulación de E/S**
1. Proceso solicita operación a dispositivo
2. Solicitud se encola
3. `poll()` procesa una solicitud por dispositivo
4. Se notifica al proceso (simulado con log)

---

### IV. PRUEBAS (Fase 4)

**Estructura de Tests**
```
tests/
├── domain/
│   └── test_pcb.cpp              (2 tests)
├── application/
│   └── test_integration_scenarios.cpp  (3 tests)
└── adapters/
    ├── test_first_fit_memory.cpp      (3 tests)
    ├── test_in_memory_filesystem.cpp  (3 tests)
    └── test_schedulers.cpp             (2 tests)
```

**Total: 13 Unit Tests + 3 Escenarios de Integración**

**Escenarios de Integración**
1. **CPU + Memory Race**: Procesos compiten por CPU, asignan memoria
2. **Concurrent I/O**: Múltiples procesos con operaciones de archivo simultáneas
3. **Full Integration**: Todos los módulos trabajando juntos

---

## ALGORITMOS Y ESTRUCTURAS DE DATOS

### Algoritmo First-Fit Memory

```cpp
AllocationResult FirstFitMemory::allocate(int pid, int size) {
    int consec = 0;
    for (int i = 0; i < total_size; ++i) {
        if (mem[i] == -1) {  // Libre
            ++consec;
            if (consec == size) {
                int start = i - size + 1;
                // Marcar bloque como asignado
                for (int j = start; j <= i; ++j) 
                    mem[j] = pid;
                allocations[pid] = Block(start, size, pid);
                return start;
            }
        } else {
            consec = 0;  // Reiniciar contador
        }
    }
    return std::nullopt;  // Fallo
}
```

**Complejidad**: O(n) donde n = tamaño total de memoria
**Ventaja**: Simple, suficiente para educación
**Limitación**: No maneja compactación

### Algoritmo Round-Robin

```cpp
void RR_Scheduler::run() {
    while (!q.empty()) {
        PCB p = q.front(); q.pop_front();
        change_state(p, State::Running);
        
        int run_for = std::min(quantum, p.remaining_time);
        p.remaining_time -= run_for;
        time += run_for;
        
        if (p.remaining_time > 0) {
            change_state(p, State::Ready);
            q.push_back(p);  // Re-encolar
        } else {
            change_state(p, State::Terminated);
        }
    }
}
```

**Complejidad**: O(n × ceil(burst_time / quantum))
**Fairness**: Cada proceso recibe máximo `quantum` unidades por turno

---

## INTEGRACIÓN DE COMPONENTES

### Scenario 1: CPU + Memory Race

```
┌──────────────────┐
│   Create PCBs    │
└────────┬─────────┘
         │
┌────────▼──────────────────┐
│  Allocate Memory per PID  │
└────────┬─────────────────┘
         │
┌────────▼──────────────────┐
│   Execute on Scheduler    │
└────────┬─────────────────┘
         │
┌────────▼──────────────────┐
│   Free Memory per PID     │
└──────────────────────────┘
```

**Output Esperado**:
- Log de asignaciones de memoria
- Transiciones de estado de cada proceso
- Fragmentación visualizada en dump

###  Full Integration

Combina:
1. Creación de procesos
2. Asignación de memoria
3. Creación de archivos
4. Operaciones de E/S
5. Ejecución en CPU
6. Visualización final de estado

---

## PRUEBAS Y RESULTADOS

### Unit Tests

**Domain - PCB**
- ✅ `test_pcb_creation`: Verifica creación con atributos correctos
- ✅ `test_pcb_state_transitions`: Valida New→Ready→Running→Terminated

**Adapters - Memory**
- ✅ `test_memory_allocation`: Asignación exitosa en dirección 0
- ✅ `test_memory_allocation_failure`: Fallo cuando no hay espacio suficiente
- ✅ `test_memory_free`: Liberación y reasignación correcta

**Adapters - Filesystem**
- ✅ `test_filesystem_create`: Crear archivo
- ✅ `test_filesystem_open_close`: Abrir y cerrar
- ✅ `test_filesystem_remove`: Eliminar (con validación de archivo abierto)

**Adapters - Schedulers**
- ✅ `test_fifo_scheduler`: Ejecución FIFO sin preemption
- ✅ `test_rr_scheduler`: Ejecución RR con quantum=2

**Application - Integration**
- ✅ `scenario_cpu_memory_race`: Procesos × Memoria
- ✅ `scenario_concurrent_io`: Procesos × I/O
- ✅ `scenario_full_integration`: Procesos × Memoria × FS × I/O

---

## INSTALACIÓN Y USO

### Requisitos
- C++17 compatible compiler (g++, clang, MSVC)
- CMake 3.15+

### Build

```bash
cd cpp_os_simulator
mkdir build && cd build
cmake ..
cmake --build .
```

### Ejecutar Demos

```bash
./os_simulator_kernel      # Integración completa
./os_simulator_scheduler   # Solo procesos
./os_simulator_memory      # Solo memoria
./os_simulator_files       # Solo archivos/E/S
```

### Ejecutar Tests

```bash
ctest -V                   # Todos
ctest -R Memory_Tests -V   # Específico
```

---

## RETOS Y DECISIONES

### Reto 1: Separación de Responsabilidades
**Problema**: Múltiples módulos independientes necesitaban coordinarse
**Solución**: Arquitectura Hexagonal con inyección de dependencias a través de puertos

### Reto 2: Visualización de Memoria
**Problema**: Difícil ver estado interno de memoria
**Solución**: Método `dump()` que muestra memoria como string (. = libre, PID = asignado)

### Reto 3: Simulación de E/S
**Problema**: E/S real sería demasiado compleja
**Solución**: Colas FIFO por dispositivo con `poll()` que procesa una solicitud por dispositivo

### Reto 4: Portabilidad
**Problema**: Compilación diferente en Windows/Linux/Mac
**Solución**: CMake con configuración agnóstica



## CONCLUSIÓN

Este simulador demuestra un entendimiento profundo de:
- Componentes fundamentales de un SO
- Patrones de arquitectura profesionales
- Implementación robusta en C++
- Integración de módulos complejos
- Testing y validación de software



