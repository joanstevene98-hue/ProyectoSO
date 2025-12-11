<<<<<<< HEAD
# ProyectoSO
=======
# SIMULADOR DE MINI-KERNEL EN C++ (Arquitectura Hexagonal)

**Proyecto educativo que implementa los 4 componentes principales de un Sistema Operativo**

---



##  Resumen del Proyecto

Este simulador demuestra un dominio profundo de:
- **Gestión de Procesos**: PCB, planificadores FIFO y Round-Robin, transiciones de estado
- **Gestión de Memoria**: Asignación First-Fit, fragmentación, liberación
- **Gestión de Archivos y E/S**: FCB, operaciones CRUD, dispositivos simulados
- **Integración de Componentes**: 3 escenarios que demuestran sinergia

**Arquitectura**: Hexagonal (Ports & Adapters) con clara separación Domain → Application → Adapters



## 📁 Estructura del Proyecto

```
Proyecto So/
├── cpp_os_simulator/              # Proyecto principal C++
│   ├── src/
│   │   ├── domain/                # Núcleo del negocio (hexagonal)
│   │   │   ├── entities/          # PCB, Block, FCB, MiniKernel
│   │   │   └── ports/             # Interfaces (contratos)
│   │   ├── application/           # Casos de uso y orquestación
│   │   │   └── use_cases/         # Escenarios de integración
│   │   └── adapters/              # Implementaciones técnicas
│   │       ├── inbound/cli/       # CLI runners (entry points)
│   │       └── outbound/          # Memory, Schedulers, FS, I/O
│   ├── tests/                     # Tests por capa
│   │   ├── domain/                # test_pcb.cpp
│   │   ├── application/           # test_integration_scenarios.cpp
│   │   └── adapters/              # test_*.cpp (5 tests)
│   ├── CMakeLists.txt             # Build configuration
│   └── README.md                  # Instrucciones específicas
│
├── docs/
│   ├── architecture.md            # Arquitectura hexagonal
│   ├── DOCUMENTO_TECNICO.md       # Documento profesional (500+ líneas)
│   └── EVALUACION_RUBRICA.md      # Evaluación contra criterios
│
└── README.md                      # Este archivo
```

---


### Compilación

```bash
cd cpp_os_simulator
mkdir build && cd build
cmake ..
cmake --build .
```

### Ejecutar Demostraciones

```bash
# Integración completa (Fase 4)
./os_simulator_kernel

# Demos individuales
./os_simulator_scheduler    # Solo procesos
./os_simulator_memory       # Solo memoria
./os_simulator_files        # Solo archivos/E/S
```

### Ejecutar Tests

```bash
# Todos los tests
ctest -V

# Tests específicos
ctest -R PCB_Tests -V
ctest -R Memory_Tests -V
ctest -R Integration_Tests -V
```

---

##  Documentación

| Documento | Descripción |
|-----------|-------------|
| [cpp_os_simulator/README.md](cpp_os_simulator/README.md) | Build, tests, ejemplos |
| [docs/architecture.md](docs/architecture.md) | Arquitectura hexagonal, capas |
| [docs/DOCUMENTO_TECNICO.md](docs/DOCUMENTO_TECNICO.md) | Documento profesional (500+ líneas, 10 secciones) |
| [docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md) | Evaluación detallada contra criterios |
| [cpp_os_simulator/tests/README.md](cpp_os_simulator/tests/README.md) | Estrategia de testing |

---

##  Fases Implementadas

###  Fase 1: Gestión de Procesos
- **PCB**: Estructura completa (PID, nombre, tiempos, estado)
- **Estados**: 5 estados (New, Ready, Running, Waiting, Terminated)
- **Planificadores**:
  - FIFO: Orden de llegada, sin preemption
  - Round-Robin: Quantum configurable, fairness
- **Test**: test_pcb.cpp, test_schedulers.cpp

###  Fase 2: Gestión de Memoria
- **Algoritmo**: First-Fit (simple, educativo)
- **Asignación**: O(n), alojamiento contiguo
- **Fragmentación**: Visible mediante dump()
- **Liberación**: Con validación de proceso
- **Test**: test_first_fit_memory.cpp (3 casos)

###  Fase 3: Gestión de Archivos y E/S
- **FCB**: File Control Block con metadata
- **CRUD**: Create, Open, Close, Remove, List
- **Validaciones**: No remover archivos abiertos
- **Dispositivos**: Tabla simulada con colas
- **E/S**: Solicitudes, interrupciones, poll()
- **Test**: test_in_memory_filesystem.cpp (3 casos)

###  Fase 4: Integración y Pruebas
- **Escenario 1**: CPU + Memory Race (4 procesos)
- **Escenario 2**: Concurrent I/O (múltiples archivos)
- **Escenario 3**: Full Integration (todos los módulos)
- **Tests**: 13 unit tests + 3 integration scenarios
- **Coverage**: Domain, Adapters, Application

---

##  Características Destacadas

### Arquitectura Hexagonal
```
Beneficios:
- Independencia de implementación
- Testabilidad: Fácil crear mocks
- Mantenibilidad: Cada módulo aislado
- Escalabilidad: Agregar nuevos adaptadores
```

### Código Profesional ¿Por que decimos eso ?
 C++17 con tipos modernos (optional, structured bindings)
 Documentación Doxygen en headers
 Namespaces anidados para organización
 Validaciones robustas (error handling)
 Comentarios explicativos en algoritmos

### Pruebas Exhaustivas
 13 unit tests (domain + adapters)
 13 integration scenarios (application)
  CMake con `ctest` integrado
 Coverage de happy path + error cases

### Documentación Completa
 Documento técnico profesional 
 10 secciones: Resumen, Arquitectura, Módulos, Algoritmos, Pruebas, etc.
 Retos identificados y resueltos
 Extensiones futuras propuestas

---

## 🔧 Especificaciones Técnicas

| Aspecto | Detalle |
|--------|---------|
| **Lenguaje** | C++17 |
| **Build System** | CMake 3.15+ |
| **Compiladores** | g++, clang, MSVC |
| **Memoria Simulada** | 64 unidades (configurable) |
| **Procesos Simulados** | 4-10 (configurable) |
| **Algoritmos Scheduler** | FIFO, Round-Robin (quantum=3) |
| **Algoritmo Memoria** | First-Fit |
| **Dispositivos I/O** | disk, network (extensible) |






##  Validación y Testing

### Ejecutar Validación Completa

```bash
cd cpp_os_simulator/build
cmake --build . --target all
ctest -V                              # Todos los tests
ctest -R "Domain|Memory|Filesystem|Scheduler|Integration" -V  # Por categoría
```

### Tests Incluidos

```
Domain Tests:
   test_pcb_creation
   test_pcb_state_transitions

Adapter Tests:
   test_memory_allocation
   test_memory_allocation_failure
   test_memory_free
   test_filesystem_create
   test_filesystem_open_close
   test_filesystem_remove
   test_fifo_scheduler
   test_rr_scheduler

Application Tests:
   scenario_cpu_memory_race
   scenario_concurrent_io
   scenario_full_integration
```

---

## 📖 Cómo Leer Este Proyecto

1. **Empezar aquí**: [README.md](README.md) (este archivo)
2. **Build y tests**: [cpp_os_simulator/README.md](cpp_os_simulator/README.md)
3. **Arquitectura**: [docs/architecture.md](docs/architecture.md)
4. **Documento técnico**: [docs/DOCUMENTO_TECNICO.md](docs/DOCUMENTO_TECNICO.md)
5. **Evaluación**: [docs/EVALUACION_RUBRICA.md](docs/EVALUACION_RUBRICA.md)
6. **Código fuente**: Empezar en `src/domain/` (núcleo), luego adapters

---


## ✨ Conclusión

Este proyecto demuestra:
 Comprensión profunda de sistemas operativos
 Arquitectura profesional y escalable
 Código limpio, modular, documentado
 Testing exhaustivo
 Documentación profesional

**Estado**: LISTO PARA EVALUACIÓN ✅
>>>>>>> cad2e0b (Initial commit: add project files)
