cmake_minimum_required(VERSION 3.6)
project(film)

include(FindGraphicsMagick.cmake)
include_directories(./ ${GraphicsMagick++_INCLUDE_DIRS})

add_subdirectory(server)

set(LIBRARIES Server)

add_executable(film main.cpp film.cpp)
target_link_libraries(film ${LIBRARIES} ${GraphicsMagick++_LIBRARIES})

set_property(TARGET film PROPERTY CXX_STANDARD 14)
