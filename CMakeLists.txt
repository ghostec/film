cmake_minimum_required(VERSION 3.6)
project(film)

set(CMAKE_CXX_STANDARD 14)

include(FindGraphicsMagick.cmake)
include_directories(./ ./deps ${GraphicsMagick++_INCLUDE_DIRS})

add_subdirectory(deps/film-network)
add_subdirectory(renderer)

set(LIBRARIES Film_Network Renderer)

add_executable(film main.cpp film.cpp)
target_link_libraries(film ${LIBRARIES} ${GraphicsMagick++_LIBRARIES})
