#ifndef TRACERH
#define TRACERH

#include "scene/scenegraph.h"
#include "hitable/hitable.h"
#include "math/ray.h"
#include "math/rgb.h"

namespace film {

namespace tracers {

class tracer {
public:
  tracer();
  ~tracer();
  virtual math::rgb TraceRay(const math::ray ray, const hitable::hitable* scene) const;
};

}

}

#endif
