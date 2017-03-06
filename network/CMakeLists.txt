project(Network)

find_package(Qt5Network)

set(SOURCE_FILES
  client.cpp worker.cpp server.cpp film_job_t.cpp film_job_coordinator.cpp
  frame_coordinator.cpp coordinator.cpp)

add_library(Network ${SOURCE_FILES})

target_link_libraries(Network Qt5::Network)
