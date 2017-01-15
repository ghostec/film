#include "math/random.h"
#include <iostream>
#include "pinhole.h"

namespace film {

namespace cameras {

pinhole::pinhole() : plane_distance(100), zoom(1), camera() {}

pinhole::~pinhole() {}

void pinhole::renderScene(hitable::hitable* scene_ptr, tracers::tracer* tracer_ptr, scene::film* film_ptr) {
  while(true) {
    auto job = jobScheduler(film_ptr);
    if(job.status == render_job_status::done) return;

    math::rgb color;
    math::ray ray;
    double x, y;
    auto recursion_depth = 0;

    ray.origin = eye;

    auto vres = film_ptr->GetVres();
    auto hres = film_ptr->GetHres();
    auto s = film_ptr->GetS() / zoom;
    auto r = job.row;
    auto samples = 4;
    float invsamples = 1.0 / (samples * samples);

    for(auto c = 0; c < hres; c++) {
      color = {0.0, 0.0, 0.0};

      for(auto sr = 0; sr < samples; sr++) {
        for(auto sc = 0; sc < samples; sc++) {
          x = s * (c - 0.5 * hres + (sc + math::rand_float()) / samples);
          y = s * (r - 0.5 * vres + (sr + math::rand_float()) / samples);
          ray.direction = RayDirection(x, y);
          color += tracer_ptr->TraceRay(ray, scene_ptr);
        }
      }

      (*film_ptr)[r * hres + c] = color * invsamples;
    }
  } 
}

math::vec3 pinhole::RayDirection(const double x, const double y) {
  return (x * u + y * v - plane_distance * w).Hat();
}

void pinhole::SetPlaneDistance(const float _plane_distance) {
  plane_distance = _plane_distance;
}

void pinhole::SetZoom(const float _zoom) {
  zoom = _zoom;
}

}

}
