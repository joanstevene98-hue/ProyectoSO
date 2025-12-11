# Arquitectura Hexagonal - Mini Kernel Simulator

## Resumen General

El proyecto implementa un **simulador de mini-kernel en C++** siguiendo la **arquitectura hexagonal**. Los cuatro componentes principales de un SO (procesos, memoria, archivos, E/S) están organizados en capas independientes, conectadas mediante puertos e interfaces.

## Estructura por Capas

### 1. **Domain Layer** (Núcleo del negocio)
   - **Entities** (`src/domain/entities/`):
     - `pcb.h/cpp`: Process Control Block (PID, estado, tiempos)
     - `memory/block.h`: Estructura de bloque de memoria
     - `fs/fcb.h`: File Control Block (meta-datos de archivo)
     - `kernel/minikernel.h`: Estado centralizado del kernel

   - **Ports** (Interfaces - contratos):
     - `src/domain/ports/scheduler_port.h`: Interfaz para planificadores
     - `src/domain/ports/memory/memory_port.h`: Interfaz para gestor de memoria
     - `src/domain/ports/fs/filesystem_port.h`: Interfaz para sistema de archivos
     - `src/domain/ports/io/io_port.h`: Interfaz para gestión de E/S

### 2. **Application Layer** (Casos de uso)
   - `src/application/use_cases/`:
     - `run_scheduler.h/cpp`: Orquesta ejecución de procesos
     - `manage_memory.h/cpp`: Demostración de gestión de memoria
     - `manage_files.h/cpp`: Operaciones de archivo y E/S
     - `integration_scenario.h/cpp`: Escenarios de integración (Fase 4)

### 3. **Adapters Layer** (Implementaciones concretas)

   **Inbound** (entradas de usuario):
   - `src/adapters/inbound/cli/`:
     - `main.cpp`: Demo de scheduler
     - `memory_cli.cpp`: Demo de memoria
     - `files_cli.cpp`: Demo de archivos/E/S
     - `kernel_runner.cpp`: Demo integrada (Fase 4)

   **Outbound** (adaptadores técnicos):
   - `src/adapters/outbound/schedulers/`:
     - `fifo_scheduler.h/cpp`: Planificador FIFO
     - `rr_scheduler.h/cpp`: Planificador Round-Robin

   - `src/adapters/outbound/memory/`:
     - `first_fit_memory.h/cpp`: Gestión de memoria con algoritmo First-Fit

   - `src/adapters/outbound/fs/`:
     - `in_memory_filesystem.h/cpp`: Sistema de archivos en memoria

   - `src/adapters/outbound/devices/`:
     - `device_sim.h/cpp`: Simulador de dispositivos E/S

## Fases Implementadas

| Fase | Tarea | Componentes | Estado |
|------|-------|-------------|--------|
| **1** | Definición e Estructura de Procesos | PCB, FIFO, RR | 
| **2** | Gestión de Memoria | Memory Manager (First-Fit) |
| **3** | Gestión de Archivos y E/S | Filesystem, Dispositivos |
| **4** | Integración y Pruebas | Scenarios 1-3, Kernel Integrado | 

## Escenarios de Prueba (Fase 4)

1. **Scenario 1: CPU + Memory Race**
   - Procesos compiten por CPU
   - Cada proceso solicita memoria
   - Se ejecutan y liberan memoria

2. **Scenario 2: Concurrent I/O**
   - Múltiples procesos abren archivos
   - Realizar operaciones de E/S simultáneamente
   - Prueba de aislamiento de dispositivos

3. **Scenario 3: Full Integration**
   - Combinación de todos los componentes
   - Procesos se ejecutan en CPU, asignan memoria, acceden a archivos y E/S
   - Demostración de coordinación global

## Flujo de Datos

```
[CLI Runner] 
    ↓
[Use Cases - Application]  (orquestación)
    ↓
[Ports - Domain]  (interfaces)
    ↓
[Adapters - Outbound]  (implementaciones)
    ↓
[Componentes técnicos: Scheduler, Memory, FS, IO]
```

## Compilación

Ver `cpp_os_simulator/README.md` para comandos de compilación específicos.

Compilación integrada (recomendado):
```bash
cd src
g++ -std=c++17 adapters/inbound/cli/kernel_runner.cpp \
  adapters/outbound/schedulers/{fifo,rr}_scheduler.cpp \
  adapters/outbound/memory/first_fit_memory.cpp \
  adapters/outbound/fs/in_memory_filesystem.cpp \
  adapters/outbound/devices/device_sim.cpp \
  application/use_cases/{run_scheduler,manage_memory,manage_files,integration_scenario}.cpp \
  domain/entities/pcb.cpp \
  -I../../include -o os_simulator_kernel
./os_simulator_kernel
```

## Próximas Extensiones

- Implementar paginación y memoria virtual (Fase 3 extendida)
- Agregar estadísticas: turnaround time, wait time, fragmentación
- Persistencia de archivos (serialización)
- Interfaz gráfica o REST API (nuevos adaptadores inbound)
