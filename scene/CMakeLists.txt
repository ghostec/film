project(Scene)

set(SceneFiles
  film.cpp film.h
  scenegraph.cpp scenegraph.h
  renderer.cpp renderer.h
)

add_library(Scene ${SceneFiles})

set_property(TARGET Scene PROPERTY CXX_STANDARD 14)
