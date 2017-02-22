cmake_minimum_required(VERSION 3.6)
project(film)

include_directories(./)

add_subdirectory(server)

set(LIBRARIES Server)

add_executable(film main.cpp film.cpp)

target_link_libraries(film ${LIBRARIES})

set_property(TARGET film PROPERTY CXX_STANDARD 14)
