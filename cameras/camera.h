#ifndef CAMERAH
#define CAMERAH

#include <atomic>

#include "math/point3.h"
#include "math/vec3.h"
#include "hitable/hitable.h"
#include "scene/film.h"
#include "tracers/tracer.h"

namespace film {

namespace cameras {

enum class render_job_status {
  work, done
};

struct render_job {
  render_job_status status;
  size_t row;
};

class camera {
public:
  camera();
  ~camera();
  void ComputeUvw();
  void RenderScene(hitable::hitable* scene_ptr, tracers::tracer* tracer_ptr, scene::film* film_ptr);
  void SetEye(const math::point3 _eye);
  void SetLookAt(const math::point3 _lookat);
  void SetUp(const math::vec3 _up);
  void SetNThreads(const size_t _n_threads);
protected:
  math::point3 eye, lookat;
  math::vec3 up, u, v, w;
  float exposure_time;
  // threading
  std::atomic_size_t current_row;
  size_t n_threads;
  render_job jobScheduler(scene::film* film_ptr);
private:
  virtual void renderScene(hitable::hitable* scene_ptr, tracers::tracer* tracer_ptr, scene::film* film_ptr) = 0;
};

}

}

#endif
