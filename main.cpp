#include <iostream>
#include "scene/film.h"
#include "scene/scenegraph.h"
#include "scene/renderer.h"
#include "tracers/tracer.h"

int main() {
  film::scene::renderer renderer;
  film::scene::film film(400, 300);
  film::scene::scenegraph* scenegraph = new film::scene::scenegraph();
  film::tracers::tracer* tracer = new film::tracers::tracer(scenegraph);
  
  scenegraph->build();

  renderer.SetFilm(film);
  renderer.SetSceneGraph(scenegraph);
  renderer.SetTracer(tracer);

  renderer.render();

  return 0;
}
