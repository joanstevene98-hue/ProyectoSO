#include <iostream>
#include "../../../application/use_cases/run_scheduler.h"
#include "../../outbound/schedulers/fifo_scheduler.h"
#include "../../outbound/schedulers/rr_scheduler.h"

int main() {
    std::cout << "=== Simulador Fase 1 (Hexagonal) ===\n\n";

    std::cout << "-- Usando adaptador FIFO --\n";
    adapters::outbound::schedulers::FIFO_Scheduler fifo;
    application::use_cases::run_example(fifo);

    std::cout << "\n-- Usando adaptador Round-Robin (quantum=3) --\n";
    adapters::outbound::schedulers::RR_Scheduler rr(3);
    application::use_cases::run_example(rr);

    std::cout << "\nSimulación completada.\n";
    return 0;
}
