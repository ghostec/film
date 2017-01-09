#ifndef TRACERH
#define TRACERH

#include "scene/scenegraph.h"
#include "math/ray.h"
#include "math/rgb.h"

namespace film {

namespace tracers {

class tracer {
public:
  tracer();
  tracer(scene::scenegraph* _scenegraph);
  ~tracer();
  virtual math::rgb TraceRay(const math::ray ray) const;
protected:
  scene::scenegraph* scenegraph;
};

}

}

#endif
