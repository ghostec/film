project(Server)

set(ServerFiles
  server.cpp
)

add_library(Server ${ServerFiles})

include(${CMAKE_CURRENT_SOURCE_DIR}/FindLibUV.cmake)
target_link_libraries(Server uv)

set_property(TARGET Server PROPERTY CXX_STANDARD 14)
