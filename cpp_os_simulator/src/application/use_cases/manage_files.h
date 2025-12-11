#ifndef APPLICATION_USE_CASES_MANAGE_FILES_H
#define APPLICATION_USE_CASES_MANAGE_FILES_H

#include "../../domain/ports/fs/filesystem_port.h"
#include "../../domain/ports/io/io_port.h"

namespace application::use_cases {

void run_files_demo(domain::ports::fs::FilesystemPort &fs, domain::ports::io::IOPort &io);

} // namespace application::use_cases

#endif // APPLICATION_USE_CASES_MANAGE_FILES_H
