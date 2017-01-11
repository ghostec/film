#include "renderer.h"
#include "math/point3.h"
#include "math/random.h"
#include <thread>

namespace film {

namespace scene {

renderer::renderer() : film_ptr(nullptr), scenegraph_ptr(nullptr), current_row(0), n_threads(1) {}

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

void renderer::SetNThreads(size_t _n_threads) {
  n_threads = _n_threads;
}

void renderer::Render() {
  for(auto i = 0; i < n_threads; i++) {
    std::thread t(&renderer::work, this);
    t.join();
  }
}

void renderer::work() {
  while(true) {
    auto job = jobScheduler();
    if(job.status == render_job_status::done) return;

    math::rgb color;
    math::ray ray;
    double zw = 100.0;
    double x, y;

    ray.direction = math::vec3(0, 0, -1);

    auto vres = film_ptr->GetVres();
    auto hres = film_ptr->GetHres();
    auto s = film_ptr->GetS();
    auto r = job.row;
    auto scene = scenegraph_ptr->GetObjects();
    auto samples = 4;
    float invsamples = 1.0 / (samples * samples);

    for(auto c = 0; c < hres; c++) {
      color = {0.0, 0.0, 0.0};

      for(auto sr = 0; sr < samples; sr++) {
        for(auto sc = 0; sc < samples; sc++) {
          x = s * (c - 0.5 * hres + (sc + math::rand_float()) / samples);
          y = s * (r - 0.5 * vres + (sr + math::rand_float()) / samples);
          ray.origin = math::point3(x, y, zw);
          color += tracer_ptr->TraceRay(ray, scene);
        }
      }

      (*film_ptr)[r * hres + c] = color * invsamples;
    }
  }
}

render_job renderer::jobScheduler() {
  auto vres = film_ptr->GetVres();
  if(current_row >= vres) return { render_job_status::done };
  return { render_job_status::work, current_row++ };
}

}

}
