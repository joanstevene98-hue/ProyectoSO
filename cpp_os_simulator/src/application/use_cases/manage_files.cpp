#include "manage_files.h"
#include <iostream>

namespace application::use_cases {

void run_files_demo(domain::ports::fs::FilesystemPort &fs, domain::ports::io::IOPort &io) {
    std::cout << "=== Demo: Sistema de Archivos y E/S ===\n";
    fs.create("file1.txt");
    fs.create("file2.log");
    fs.ls();

    auto h = fs.open("file1.txt");
    if (h) {
        std::cout << "Opened handle=" << *h << "\n";
    }

    io.register_device("disk0");
    io.request_io("disk0", 1, "write file1.txt");
    io.poll();

    if (h) fs.close(*h);
    fs.ls();
    fs.remove("file2.log");
    fs.ls();

    std::cout << "=== Demo archivos/E/S finalizada ===\n";
}

} // namespace application::use_cases
