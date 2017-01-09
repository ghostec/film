cmake_minimum_required(VERSION 3.6)
project(film)

add_subdirectory(math)
add_subdirectory(hitable)

set(LIBRARIES Math Hitable)

add_executable(film main.cpp)

target_link_libraries(film ${LIBRARIES})

set_property(TARGET film PROPERTY CXX_STANDARD 14)
