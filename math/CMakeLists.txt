project(Math)

set(MathFiles
  vec3.cpp vec3.h
  point3.cpp point3.h
  normal.cpp normal.h
  rgb.cpp rgb.h
  ray.cpp ray.h
)

add_library(Math ${MathFiles})

set_property(TARGET Math PROPERTY CXX_STANDARD 14)
