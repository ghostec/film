#include "renderer.h"
#include "math/point3.h"
#include <iostream>

namespace film {

namespace scene {

renderer::renderer() : film_ptr(nullptr), scenegraph_ptr(nullptr) {}

renderer::~renderer() {}

void renderer::SetFilm(film* _film_ptr) {
  film_ptr = _film_ptr;
}

void renderer::SetSceneGraph(scenegraph* _scenegraph_ptr) {
  scenegraph_ptr = _scenegraph_ptr;
}

void renderer::SetTracer(tracers::tracer* _tracer_ptr) {
  tracer_ptr = _tracer_ptr;
}

film* renderer::GetFilm() {
  return film_ptr;
}

void renderer::Render() {
  math::rgb color;
  math::ray ray;
  double zw = 100.0;
  double x, y;

  ray.direction = math::vec3(0, 0, -1);

  auto vres = film_ptr->GetVres();
  auto hres = film_ptr->GetHres();
  auto s = film_ptr->GetS();

  for(auto r = 0; r < vres; r++) {
    for(auto c = 0; c < hres; c++) {
      x = s * (c - 0.5 * (hres - 1.0));
      y = s * (r - 0.5 * (vres - 1.0));
      ray.origin = math::point3(x, y, zw);
      color = tracer_ptr->TraceRay(ray);
      (*film_ptr)[r * hres + c] = color;
    }
  }
}

}

}
