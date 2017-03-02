#ifndef HITABLE_HITABLEH
#define HITABLE_HITABLEH

#include "math/point3.h"
#include "math/normal.h"
#include "math/ray.h"

namespace film { namespace hitable {

struct HitRecord {
  bool hit;
  float t;
  math::point3 point;
  math::normal normal;
};

class Hitable {
public:
  Hitable() {}
  ~Hitable() {}
  virtual HitRecord hit(const math::ray& ray, float t_min, float t_max) const = 0;
};

} }

#endif
