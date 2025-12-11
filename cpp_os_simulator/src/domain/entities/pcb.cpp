#include "pcb.h"
#include <iostream>

using namespace domain::entities;

std::string state_to_string(State s) {
    switch (s) {
        case State::New: return "New";
        case State::Ready: return "Ready";
        case State::Running: return "Running";
        case State::Waiting: return "Waiting";
        case State::Terminated: return "Terminated";
    }
    return "Unknown";
}

void change_state(PCB &p, State new_state) {
    std::cout << "PID " << p.pid << " (" << p.name << "): " << state_to_string(p.state)
              << " -> " << state_to_string(new_state) << "\n";
    p.state = new_state;
}
