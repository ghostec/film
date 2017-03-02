cmake_minimum_required(VERSION 3.6)
project(film)

set(CMAKE_CXX_STANDARD 14)

include(FindGraphicsMagick.cmake)
include_directories(./ ./deps ${GraphicsMagick++_INCLUDE_DIRS})

add_subdirectory(deps/film-network)
add_subdirectory(math)
add_subdirectory(hitable)
add_subdirectory(renderer)
add_subdirectory(network)

set(LIBRARIES Film_Network Math Hitable Renderer Network)

add_executable(film main.cpp film.cpp)
target_link_libraries(film ${LIBRARIES} ${GraphicsMagick++_LIBRARIES})
