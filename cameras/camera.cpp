#include <thread>
#include "camera.h"
#include <iostream>

namespace film {

namespace cameras {

camera::camera() : up(math::vec3{0,1,0}), exposure_time(1), lookat({0,0,-1}) {}

camera::~camera() {}

void camera::SetEye(const math::point3 _eye) {
  eye = _eye;
}

void camera::SetLookAt(const math::point3 _lookat) {
  lookat = _lookat;
}

void camera::SetUp(const math::vec3 _up) {
  up = _up;
}

void camera::SetNThreads(const size_t _n_threads) {
  n_threads = _n_threads;
}

void camera::ComputeUvw() {
  w = eye - lookat;
  w.Normalize();
  u = up ^ w;
  u.Normalize();
  v = w ^ u;
}

void camera::RenderScene(hitable::hitable* scene_ptr, tracers::tracer* tracer_ptr, scene::film* film_ptr) {
  for(auto i = 0; i < n_threads; i++) {
    std::thread t(&camera::renderScene, this, scene_ptr, tracer_ptr, film_ptr);
    t.join();
  }
}

render_job camera::jobScheduler(scene::film* film_ptr) {
  auto vres = film_ptr->GetVres();
  if(current_row >= vres) return { render_job_status::done };
  return { render_job_status::work, current_row++ };
}

}

}
