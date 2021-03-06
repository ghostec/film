#include "scene.h"

namespace film {
Scene::Scene() {}
Scene::~Scene() {}

Camera* Scene::getCamera() const { return cameraPtr; }

Hitable* Scene::getWorld() const { return worldPtr; }

void Scene::setCamera(Camera* cameraPtr) { this->cameraPtr = cameraPtr; }

void Scene::setWorld(Hitable* worldPtr) { this->worldPtr = worldPtr; }

void Scene::render(Film* filmPtr, size_t firstRow, size_t lastRow, size_t width,
                   size_t height) {
  cameraPtr->render(filmPtr, worldPtr, firstRow, lastRow, width, height);
}
}
