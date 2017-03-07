project(FilmServer)

find_package(Qt5Network)

add_subdirectory(renderer)
add_subdirectory(network)
add_subdirectory(math)
add_subdirectory(camera)
add_subdirectory(hitable)

set(LIBRARIES Math Camera Hitable Renderer Network)

set(SOURCE_FILES film_server.cpp)
add_executable(FilmServer ${SOURCE_FILES})

target_link_libraries(FilmServer ${LIBRARIES} Qt5::Network)
