#ifndef RENDERER_SCENEH
#define RENDERER_SCENEH

#include "camera/camera.h"
#include "film.h"
#include "hitable/hitable.h"

namespace film {
class Scene {
 public:
  Scene();
  ~Scene();
  Camera* getCamera() const;
  Hitable* getWorld() const;
  void setCamera(Camera* cameraPtr);
  void setWorld(Hitable* worldPtr);
  void render(Film* filmPtr, size_t firstRow, size_t lastRow, size_t width,
              size_t height);

 private:
  Camera* cameraPtr;
  Hitable* worldPtr;
};
}

#endif
