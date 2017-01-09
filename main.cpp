#include <iostream>
#include "scene/film.h"
#include "scene/scenegraph.h"
#include "scene/renderer.h"

int main() {
  film::scene::renderer renderer;
  film::scene::film film(400, 300);
  film::scene::scenegraph scenegraph;
  
  scenegraph.build();

  renderer.SetFilm(film);
  renderer.SetSceneGraph(scenegraph);

  return 0;
}
