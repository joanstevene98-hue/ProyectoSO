#ifndef DOMAIN_ENTITIES_KERNEL_MINIKERNEL_H
#define DOMAIN_ENTITIES_KERNEL_MINIKERNEL_H

#include "../pcb.h"
#include "../memory/block.h"
#include "../fs/fcb.h"

namespace domain::entities::kernel {

// Estructura centralizada para simular un mini-kernel que coordina todos los componentes
// En hexagonal, este sería parte del dominio pero orquestado desde application/use_cases
struct MiniKernelState {
    int current_time{0};
    int next_pid{1};
    // Las referencias a los puertos/adaptadores se inyectarán desde application layer
};

} // namespace domain::entities::kernel

#endif // DOMAIN_ENTITIES_KERNEL_MINIKERNEL_H
