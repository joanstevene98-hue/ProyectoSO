#include "fifo_scheduler.h"
#include "../../../domain/entities/pcb.h"
#include <iostream>

using namespace adapters::outbound::schedulers;
using namespace domain::entities;

void FIFO_Scheduler::addProcess(const PCB &p) {
    PCB copy = p;
    change_state(copy, State::Ready);
    q.push(copy);
}

void FIFO_Scheduler::run() {
    std::cout << "[FIFO Adapter] Inicio de la ejecución\n";
    int time = 0;
    while (!q.empty()) {
        PCB p = q.front(); q.pop();
        change_state(p, State::Running);
        std::cout << "[FIFO Adapter] Ejecutando PID " << p.pid << " (" << p.name << ") burst=" << p.burst_time << "\n";
        time += p.remaining_time;
        p.remaining_time = 0;
        change_state(p, State::Terminated);
    }
    std::cout << "[FIFO Adapter] Finalizado (tiempo simulado: " << time << ")\n";
}
