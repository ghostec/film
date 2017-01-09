cmake_minimum_required(VERSION 3.6)
project(film)

include_directories(./)

add_subdirectory(math)
add_subdirectory(hitable)
add_subdirectory(scene)

set(LIBRARIES Math Hitable Scene)

add_executable(film main.cpp)

target_link_libraries(film ${LIBRARIES})

set_property(TARGET film PROPERTY CXX_STANDARD 14)
