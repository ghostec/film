#ifndef HITABLE_SPHEREH
#define HITABLE_SPHEREH

#include "hitable.h"

namespace film {
class Sphere : public Hitable {
 public:
  point3 center;
  float radius;

  Sphere(point3 center, float radius);
  ~Sphere();
  virtual HitRecord hit(const ray& ray, float t_min, float t_max) const;

 private:
  HitRecord hit_record_from_parameter(const ray& ray, float t) const;
};
}

#endif
