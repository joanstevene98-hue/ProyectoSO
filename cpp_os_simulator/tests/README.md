# Testing Strategy - Mini Kernel Simulator

## Test Organization (Arquitectura Hexagonal)

Los tests están organizados por capas arquitectónicas:

```
tests/
├── domain/
│   └── test_pcb.cpp              # Unit tests de entidades del dominio
├── application/
│   └── test_integration_scenarios.cpp  # Tests de casos de uso integrados
└── adapters/
    ├── test_first_fit_memory.cpp      # Tests del adaptador Memory
    ├── test_in_memory_filesystem.cpp  # Tests del adaptador FS
    └── test_schedulers.cpp             # Tests de adaptadores Scheduler
```

## Descripción de Tests

### 1. Domain Tests (tests/domain/)

**test_pcb.cpp**
- `test_pcb_creation`: Verifica creación correcta de PCB con atributos iniciales
- `test_pcb_state_transitions`: Valida transiciones de estado (New → Ready → Running → Terminated)

### 2. Adapter Tests (tests/adapters/)

**test_first_fit_memory.cpp**
- `test_memory_allocation`: Verifica asignación exitosa de memoria
- `test_memory_allocation_failure`: Comprueba que falla cuando no hay espacio
- `test_memory_free`: Valida liberación y reasignación de memoria

**test_in_memory_filesystem.cpp**
- `test_filesystem_create`: Verifica creación de archivos
- `test_filesystem_open_close`: Valida abrir y cerrar archivos
- `test_filesystem_remove`: Comprueba eliminación de archivos

**test_schedulers.cpp**
- `test_fifo_scheduler`: Ejecuta FIFO y valida orden de procesos
- `test_rr_scheduler`: Ejecuta Round-Robin con quantum configurado

### 3. Application Tests (tests/application/)

**test_integration_scenarios.cpp**
- `scenario_cpu_memory_race`: Procesos compiten por CPU y memoria
- `scenario_concurrent_io`: Operaciones de I/O simultáneas
- `scenario_full_integration`: Integración completa de todos los módulos

## Ejecución de Tests

### Con CMake

```bash
cd build
ctest              # Ejecuta todos los tests
ctest -V           # Modo verbose
ctest -R PCB       # Ejecuta solo tests que coincidan con patrón
```

### Tests Individuales

```bash
./test_pcb
./test_memory
./test_filesystem
./test_schedulers
./test_integration
```

## Estrategia de Testing

1. **Aislamiento**: Cada test es independiente (no usa estado de otros tests)
2. **Reproducibilidad**: Los tests usan always los mismos datos iniciales
3. **Claridad**: Nombres descriptivos y estructura simple (sin frameworks externos)
4. **Cobertura**: Cubre happy path y error cases básicos

