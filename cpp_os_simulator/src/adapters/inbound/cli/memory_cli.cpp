#include <iostream>
#include "../../../application/use_cases/manage_memory.h"
#include "../../outbound/memory/first_fit_memory.h"

int main() {
    std::cout << "=== Simulador Fase 2: Gestión de Memoria ===\n\n";
    adapters::outbound::memory::FirstFitMemory mm(32); // 32 unidades de memoria simulada
    application::use_cases::run_memory_demo(mm);
    std::cout << "\nDemo de memoria completada.\n";
    return 0;
}
