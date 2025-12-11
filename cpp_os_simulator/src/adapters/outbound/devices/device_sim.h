#ifndef ADAPTERS_OUTBOUND_DEVICES_DEVICE_SIM_H
#define ADAPTERS_OUTBOUND_DEVICES_DEVICE_SIM_H

#include "../../../domain/ports/io/io_port.h"
#include <queue>
#include <string>
#include <map>

namespace adapters::outbound::devices {

struct IORequest { int pid; std::string data; };

class DeviceSimulator : public domain::ports::io::IOPort {
    std::map<std::string, std::queue<IORequest>> queues;
public:
    void register_device(const std::string &name) override;
    void request_io(const std::string &device, int pid, const std::string &data) override;
    void poll() override; // process one item from each queue
};

} // namespace adapters::outbound::devices

#endif // ADAPTERS_OUTBOUND_DEVICES_DEVICE_SIM_H
