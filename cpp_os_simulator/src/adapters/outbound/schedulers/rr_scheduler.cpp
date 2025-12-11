#include "rr_scheduler.h"
#include "../../../domain/entities/pcb.h"
#include <iostream>
#include <algorithm>

using namespace adapters::outbound::schedulers;
using namespace domain::entities;

void RR_Scheduler::addProcess(const PCB &p) {
    PCB copy = p;
    change_state(copy, State::Ready);
    q.push_back(copy);
}

void RR_Scheduler::run() {
    std::cout << "[RR Adapter] Inicio de la ejecución (quantum=" << quantum << ")\n";
    int time = 0;
    while (!q.empty()) {
        PCB p = q.front(); q.pop_front();
        change_state(p, State::Running);
        int run_for = std::min(quantum, p.remaining_time);
        std::cout << "[RR Adapter] Ejecutando PID " << p.pid << " (" << p.name << ") por " << run_for << " unidades\n";
        p.remaining_time -= run_for;
        time += run_for;
        if (p.remaining_time > 0) {
            change_state(p, State::Ready);
            q.push_back(p);
        } else {
            change_state(p, State::Terminated);
        }
    }
    std::cout << "[RR Adapter] Finalizado (tiempo simulado: " << time << ")\n";
}
