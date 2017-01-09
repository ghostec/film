#include <iostream>
#include "scene/film.h"
#include "scene/scenegraph.h"
#include "scene/renderer.h"
#include "tracers/singlesphere.h"

int main() {
  film::scene::renderer renderer;
  film::scene::film* film_ptr = new film::scene::film(400, 300);
  film::scene::scenegraph* scenegraph_ptr = new film::scene::scenegraph();
  film::tracers::tracer* tracer_ptr = new film::tracers::singlesphere(scenegraph_ptr);
  
  scenegraph_ptr->build();

  renderer.SetFilm(film_ptr);
  renderer.SetSceneGraph(scenegraph_ptr);
  renderer.SetTracer(tracer_ptr);

  renderer.Render();
  film_ptr->SavePPM();

  return 0;
}
