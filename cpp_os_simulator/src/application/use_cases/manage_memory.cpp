#include "manage_memory.h"
#include <iostream>

namespace application::use_cases {

void run_memory_demo(domain::ports::memory::MemoryManagerPort &mm) {
    std::cout << "=== Demo: Gestión de Memoria (First-Fit) ===\n";
    mm.dump();
    mm.allocate(10, 5); // pid 10 size 5
    mm.dump();
    mm.allocate(11, 3);
    mm.dump();
    mm.allocate(12, 8);
    mm.dump();
    mm.free(11);
    mm.dump();
    mm.allocate(13, 2);
    mm.dump();
    mm.free(10);
    mm.dump();
    mm.allocate(14, 6);
    mm.dump();
    std::cout << "=== Demo finalizada ===\n";
}

} // namespace application::use_cases
