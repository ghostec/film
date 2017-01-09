cmake_minimum_required(VERSION 3.6)
project(film)

include_directories(./)

add_subdirectory(math)
add_subdirectory(hitable)
add_subdirectory(scene)
add_subdirectory(tracers)

set(LIBRARIES Math Hitable Scene Tracers)

add_executable(film main.cpp)

target_link_libraries(film ${LIBRARIES})

set_property(TARGET film PROPERTY CXX_STANDARD 14)
