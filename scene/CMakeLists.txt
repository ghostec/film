project(Scene)

set(SceneFiles
  film.cpp film.h
)

add_library(Scene ${SceneFiles})

set_property(TARGET Scene PROPERTY CXX_STANDARD 14)

