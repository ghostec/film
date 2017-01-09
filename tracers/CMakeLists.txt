project(Tracers)

set(TracersFiles
  tracer.cpp tracer.h
)

add_library(Tracers ${TracersFiles})

set_property(TARGET Tracers PROPERTY CXX_STANDARD 14)
