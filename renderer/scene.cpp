#include "scene.h"

namespace film {
Scene::Scene() {}
Scene::~Scene() {}

void Scene::setCamera(Camera* cameraPtr) { this->cameraPtr = cameraPtr; }

void Scene::setWorld(Hitable* worldPtr) { this->worldPtr = worldPtr; }

void Scene::render(Film* filmPtr, size_t firstRow, size_t lastRow, size_t width,
                   size_t height) {
  return;
}
}
