#include "renderer.h"
#include "math/point3.h"
#include "math/random.h"
#include <thread>

namespace film {

namespace scene {

renderer::renderer() : film_ptr(nullptr), scenegraph_ptr(nullptr), n_threads(1) {}

renderer::~renderer() {}

void renderer::SetFilm(film* _film_ptr) {
  film_ptr = _film_ptr;
}

void renderer::SetSceneGraph(scenegraph* _scenegraph_ptr) {
  scenegraph_ptr = _scenegraph_ptr;
}

void renderer::SetTracer(tracers::tracer* _tracer_ptr) {
  tracer_ptr = _tracer_ptr;
}

void renderer::SetCamera(cameras::camera* _camera_ptr) {
  camera_ptr = _camera_ptr;
}

film* renderer::GetFilm() {
  return film_ptr;
}

void renderer::Render() {
  camera_ptr->RenderScene(scenegraph_ptr->GetObjects(), tracer_ptr, film_ptr);
}

}

}
