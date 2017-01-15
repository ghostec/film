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
  void SetPlaneDistance(const float _plane_distance);
  void SetZoom(const float _zoom);
private:
  float plane_distance, zoom;
  virtual void renderScene(hitable::hitable* scene_ptr, tracers::tracer* tracer_ptr, scene::film* film_ptr);
};

}

}

#endif
