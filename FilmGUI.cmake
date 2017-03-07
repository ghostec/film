project(FilmGUI)

find_package(Qt5Widgets)
find_package(Qt5Network)

include_directories(./)

add_subdirectory(network)
add_subdirectory(gui)

set(LIBRARIES Network GUI)

set(SOURCE_FILES film_gui.cpp)
add_executable(FilmGUI ${SOURCE_FILES})

target_link_libraries(FilmGUI ${LIBRARIES} Qt5::Network Qt5::Widgets)
