#include "renderer.h"

namespace film { namespace renderer {

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::render() {
  return;
}

void Renderer::set_film(Film* film) {
  this->film = film;
}

} }
