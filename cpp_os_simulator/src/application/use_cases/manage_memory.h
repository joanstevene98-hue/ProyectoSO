#ifndef APPLICATION_USE_CASES_MANAGE_MEMORY_H
#define APPLICATION_USE_CASES_MANAGE_MEMORY_H

#include "../../domain/ports/memory/memory_port.h"

namespace application::use_cases {

void run_memory_demo(domain::ports::memory::MemoryManagerPort &mm);

} // namespace application::use_cases

#endif // APPLICATION_USE_CASES_MANAGE_MEMORY_H
