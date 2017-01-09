project(Hitable)

set(HitableFiles
  hit_record.h
  hitable.cpp hitable.h
)

add_library(Hitable ${HitableFiles})

set_property(TARGET Hitable PROPERTY CXX_STANDARD 14)
