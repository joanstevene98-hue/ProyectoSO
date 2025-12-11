#ifndef DOMAIN_ENTITIES_MEMORY_BLOCK_H
#define DOMAIN_ENTITIES_MEMORY_BLOCK_H

#include <optional>

namespace domain::entities::memory {

struct Block {
    int start; // start index in simulated memory
    int size;  // size in units
    int pid;   // owner pid, -1 if free

    Block(int s=0,int sz=0,int p=-1):start(s),size(sz),pid(p){}
};

} // namespace domain::entities::memory

#endif // DOMAIN_ENTITIES_MEMORY_BLOCK_H
