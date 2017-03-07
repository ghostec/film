project(FilmWorker)

find_package(Qt5Network)

add_subdirectory(renderer)
add_subdirectory(network)
add_subdirectory(math)
add_subdirectory(camera)
add_subdirectory(hitable)

set(LIBRARIES Math Camera Hitable Renderer Network)

set(SOURCE_FILES film_worker.cpp)
add_executable(FilmWorker ${SOURCE_FILES})

target_link_libraries(FilmWorker ${LIBRARIES} Qt5::Network)
