#include <iostream>
#include "../../../application/use_cases/manage_files.h"
#include "../../outbound/fs/in_memory_filesystem.h"
#include "../../outbound/devices/device_sim.h"

int main_files_demo() {
    std::cout << "=== Runner CLI: Archivos y E/S ===\n";
    adapters::outbound::fs::InMemoryFilesystem fs;
    adapters::outbound::devices::DeviceSimulator dev;
    application::use_cases::run_files_demo(fs, dev);
    std::cout << "\nRunner finalizado.\n";
    return 0;
}
