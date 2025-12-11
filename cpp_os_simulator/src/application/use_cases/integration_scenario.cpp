#include "integration_scenario.h"
#include "../../domain/entities/pcb.h"
#include <iostream>
#include <vector>

using namespace domain::entities;
using namespace domain::ports;

namespace application::use_cases {

void scenario_cpu_memory_race(
    SchedulerPort &scheduler,
    memory::MemoryManagerPort &memory)
{
    std::cout << "\n=== Scenario 1: CPU + Memory Race ===\n";
    std::cout << "[Scenario] Starting processes that allocate memory\n";

    // Create 4 processes
    std::vector<PCB> procs = {
        PCB(1, "P1_heavy", 10),
        PCB(2, "P2_light", 4),
        PCB(3, "P3_medium", 7),
        PCB(4, "P4_io", 5)
    };

    // Simulate: each process requests memory, then runs on CPU
    for (auto &p : procs) {
        scheduler.addProcess(p);
        int req_mem = p.burst_time * 2; // each process asks for 2x its burst time
        auto res = memory.allocate(p.pid, req_mem);
        if (res) {
            std::cout << "[Scenario] PID " << p.pid << " allocated memory at " << *res << "\n";
        } else {
            std::cout << "[Scenario] PID " << p.pid << " FAILED to allocate memory\n";
        }
    }

    memory.dump();
    std::cout << "[Scenario] Executing processes on CPU\n";
    scheduler.run();

    // Free memory
    std::cout << "[Scenario] Freeing memory after execution\n";
    for (auto &p : procs) {
        memory.free(p.pid);
    }
    memory.dump();
}

void scenario_concurrent_io(
    SchedulerPort &scheduler,
    fs::FilesystemPort &fs,
    io::IOPort &io)
{
    std::cout << "\n=== Scenario 2: Concurrent I/O Operations ===\n";
    std::cout << "[Scenario] Setting up filesystem and I/O devices\n";

    // Create files
    fs.create("data.txt");
    fs.create("log.txt");
    fs.ls();

    // Register I/O devices
    io.register_device("disk");
    io.register_device("network");

    // Open files and simulate I/O requests
    if (auto h = fs.open("data.txt")) {
        std::cout << "[Scenario] PID 10 opened data.txt (handle=" << *h << ")\n";
        io.request_io("disk", 10, "write data");
        io.poll();
        fs.close(*h);
    }

    if (auto h = fs.open("log.txt")) {
        std::cout << "[Scenario] PID 11 opened log.txt (handle=" << *h << ")\n";
        io.request_io("network", 11, "send log");
        io.poll();
        fs.close(*h);
    }

    fs.ls();
}

void scenario_full_integration(
    SchedulerPort &scheduler,
    memory::MemoryManagerPort &memory,
    fs::FilesystemPort &fs,
    io::IOPort &io)
{
    std::cout << "\n=== Scenario 3: Full Integration (CPU + Mem + FS + I/O) ===\n";

    std::cout << "[Scenario] Phase 1: Create processes and allocate resources\n";
    std::vector<PCB> procs = {
        PCB(100, "DataProcessor", 8),
        PCB(101, "FileWriter", 6),
        PCB(102, "NetReader", 5)
    };

    for (auto &p : procs) {
        scheduler.addProcess(p);
        auto mem_res = memory.allocate(p.pid, 10 + p.pid % 5);
        std::cout << "[Scenario] PID " << p.pid << " allocated mem=" << (mem_res ? std::to_string(*mem_res) : "FAILED") << "\n";
    }

    std::cout << "[Scenario] Phase 2: Setup filesystem\n";
    fs.create("process_data.bin");
    fs.create("output.log");
    if (auto h = fs.open("process_data.bin")) {
        std::cout << "[Scenario] PID 100 opened process_data.bin\n";
        io.register_device("disk");
        io.request_io("disk", 100, "read dataset");
        io.poll();
        fs.close(*h);
    }

    std::cout << "[Scenario] Phase 3: Execute on CPU scheduler (Round-Robin)\n";
    scheduler.run();

    std::cout << "[Scenario] Phase 4: Final state\n";
    memory.dump();
    fs.ls();

    std::cout << "[Scenario] Full integration scenario completed\n";
}

} // namespace application::use_cases
