project(FilmServer)

find_package(Qt5Network)

add_subdirectory(network)

set(LIBRARIES Network)

set(SOURCE_FILES film_server.cpp)
add_executable(FilmServer ${SOURCE_FILES})

target_link_libraries(FilmServer ${LIBRARIES} Qt5::Network)
