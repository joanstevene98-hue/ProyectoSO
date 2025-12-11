#ifndef DOMAIN_PORTS_MEMORY_MEMORY_PORT_H
#define DOMAIN_PORTS_MEMORY_MEMORY_PORT_H

#include <optional>

namespace domain::ports::memory {

// Result: starting address or -1 / nullopt if failed
using AllocationResult = std::optional<int>;

class MemoryManagerPort {
public:
    virtual ~MemoryManagerPort() = default;
    virtual AllocationResult allocate(int pid, int size) = 0;
    virtual bool free(int pid) = 0;
    virtual void dump() = 0; // print memory map
};

} // namespace domain::ports::memory

#endif // DOMAIN_PORTS_MEMORY_MEMORY_PORT_H
