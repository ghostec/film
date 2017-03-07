project(Network)

find_package(Qt5Network)

set(SOURCE_FILES
  client.cpp worker.cpp film_job_t.cpp film_job_coordinator.cpp
  frame_coordinator.cpp coordinator.cpp qdatastream.cpp)

if(${target} STREQUAL "FilmServer")
  set(SOURCE_FILES ${SOURCE_FILES} server.cpp)
endif()

add_library(Network ${SOURCE_FILES})

target_link_libraries(Network Qt5::Network)
