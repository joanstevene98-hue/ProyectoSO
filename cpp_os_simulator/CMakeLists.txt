cmake_minimum_required(VERSION 3.15)
project(OSSimulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# SOURCE FILES (shared across all targets)

set(DOMAIN_SOURCES
    src/domain/entities/pcb.cpp
)

set(ADAPTER_SOURCES
    src/adapters/outbound/schedulers/fifo_scheduler.cpp
    src/adapters/outbound/schedulers/rr_scheduler.cpp
    src/adapters/outbound/memory/first_fit_memory.cpp
    src/adapters/outbound/fs/in_memory_filesystem.cpp
    src/adapters/outbound/devices/device_sim.cpp
)

set(APPLICATION_SOURCES
    src/application/use_cases/run_scheduler.cpp
    src/application/use_cases/manage_memory.cpp
    src/application/use_cases/manage_files.cpp
    src/application/use_cases/integration_scenario.cpp
)

set(ALL_SOURCES ${DOMAIN_SOURCES} ${ADAPTER_SOURCES} ${APPLICATION_SOURCES})

# ============================================================================
# CLI RUNNERS (Adapters Inbound)
# ============================================================================

add_executable(os_simulator_kernel
    src/adapters/inbound/cli/kernel_runner.cpp
    ${ALL_SOURCES}
)
target_include_directories(os_simulator_kernel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(os_simulator_scheduler
    src/adapters/inbound/cli/main.cpp
    ${ADAPTER_SOURCES} ${APPLICATION_SOURCES} ${DOMAIN_SOURCES}
)
target_include_directories(os_simulator_scheduler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(os_simulator_memory
    src/adapters/inbound/cli/memory_cli.cpp
    src/adapters/outbound/memory/first_fit_memory.cpp
    src/application/use_cases/manage_memory.cpp
)
target_include_directories(os_simulator_memory PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(os_simulator_files
    src/adapters/inbound/cli/files_cli.cpp
    src/adapters/outbound/fs/in_memory_filesystem.cpp
    src/adapters/outbound/devices/device_sim.cpp
    src/application/use_cases/manage_files.cpp
)
target_include_directories(os_simulator_files PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# UNIT TESTS (Domain, Adapters, Application)


enable_testing()

# Test: Domain entities (PCB)
add_executable(test_pcb
    tests/domain/test_pcb.cpp
    ${DOMAIN_SOURCES}
)
target_include_directories(test_pcb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME PCB_Tests COMMAND test_pcb)

# Test: Adapter - Memory
add_executable(test_memory
    tests/adapters/test_first_fit_memory.cpp
    src/adapters/outbound/memory/first_fit_memory.cpp
)
target_include_directories(test_memory PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME Memory_Tests COMMAND test_memory)

# Test: Adapter - Filesystem
add_executable(test_filesystem
    tests/adapters/test_in_memory_filesystem.cpp
    src/adapters/outbound/fs/in_memory_filesystem.cpp
)
target_include_directories(test_filesystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME Filesystem_Tests COMMAND test_filesystem)

# Test: Adapter - Schedulers
add_executable(test_schedulers
    tests/adapters/test_schedulers.cpp
    ${ADAPTER_SOURCES} ${APPLICATION_SOURCES} ${DOMAIN_SOURCES}
)
target_include_directories(test_schedulers PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME Scheduler_Tests COMMAND test_schedulers)

# Test: Application - Integration scenarios
add_executable(test_integration
    tests/application/test_integration_scenarios.cpp
    ${ALL_SOURCES}
)
target_include_directories(test_integration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME Integration_Tests COMMAND test_integration)

