#ifndef RENDERERH
#define RENDERERH

#include <atomic>

#include "film.h"
#include "scenegraph.h"
#include "tracers/tracer.h"

namespace film {

namespace scene {

enum class render_job_status {
  work, done
};

struct render_job {
  render_job_status status;
  size_t row;
};

class renderer {
public:
  renderer();
  ~renderer();
  void Render();
  void SetFilm(film* _film_ptr);
  void SetSceneGraph(scenegraph* _scenegraph_ptr);
  void SetTracer(tracers::tracer* _tracer_ptr);
  void SetNThreads(size_t _n_threads);
  film* GetFilm();
private:
  film* film_ptr;
  scenegraph* scenegraph_ptr;
  tracers::tracer* tracer_ptr;
  std::atomic_size_t current_row;
  size_t n_threads;

  void work();
  render_job jobScheduler();
};

}

}

#endif
