#include <iostream>
#include "../../../application/use_cases/integration_scenario.h"
#include "../../outbound/schedulers/fifo_scheduler.h"
#include "../../outbound/schedulers/rr_scheduler.h"
#include "../../outbound/memory/first_fit_memory.h"
#include "../../outbound/fs/in_memory_filesystem.h"
#include "../../outbound/devices/device_sim.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "  MINI-KERNEL SIMULATOR - FASE 4\n";
    std::cout << "  Integración, Pruebas y Depuración\n";
    std::cout << "========================================\n";

    // Initialize adapters
    adapters::outbound::schedulers::RR_Scheduler scheduler(3); // quantum=3
    adapters::outbound::memory::FirstFitMemory memory(64);      // 64 units
    adapters::outbound::fs::InMemoryFilesystem fs;
    adapters::outbound::devices::DeviceSimulator io;

    // Run integration scenarios
    application::use_cases::scenario_cpu_memory_race(scheduler, memory);
    
    // Reset for scenario 2
    adapters::outbound::schedulers::RR_Scheduler scheduler2(3);
    application::use_cases::scenario_concurrent_io(scheduler2, fs, io);

    // Reset for scenario 3 - full integration
    adapters::outbound::schedulers::RR_Scheduler scheduler3(3);
    adapters::outbound::memory::FirstFitMemory memory3(64);
    adapters::outbound::fs::InMemoryFilesystem fs3;
    adapters::outbound::devices::DeviceSimulator io3;
    application::use_cases::scenario_full_integration(scheduler3, memory3, fs3, io3);

    std::cout << "\n========================================\n";
    std::cout << "  All scenarios completed successfully!\n";
    std::cout << "========================================\n";

    return 0;
}
