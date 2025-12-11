# 📑 ÍNDICE DEL PROYECTO - Guía de Navegación

**Documento principal para entender la estructura y encontrar cualquier cosa rápidamente**

---

## 🎯 Acceso Rápido

### Para Empezar
- **[INICIO.md](INICIO.md)** ← **EMPIEZA AQUÍ** (5 min) - Quick start, compilación, ejecución
- **[README.md](README.md)** - Visión general, evaluación rúbrica
- **[CHECKLIST_EVALUACION.md](CHECKLIST_EVALUACION.md)** - Verificación contra criterios

### Para Entender la Arquitectura
- **[docs/architecture.md](docs/architecture.md)** - Arquitectura hexagonal explicada
- **[docs/DOCUMENTO_TECNICO.md](docs/DOCUMENTO_TECNICO.md)** - Documento técnico profesional (500+ líneas)

### Para Evaluar contra Rúbrica
- **[docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md)** - Evaluación detallada (5 criterios)

### Para Construir y Probar
- **[cpp_os_simulator/README.md](cpp_os_simulator/README.md)** - Build instructions
- **[cpp_os_simulator/tests/README.md](cpp_os_simulator/tests/README.md)** - Testing strategy

---

## 📁 Estructura de Carpetas

```
Proyecto So/
├── 📄 INICIO.md                    ← EMPIEZA AQUÍ
├── 📄 README.md                    Visión general
├── 📄 CHECKLIST_EVALUACION.md      Verificación contra rúbrica
├── 📄 INDEX.md                     Este archivo
├── 📄 .gitignore                   Git ignore rules
│
├── 📁 cpp_os_simulator/            Proyecto C++ principal
│   ├── 📄 README.md                Build y ejecución
│   ├── 📄 CMakeLists.txt           Build configuration
│   │
│   ├── 📁 src/                     CÓDIGO FUENTE
│   │   ├── 📁 domain/               Núcleo (Domain Layer)
│   │   │   ├── 📁 entities/        Estructuras: PCB, Block, FCB
│   │   │   │   ├── pcb.h/cpp       Process Control Block
│   │   │   │   ├── memory/block.h  Memory block
│   │   │   │   ├── fs/fcb.h        File Control Block
│   │   │   │   └── kernel/minikernel.h  Kernel state
│   │   │   └── 📁 ports/           Interfaces/contratos
│   │   │       ├── scheduler_port.h
│   │   │       ├── memory/memory_port.h
│   │   │       ├── fs/filesystem_port.h
│   │   │       └── io/io_port.h
│   │   │
│   │   ├── 📁 application/          Casos de Uso (Application Layer)
│   │   │   └── 📁 use_cases/       Orquestación
│   │   │       ├── run_scheduler.h/cpp
│   │   │       ├── manage_memory.h/cpp
│   │   │       ├── manage_files.h/cpp
│   │   │       └── integration_scenario.h/cpp  ★ Main scenarios
│   │   │
│   │   └── 📁 adapters/             Implementaciones (Adapters Layer)
│   │       ├── 📁 inbound/         Entry points
│   │       │   └── 📁 cli/         CLI runners
│   │       │       ├── main.cpp    Scheduler demo
│   │       │       ├── memory_cli.cpp  Memory demo
│   │       │       ├── files_cli.cpp   Files demo
│   │       │       └── kernel_runner.cpp  ★ Integrated demo
│   │       └── 📁 outbound/        Technical implementations
│   │           ├── 📁 schedulers/  Planificadores
│   │           │   ├── fifo_scheduler.h/cpp
│   │           │   └── rr_scheduler.h/cpp
│   │           ├── 📁 memory/      Gestión de memoria
│   │           │   └── first_fit_memory.h/cpp
│   │           ├── 📁 fs/          Sistema de archivos
│   │           │   └── in_memory_filesystem.h/cpp
│   │           └── 📁 devices/     Dispositivos I/O
│   │               └── device_sim.h/cpp
│   │
│   ├── 📁 tests/                    PRUEBAS (mismo layout que src/)
│   │   ├── 📁 domain/              Domain layer tests
│   │   │   └── test_pcb.cpp        PCB creation, state transitions
│   │   ├── 📁 adapters/            Adapter layer tests
│   │   │   ├── test_first_fit_memory.cpp     Memory: allocation, failure, free
│   │   │   ├── test_in_memory_filesystem.cpp Filesystem: create, open/close, remove
│   │   │   └── test_schedulers.cpp           Schedulers: FIFO, RR
│   │   ├── 📁 application/         Application layer tests
│   │   │   └── test_integration_scenarios.cpp  Scenario 1, 2, 3
│   │   └── 📄 README.md            Testing strategy
│   │
│   └── 📁 include/                 (Empty - not used in hexagonal)
│
└── 📁 docs/                         DOCUMENTACIÓN
    ├── 📄 architecture.md           Arquitectura hexagonal
    ├── 📄 DOCUMENTO_TECNICO.md      Documento profesional (500+ líneas)
    └── 📄 EVALUACION_RUBRICA.md    Evaluación contra 5 criterios (100/100)
```

---

##  Cómo Navegar por Criterio de Rúbrica

### GESTIÓN DE PROCESOS 

**Código**:
- [src/domain/entities/pcb.h](cpp_os_simulator/src/domain/entities/pcb.h) - Estructura PCB
- [src/adapters/outbound/schedulers/fifo_scheduler.cpp](cpp_os_simulator/src/adapters/outbound/schedulers/fifo_scheduler.cpp) - FIFO
- [src/adapters/outbound/schedulers/rr_scheduler.cpp](cpp_os_simulator/src/adapters/outbound/schedulers/rr_scheduler.cpp) - Round-Robin

**Tests**:
- [tests/domain/test_pcb.cpp](cpp_os_simulator/tests/domain/test_pcb.cpp)
- [tests/adapters/test_schedulers.cpp](cpp_os_simulator/tests/adapters/test_schedulers.cpp)

**Documentación**:
- [docs/DOCUMENTO_TECNICO.md](docs/DOCUMENTO_TECNICO.md) - Sección 5: Algoritmos
- [docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md) - Sección I

---

### GESTIÓN DE MEMORIA 

**Código**:
- [src/domain/entities/memory/block.h](cpp_os_simulator/src/domain/entities/memory/block.h) - Estructura Block
- [src/adapters/outbound/memory/first_fit_memory.h](cpp_os_simulator/src/adapters/outbound/memory/first_fit_memory.h)
- [src/adapters/outbound/memory/first_fit_memory.cpp](cpp_os_simulator/src/adapters/outbound/memory/first_fit_memory.cpp) - First-Fit

**Tests**:
- [tests/adapters/test_first_fit_memory.cpp](cpp_os_simulator/tests/adapters/test_first_fit_memory.cpp)

**Documentación**:
- [docs/DOCUMENTO_TECNICO.md](docs/DOCUMENTO_TECNICO.md) - Sección 5: First-Fit
- [docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md) - Sección II

---

### GESTIÓN DE ARCHIVOS Y E/S 

**Código**:
- [src/domain/entities/fs/fcb.h](cpp_os_simulator/src/domain/entities/fs/fcb.h) - Estructura FCB
- [src/adapters/outbound/fs/in_memory_filesystem.h](cpp_os_simulator/src/adapters/outbound/fs/in_memory_filesystem.h)
- [src/adapters/outbound/fs/in_memory_filesystem.cpp](cpp_os_simulator/src/adapters/outbound/fs/in_memory_filesystem.cpp) - Filesystem
- [src/adapters/outbound/devices/device_sim.h](cpp_os_simulator/src/adapters/outbound/devices/device_sim.h)
- [src/adapters/outbound/devices/device_sim.cpp](cpp_os_simulator/src/adapters/outbound/devices/device_sim.cpp) - I/O Devices

**Tests**:
- [tests/adapters/test_in_memory_filesystem.cpp](cpp_os_simulator/tests/adapters/test_in_memory_filesystem.cpp)

**Documentación**:
- [docs/DOCUMENTO_TECNICO.md](docs/DOCUMENTO_TECNICO.md) - Sección 4: Módulos
- [docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md) - Sección III

---

### CALIDAD CÓDIGO Y PRUEBAS 

**Compilación**:
- [cpp_os_simulator/CMakeLists.txt](cpp_os_simulator/CMakeLists.txt) - Build system

**Código**:
- Todos los archivos `.h` tienen Doxygen documentation
- Ejemplos: pcb.h, first_fit_memory.h, rr_scheduler.h

**Tests**:
- Todos los archivos en [tests/](cpp_os_simulator/tests/)
- Total: 13 unit tests + 3 integration scenarios

**Documentación**:
- [docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md) - Sección IV

---

###  DOCUMENTACIÓN TÉCNICA 

**Documentos principales**:
- [docs/DOCUMENTO_TECNICO.md](docs/DOCUMENTO_TECNICO.md) - ⭐ Documento técnico completo (500+ líneas, 10 secciones)
- [docs/architecture.md](docs/architecture.md) - Arquitectura hexagonal
- [docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md) - Evaluación detallada
- [README.md](README.md) - Visión general
- [INICIO.md](INICIO.md) - Quick start

**En el código**:
- Headers con Doxygen comments
- Métodos documentados con propósito y complejidad

**Documentación**:
- [docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md) - Sección V



## 🔍 Búsqueda Rápida

### Busco... implementación de...
- **PCB**: [src/domain/entities/pcb.h](cpp_os_simulator/src/domain/entities/pcb.h)
- **FIFO Scheduler**: [src/adapters/outbound/schedulers/fifo_scheduler.cpp](cpp_os_simulator/src/adapters/outbound/schedulers/fifo_scheduler.cpp)
- **Round-Robin**: [src/adapters/outbound/schedulers/rr_scheduler.cpp](cpp_os_simulator/src/adapters/outbound/schedulers/rr_scheduler.cpp)
- **First-Fit Memory**: [src/adapters/outbound/memory/first_fit_memory.cpp](cpp_os_simulator/src/adapters/outbound/memory/first_fit_memory.cpp)
- **Filesystem**: [src/adapters/outbound/fs/in_memory_filesystem.cpp](cpp_os_simulator/src/adapters/outbound/fs/in_memory_filesystem.cpp)
- **I/O Devices**: [src/adapters/outbound/devices/device_sim.cpp](cpp_os_simulator/src/adapters/outbound/devices/device_sim.cpp)

### Busco... test de...
- **PCB**: [tests/domain/test_pcb.cpp](cpp_os_simulator/tests/domain/test_pcb.cpp)
- **Memory**: [tests/adapters/test_first_fit_memory.cpp](cpp_os_simulator/tests/adapters/test_first_fit_memory.cpp)
- **Filesystem**: [tests/adapters/test_in_memory_filesystem.cpp](cpp_os_simulator/tests/adapters/test_in_memory_filesystem.cpp)
- **Schedulers**: [tests/adapters/test_schedulers.cpp](cpp_os_simulator/tests/adapters/test_schedulers.cpp)
- **Integration**: [tests/application/test_integration_scenarios.cpp](cpp_os_simulator/tests/application/test_integration_scenarios.cpp)

### Busco... arquitectura/diseño...
- **Visión general**: [README.md](README.md)
- **Arquitectura**: [docs/architecture.md](docs/architecture.md)
- **Decisiones técnicas**: [docs/DOCUMENTO_TECNICO.md](docs/DOCUMENTO_TECNICO.md)
- **Evaluación vs rúbrica**: [docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md)

### Busco... compilar y ejecutar...
- **Build instructions**: [cpp_os_simulator/README.md](cpp_os_simulator/README.md)
- **Quick start**: [INICIO.md](INICIO.md)
- **Testing strategy**: [cpp_os_simulator/tests/README.md](cpp_os_simulator/tests/README.md)



##  Conclusión

**Este índice te ayuda a navegar el proyecto rápidamente según tus necesidades:**

- ¿**Quieres empezar?** → [INICIO.md](INICIO.md)
- ¿**Quieres compilar?** → [cpp_os_simulator/README.md](cpp_os_simulator/README.md)
- ¿**Quieres entender?** → [docs/architecture.md](docs/architecture.md)
- ¿**Quieres evaluación?** → [docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md)
- ¿**Quieres buscar algo?** → Usa la sección "Búsqueda Rápida"

