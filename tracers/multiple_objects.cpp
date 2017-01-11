#include "multiple_objects.h"
#include "hitable/hit_record.h"

namespace film {

namespace tracers {

multiple_objects::multiple_objects() : tracer() {}

multiple_objects::~multiple_objects() {}

math::rgb multiple_objects::TraceRay(const math::ray ray, const hitable::hitable* scene) const {
  hitable::hit_record rec;
  double t = 100.0;

  if(scene->hit(ray, t, rec)) return rec.color;

  return {0.0};
}

}

}
