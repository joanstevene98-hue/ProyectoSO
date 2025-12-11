#ifndef ADAPTERS_OUTBOUND_FIFO_SCHEDULER_H
#define ADAPTERS_OUTBOUND_FIFO_SCHEDULER_H

#include "../../../domain/ports/scheduler_port.h"
#include "../../../domain/entities/pcb.h"
#include <queue>

namespace adapters::outbound::schedulers {

class FIFO_Scheduler : public domain::ports::SchedulerPort {
    std::queue<domain::entities::PCB> q;
public:
    void addProcess(const domain::entities::PCB &p) override;
    void run() override;
};

} // namespace adapters::outbound::schedulers

#endif // ADAPTERS_OUTBOUND_FIFO_SCHEDULER_H
