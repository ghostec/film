#ifndef SINGLESPHEREH
#define SINGLESPHEREH

#include "tracer.h"

namespace film {

namespace tracers {

class singlesphere : public tracer {
public:
  singlesphere();
  singlesphere(scene::scenegraph* _scenegraph);
  ~singlesphere();
  virtual math::rgb TraceRay(const math::ray ray, const hitable::hitable* scene) const;
};

}

}

#endif
