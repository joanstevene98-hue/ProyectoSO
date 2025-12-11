#include <iostream>
#include "../../src/adapters/outbound/schedulers/rr_scheduler.h"
#include "../../src/adapters/outbound/memory/first_fit_memory.h"
#include "../../src/adapters/outbound/fs/in_memory_filesystem.h"
#include "../../src/adapters/outbound/devices/device_sim.h"
#include "../../src/application/use_cases/integration_scenario.h"

int main() {
    std::cout << "=== Integration Scenario Tests ===\n";

    std::cout << "\n[TEST 1] CPU + Memory Race\n";
    adapters::outbound::schedulers::RR_Scheduler sched1(3);
    adapters::outbound::memory::FirstFitMemory mem1(64);
    application::use_cases::scenario_cpu_memory_race(sched1, mem1);

    std::cout << "\n[TEST 2] Concurrent I/O\n";
    adapters::outbound::schedulers::RR_Scheduler sched2(3);
    adapters::outbound::fs::InMemoryFilesystem fs2;
    adapters::outbound::devices::DeviceSimulator io2;
    application::use_cases::scenario_concurrent_io(sched2, fs2, io2);

    std::cout << "\n[TEST 3] Full Integration\n";
    adapters::outbound::schedulers::RR_Scheduler sched3(3);
    adapters::outbound::memory::FirstFitMemory mem3(64);
    adapters::outbound::fs::InMemoryFilesystem fs3;
    adapters::outbound::devices::DeviceSimulator io3;
    application::use_cases::scenario_full_integration(sched3, mem3, fs3, io3);

    std::cout << "\n=== All integration tests passed! ===\n";
    return 0;
}
