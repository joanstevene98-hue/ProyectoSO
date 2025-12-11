#include "device_sim.h"
#include <iostream>

using namespace adapters::outbound::devices;

void DeviceSimulator::register_device(const std::string &name) {
    if (queues.find(name) == queues.end()) {
        queues[name] = std::queue<IORequest>();
        std::cout << "[DeviceSim] Registered device: " << name << "\n";
    }
}

void DeviceSimulator::request_io(const std::string &device, int pid, const std::string &data) {
    auto it = queues.find(device);
    if (it == queues.end()) {
        std::cout << "[DeviceSim] Unknown device: " << device << "\n";
        return;
    }
    it->second.push({pid, data});
    std::cout << "[DeviceSim] IO requested on " << device << " by pid=" << pid << " data='" << data << "'\n";
}

void DeviceSimulator::poll() {
    for (auto &p : queues) {
        auto &q = p.second;
        if (!q.empty()) {
            IORequest r = q.front(); q.pop();
            std::cout << "[DeviceSim] Device " << p.first << " processed IO for pid=" << r.pid << " data='" << r.data << "'\n";
            // simulate notification: just print
            std::cout << "[DeviceSim] Notifying pid=" << r.pid << " of completion\n";
        }
    }
}
