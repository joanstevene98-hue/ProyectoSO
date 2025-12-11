#include <iostream>
#include <cassert>
#include "../../src/domain/entities/pcb.h"

using namespace domain::entities;

void test_pcb_creation() {
    PCB p(1, "TestProcess", 5);
    assert(p.pid == 1);
    assert(p.name == "TestProcess");
    assert(p.burst_time == 5);
    assert(p.remaining_time == 5);
    assert(p.state == State::New);
    std::cout << "[TEST PASS] PCB creation\n";
}

void test_pcb_state_transitions() {
    PCB p(2, "StateTest", 3);
    change_state(p, State::Ready);
    assert(p.state == State::Ready);
    change_state(p, State::Running);
    assert(p.state == State::Running);
    change_state(p, State::Terminated);
    assert(p.state == State::Terminated);
    std::cout << "[TEST PASS] PCB state transitions\n";
}

int main() {
    std::cout << "=== Domain Entity Tests ===\n";
    test_pcb_creation();
    test_pcb_state_transitions();
    std::cout << "All domain tests passed!\n";
    return 0;
}
