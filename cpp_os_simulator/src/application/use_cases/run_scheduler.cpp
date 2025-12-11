#include "run_scheduler.h"
#include "../../domain/entities/pcb.h"
#include <vector>

using namespace domain::entities;

namespace application::use_cases {

void run_example(domain::ports::SchedulerPort &scheduler) {
    std::vector<PCB> processes = {
        PCB(1, "Init", 5),
        PCB(2, "WorkerA", 3),
        PCB(3, "WorkerB", 8),
        PCB(4, "IO-bound", 6)
    };

    for (auto &p : processes) {
        scheduler.addProcess(p);
    }
    scheduler.run();
}

} // namespace application::use_cases
