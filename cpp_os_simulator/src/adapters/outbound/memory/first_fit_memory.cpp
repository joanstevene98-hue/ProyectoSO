#include "first_fit_memory.h"
#include <iostream>

using namespace adapters::outbound::memory;
using namespace domain::entities::memory;
using domain::ports::memory::AllocationResult;

FirstFitMemory::FirstFitMemory(int total): total_size(total), mem(total, -1) {}

AllocationResult FirstFitMemory::allocate(int pid, int size) {
    if (size <= 0 || size > total_size) return std::nullopt;
    // First-Fit: scan mem for a contiguous free block of length >= size
    int consec = 0;
    for (int i = 0; i < total_size; ++i) {
        if (mem[i] == -1) {
            ++consec;
        } else {
            consec = 0;
        }
        if (consec == size) {
            int start = i - size + 1;
            for (int j = start; j <= i; ++j) mem[j] = pid;
            allocations[pid] = Block(start, size, pid);
            std::cout << "[Memory First-Fit] Allocated pid=" << pid << " start=" << start << " size=" << size << "\n";
            return start;
        }
    }
    std::cout << "[Memory First-Fit] Allocation failed pid=" << pid << " size=" << size << "\n";
    return std::nullopt;
}

bool FirstFitMemory::free(int pid) {
    auto it = allocations.find(pid);
    if (it == allocations.end()) return false;
    Block b = it->second;
    for (int i = b.start; i < b.start + b.size; ++i) mem[i] = -1;
    allocations.erase(it);
    std::cout << "[Memory First-Fit] Freed pid=" << pid << " start=" << b.start << " size=" << b.size << "\n";
    return true;
}

void FirstFitMemory::dump() {
    std::cout << "[Memory Dump] ";
    for (int i = 0; i < total_size; ++i) {
        if (mem[i] == -1) std::cout << ".";
        else std::cout << mem[i];
    }
    std::cout << "\n";
}
