project(Cameras)

set(CamerasFiles
  camera.cpp pinhole.cpp
)

add_library(Cameras ${CamerasFiles})

set_property(TARGET Cameras PROPERTY CXX_STANDARD 14)

