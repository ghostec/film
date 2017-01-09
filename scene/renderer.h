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
  void render();
  void SetFilm(const film __film);
  void SetSceneGraph(scenegraph* __scenegraph);
  void SetTracer(tracers::tracer* _tracer);
private:
  film _film;
  scenegraph* _scenegraph;
  tracers::tracer* tracer;
};

}

}

#endif
