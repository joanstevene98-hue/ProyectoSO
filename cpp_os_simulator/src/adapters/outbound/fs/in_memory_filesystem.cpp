#include "in_memory_filesystem.h"
#include <iostream>

using namespace adapters::outbound::fs;
using namespace domain::entities::fs;
using namespace domain::ports::fs;

bool InMemoryFilesystem::create(const std::string &name) {
    if (files.find(name) != files.end()) return false;
    files[name] = FCB(name, 0, -1);
    std::cout << "[FS] Created file: " << name << "\n";
    return true;
}

OpenResult InMemoryFilesystem::open(const std::string &name) {
    auto it = files.find(name);
    if (it == files.end()) return std::nullopt;
    int handle = next_handle++;
    open_handles[handle] = name;
    it->second.open = true;
    std::cout << "[FS] Opened file: " << name << " handle=" << handle << "\n";
    return handle;
}

bool InMemoryFilesystem::close(int handle) {
    auto it = open_handles.find(handle);
    if (it == open_handles.end()) return false;
    auto fit = files.find(it->second);
    if (fit != files.end()) fit->second.open = false;
    std::cout << "[FS] Closed handle=" << handle << " (" << it->second << ")\n";
    open_handles.erase(it);
    return true;
}

bool InMemoryFilesystem::remove(const std::string &name) {
    auto it = files.find(name);
    if (it == files.end()) return false;
    if (it->second.open) return false; // cannot remove open file
    files.erase(it);
    std::cout << "[FS] Removed file: " << name << "\n";
    return true;
}

void InMemoryFilesystem::ls() {
    std::cout << "[FS] Files:\n";
    for (auto &p : files) {
        std::cout << "  - " << p.first << " (size=" << p.second.size << ")" << (p.second.open?" [open]":"") << "\n";
    }
}
