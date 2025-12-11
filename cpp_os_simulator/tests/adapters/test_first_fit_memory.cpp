#include <iostream>
#include <cassert>
#include "../../src/domain/entities/memory/block.h"
#include "../../src/adapters/outbound/memory/first_fit_memory.h"

using namespace adapters::outbound::memory;
using namespace domain::entities::memory;

void test_memory_allocation() {
    FirstFitMemory mem(32);
    auto res = mem.allocate(1, 8);
    assert(res.has_value());
    assert(*res == 0); // First allocation starts at 0
    std::cout << "[TEST PASS] Memory allocation\n";
}

void test_memory_allocation_failure() {
    FirstFitMemory mem(16);
    auto res1 = mem.allocate(1, 10);
    auto res2 = mem.allocate(2, 10); // Should fail (only 6 left)
    assert(res1.has_value());
    assert(!res2.has_value());
    std::cout << "[TEST PASS] Memory allocation failure\n";
}

void test_memory_free() {
    FirstFitMemory mem(32);
    auto res = mem.allocate(1, 8);
    assert(res.has_value());
    bool freed = mem.free(1);
    assert(freed);
    // Now should be able to allocate again
    auto res2 = mem.allocate(2, 8);
    assert(res2.has_value());
    std::cout << "[TEST PASS] Memory free\n";
}

int main() {
    std::cout << "=== Adapter Memory Tests ===\n";
    test_memory_allocation();
    test_memory_allocation_failure();
    test_memory_free();
    std::cout << "All memory adapter tests passed!\n";
    return 0;
}
