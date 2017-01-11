#ifndef MULTIPLEOBJECTSH 
#define MULTIPLEOBJECTSH

#include "tracer.h"

namespace film {

namespace tracers {

class multiple_objects : public tracer {
public:
  multiple_objects();
  ~multiple_objects();
  virtual math::rgb TraceRay(const math::ray ray, const hitable::hitable* scene) const;
};

}

}

#endif

