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
  void SetFilm(const film __film);
  void SetSceneGraph(scenegraph* __scenegraph);
  void SetTracer(tracers::tracer* _tracer);
  void SavePPM() const;
private:
  film _film;
  scenegraph* _scenegraph;
  tracers::tracer* tracer;
};

}

}

#endif
