#include "renderer.h"
#include "math/point3.h"

namespace film {

namespace scene {

renderer::renderer() : _film(film(400, 300)), _scenegraph(nullptr) {}

renderer::~renderer() {}

void renderer::SetFilm(const film __film) {
  _film = __film;
}

void renderer::SetSceneGraph(scenegraph* __scenegraph) {
  _scenegraph = __scenegraph;
}

void renderer::SetTracer(tracers::tracer* _tracer) {
  tracer = _tracer;
}

void renderer::render() {
  math::rgb color;
  math::ray ray;
  double zw = 100.0;
  double x, y;

  ray.direction = math::vec3(0, 0, -1);

  auto vres = _film.GetVres();
  auto hres = _film.GetHres();
  auto s = _film.GetS();

  for(auto r = 0; r < vres; r++) {
    for(auto c = 0; c < hres; c++) {
      x = s * (c - 0.5 * (hres - 1.0));
      y = s * (r - 0.5 * (vres - 1.0));
      ray.origin = math::point3(x, y, zw);
      color = tracer->TraceRay(ray);
      _film[r * hres + c] = color;
    }
  }
}

}

}
