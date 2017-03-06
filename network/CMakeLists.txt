project(Network)

find_package(Qt5Network)

set(SOURCE_FILES client.cpp worker.cpp server.cpp)
add_library(Network ${SOURCE_FILES})

target_link_libraries(Network Qt5::Network)
