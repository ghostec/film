#include "renderer.h"

namespace film {

namespace scene {

renderer::renderer() : _film(film(400, 300)), _scenegraph(nullptr) {}

renderer::~renderer() {}

void renderer::SetFilm(const film __film) {
  _film = __film;
}

void renderer::SetSceneGraph(scenegraph* __scenegraph) {
  _scenegraph = __scenegraph;
}

void renderer::render() {

}

}

}
