#include "renderer.h"
#include <iostream>

namespace film { namespace renderer {

Renderer::Renderer() : film(nullptr) {}
Renderer::~Renderer() {}

void Renderer::render(size_t first_row, size_t last_row, size_t film_width) {
  set_film(film_width, last_row - first_row + 1);
  for(int i = 0; i < (last_row - first_row + 1) * film_width; i++)
    (*film)[i] = math::rgb(1.0, 1.0, 1.0);
}

void Renderer::set_film(size_t width, size_t height) {
  if(film) delete film;
  film = new Film(width, height);
}

Film* Renderer::get_film() {
  return film;
}

} }
