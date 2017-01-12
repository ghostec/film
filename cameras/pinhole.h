#ifndef PINHOLEH
#define PINHOLEH

#include "camera.h"

namespace film {

namespace cameras {

class pinhole : public camera {
public:
  pinhole();
  ~pinhole();
  math::vec3 RayDirection(const double x, const double y);
  float d, zoom;
private:
  virtual void renderScene(hitable::hitable* scene_ptr, tracers::tracer* tracer_ptr, scene::film* film_ptr);
};

}

}

#endif
