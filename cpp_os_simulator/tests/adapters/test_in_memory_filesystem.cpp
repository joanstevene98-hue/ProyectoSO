#include <iostream>
#include <cassert>
#include "../../src/adapters/outbound/fs/in_memory_filesystem.h"

using namespace adapters::outbound::fs;

void test_filesystem_create() {
    InMemoryFilesystem fs;
    bool created = fs.create("test.txt");
    assert(created);
    // Try creating again (should fail)
    bool created2 = fs.create("test.txt");
    assert(!created2);
    std::cout << "[TEST PASS] Filesystem create\n";
}

void test_filesystem_open_close() {
    InMemoryFilesystem fs;
    fs.create("data.bin");
    auto h = fs.open("data.bin");
    assert(h.has_value());
    bool closed = fs.close(*h);
    assert(closed);
    std::cout << "[TEST PASS] Filesystem open/close\n";
}

void test_filesystem_remove() {
    InMemoryFilesystem fs;
    fs.create("temp.log");
    bool removed = fs.remove("temp.log");
    assert(removed);
    // Try removing again (should fail)
    bool removed2 = fs.remove("temp.log");
    assert(!removed2);
    std::cout << "[TEST PASS] Filesystem remove\n";
}

int main() {
    std::cout << "=== Adapter Filesystem Tests ===\n";
    test_filesystem_create();
    test_filesystem_open_close();
    test_filesystem_remove();
    std::cout << "All filesystem adapter tests passed!\n";
    return 0;
}
