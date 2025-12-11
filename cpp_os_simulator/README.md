Proyecto: Simulador Minikernel (C++) - Arquitectura Hexagonal

Fases implementadas:
- **Fase 1**: Gestión de Procesos (PCB, FIFO, Round-Robin)
- **Fase 2**: Gestión de Memoria (First-Fit allocation)
- **Fase 3**: Gestión de Archivos y E/S (filesystem en memoria + simulador de dispositivos)
- **Fase 4**: Integración, Pruebas y Depuración (escenarios de integración completa)

## Estructura Hexagonal

```
cpp_os_simulator/
├── src/
│   ├── domain/              # Núcleo del negocio
│   │   ├── entities/        # PCB, Memory, FS, Kernel
│   │   └── ports/           # Interfaces (contracts)
│   ├── application/         # Casos de uso y orquestación
│   │   └── use_cases/
│   └── adapters/            # Implementaciones técnicas
│       ├── inbound/cli/     # CLI runners (entry points)
│       └── outbound/        # Memory, Schedulers, FS, I/O
├── tests/                   # Tests separados por capa
│   ├── domain/              # Unit tests de entidades
│   ├── application/         # Tests de escenarios
│   └── adapters/            # Tests de adaptadores
└── CMakeLists.txt          # Build configuration
```

## Compilación con CMake (recomendado)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Ejecutar CLI Runners (Adapters Inbound)

```bash
./os_simulator_kernel          # Demo integrada (Fase 4)
./os_simulator_scheduler       # Demo de procesos (Fase 1)
./os_simulator_memory          # Demo de memoria (Fase 2)
./os_simulator_files           # Demo de archivos/E/S (Fase 3)
```

### Ejecutar Tests

```bash
# Correr todos los tests
ctest

# Correr test específico
ctest -R PCB_Tests -V
ctest -R Memory_Tests -V
ctest -R Filesystem_Tests -V
ctest -R Scheduler_Tests -V
ctest -R Integration_Tests -V
```

**Tests Disponibles:**
- `test_pcb`: Unit tests de entidad PCB (domain)
- `test_memory`: Unit tests del adaptador First-Fit (adapters)
- `test_filesystem`: Unit tests del FS en memoria (adapters)
- `test_schedulers`: Unit tests de FIFO y RR (adapters)
- `test_integration`: Tests de escenarios integrados (application)
