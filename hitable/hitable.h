#ifndef HITABLE_HITABLEH
#define HITABLE_HITABLEH

#include "math/normal.h"
#include "math/point3.h"
#include "math/ray.h"

namespace film {
struct HitRecord {
  bool hit;
  float t;
  point3 point;
  normal normal;
};

class Hitable {
 public:
  Hitable() {}
  ~Hitable() {}
  virtual HitRecord hit(const ray& ray, float t_min, float t_max) const = 0;
};
}

#endif
