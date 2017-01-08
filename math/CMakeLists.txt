project(Math)

set(MathFiles
  vec3.cpp vec3.h
)

add_library(Math ${MathFiles})

set_property(TARGET Math PROPERTY CXX_STANDARD 14)
