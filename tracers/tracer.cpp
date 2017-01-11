#include "tracer.h"

namespace film {

namespace tracers {

tracer::tracer() {}

tracer::~tracer() {}

math::rgb tracer::TraceRay(const math::ray ray, const hitable::hitable* scene) const {
  return {0.0};
}

}

}
