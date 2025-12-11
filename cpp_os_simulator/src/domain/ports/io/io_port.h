#ifndef DOMAIN_PORTS_IO_IO_PORT_H
#define DOMAIN_PORTS_IO_IO_PORT_H

#include <string>

namespace domain::ports::io {

class IOPort {
public:
    virtual ~IOPort() = default;
    virtual void register_device(const std::string &name) = 0;
    virtual void request_io(const std::string &device, int pid, const std::string &data) = 0;
    virtual void poll() = 0; // simulate processing of requests
};

} // namespace domain::ports::io

#endif // DOMAIN_PORTS_IO_IO_PORT_H
