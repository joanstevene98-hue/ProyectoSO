#ifndef DOMAIN_PORTS_SCHEDULER_PORT_H
#define DOMAIN_PORTS_SCHEDULER_PORT_H

#include "../entities/pcb.h"

namespace domain::ports {

using domain::entities::PCB;

class SchedulerPort {
public:
    virtual ~SchedulerPort() = default;
    virtual void addProcess(const PCB &p) = 0;
    virtual void run() = 0;
};

} // namespace domain::ports

#endif // DOMAIN_PORTS_SCHEDULER_PORT_H
