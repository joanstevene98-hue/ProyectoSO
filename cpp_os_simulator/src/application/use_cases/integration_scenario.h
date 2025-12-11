#ifndef APPLICATION_USE_CASES_INTEGRATION_SCENARIO_H
#define APPLICATION_USE_CASES_INTEGRATION_SCENARIO_H

#include "../../domain/ports/scheduler_port.h"
#include "../../domain/ports/memory/memory_port.h"
#include "../../domain/ports/fs/filesystem_port.h"
#include "../../domain/ports/io/io_port.h"

namespace application::use_cases {

// Scenario 1: Procesos compiten por CPU y memoria
void scenario_cpu_memory_race(
    domain::ports::SchedulerPort &scheduler,
    domain::ports::memory::MemoryManagerPort &memory
);

// Scenario 2: Procesos con E/S simultáneo
void scenario_concurrent_io(
    domain::ports::SchedulerPort &scheduler,
    domain::ports::fs::FilesystemPort &fs,
    domain::ports::io::IOPort &io
);

// Scenario 3: Integración completa (CPU + Memoria + FS + E/S)
void scenario_full_integration(
    domain::ports::SchedulerPort &scheduler,
    domain::ports::memory::MemoryManagerPort &memory,
    domain::ports::fs::FilesystemPort &fs,
    domain::ports::io::IOPort &io
);

} // namespace application::use_cases

#endif // APPLICATION_USE_CASES_INTEGRATION_SCENARIO_H
