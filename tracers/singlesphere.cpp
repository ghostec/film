#include "singlesphere.h"
#include "hitable/hit_record.h"

namespace film {

namespace tracers {

singlesphere::singlesphere() : tracer() {}

singlesphere::singlesphere(scene::scenegraph* _scenegraph) : tracer(_scenegraph) {}

singlesphere::~singlesphere() {
  scenegraph = nullptr;
}

math::rgb singlesphere::TraceRay(const math::ray ray, const hitable::hitable* scene) const {
  hitable::hit_record rec;
  double t = 100.0;

  if(scenegraph->GetObjects()->hit(ray, t, rec)) return {1.0, 0.0, 0.0};

  return {0.0};
}

}

}
