#ifndef HITABLE_SPHEREH
#define HITABLE_SPHEREH

#include "hitable.h"

namespace film { namespace hitable {

class Sphere : public Hitable {
public:
  math::point3 center;
  float radius;

  Sphere(math::point3 center, float radius);
  ~Sphere();
  virtual HitRecord hit(const math::ray& ray, float t_min, float t_max) const;
private:
  HitRecord hit_record_from_parameter(const math::ray& ray, float t) const;
};

} }

#endif
