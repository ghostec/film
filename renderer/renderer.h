#ifndef RENDERER_RENDERERH
#define RENDERER_RENDERERH

#include "film.h"

namespace film { namespace renderer {

class Renderer {
public:
  Renderer();
  ~Renderer();
  void render();
  void set_film(Film* film);
private:
  Film* film;
};

} }

#endif
