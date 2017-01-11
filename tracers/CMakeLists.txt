project(Tracers)

set(TracersFiles
  tracer.cpp tracer.h
  multiple_objects.cpp multiple_objects.h
)

add_library(Tracers ${TracersFiles})

set_property(TARGET Tracers PROPERTY CXX_STANDARD 14)
