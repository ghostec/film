project(FilmWorker)

find_package(Qt5Network)

add_subdirectory(network)

set(LIBRARIES Network)

set(SOURCE_FILES film_worker.cpp)
add_executable(FilmWorker ${SOURCE_FILES})

target_link_libraries(FilmWorker ${LIBRARIES} Qt5::Network)
