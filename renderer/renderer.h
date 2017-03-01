#ifndef RENDERER_RENDERERH
#define RENDERER_RENDERERH

#include "film.h"

namespace film { namespace renderer {

class Renderer {
public:
  Renderer();
  ~Renderer();
  void render(size_t first_row, size_t last_row, size_t film_width);
  Film* get_film();
private:
  Film* film;

  void set_film(size_t width, size_t height);
};

} }

#endif
