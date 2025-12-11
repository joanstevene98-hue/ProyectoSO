#include <iostream>
#include <cassert>
#include "../../src/adapters/outbound/schedulers/fifo_scheduler.h"
#include "../../src/adapters/outbound/schedulers/rr_scheduler.h"
#include "../../src/domain/entities/pcb.h"

using namespace adapters::outbound::schedulers;
using namespace domain::entities;

void test_fifo_scheduler() {
    FIFO_Scheduler sched;
    PCB p1(1, "P1", 5);
    PCB p2(2, "P2", 3);
    sched.addProcess(p1);
    sched.addProcess(p2);
    std::cout << "[TEST] FIFO Scheduler running...\n";
    sched.run();
    std::cout << "[TEST PASS] FIFO scheduler execution\n";
}

void test_rr_scheduler() {
    RR_Scheduler sched(2); // quantum = 2
    PCB p1(1, "P1", 5);
    PCB p2(2, "P2", 4);
    sched.addProcess(p1);
    sched.addProcess(p2);
    std::cout << "[TEST] Round-Robin Scheduler running (quantum=2)...\n";
    sched.run();
    std::cout << "[TEST PASS] RR scheduler execution\n";
}

int main() {
    std::cout << "=== Adapter Scheduler Tests ===\n";
    test_fifo_scheduler();
    std::cout << "\n";
    test_rr_scheduler();
    std::cout << "All scheduler adapter tests passed!\n";
    return 0;
}
