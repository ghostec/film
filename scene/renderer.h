#ifndef RENDERERH
#define RENDERERH

#include "film.h"
#include "scenegraph.h"

namespace film {

namespace scene {

class renderer {
public:
  renderer();
  ~renderer();
  void render();
  void SetFilm(const film __film);
  void SetSceneGraph(const scenegraph __scenegraph);
private:
  film _film;
  scenegraph _scenegraph;
};

}

}

#endif
