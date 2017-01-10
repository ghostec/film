#ifndef RENDERERH
#define RENDERERH

#include "film.h"
#include "scenegraph.h"
#include "tracers/tracer.h"

namespace film {

namespace scene {

class renderer {
public:
  renderer();
  ~renderer();
  void Render();
  void SetFilm(film* _film_ptr);
  void SetSceneGraph(scenegraph* _scenegraph_ptr);
  void SetTracer(tracers::tracer* _tracer_ptr);
  film* GetFilm();
private:
  film* film_ptr;
  scenegraph* scenegraph_ptr;
  tracers::tracer* tracer_ptr;
};

}

}

#endif
