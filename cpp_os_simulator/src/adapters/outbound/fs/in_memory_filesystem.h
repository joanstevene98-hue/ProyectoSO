#ifndef ADAPTERS_OUTBOUND_FS_IN_MEMORY_FILESYSTEM_H
#define ADAPTERS_OUTBOUND_FS_IN_MEMORY_FILESYSTEM_H

#include "../../../domain/ports/fs/filesystem_port.h"
#include "../../../domain/entities/fs/fcb.h"
#include <map>
#include <vector>
#include <string>

namespace adapters::outbound::fs {

class InMemoryFilesystem : public domain::ports::fs::FilesystemPort {
    std::map<std::string, domain::entities::fs::FCB> files;
    std::map<int, std::string> open_handles; // handle -> filename
    int next_handle{1};
public:
    bool create(const std::string &name) override;
    domain::ports::fs::OpenResult open(const std::string &name) override;
    bool close(int handle) override;
    bool remove(const std::string &name) override;
    void ls() override;
};

} // namespace adapters::outbound::fs

#endif // ADAPTERS_OUTBOUND_FS_IN_MEMORY_FILESYSTEM_H
