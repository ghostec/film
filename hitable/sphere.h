#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include "math/point3.h"
#include "math/normal.h"

namespace film {

namespace hitable {

class sphere : public hitable {
public:
  sphere();
  sphere(const math::point3& c, const double r);
  virtual bool hit(const math::ray& ray, double& t_min, hit_record& rec) const;
private:
  math::point3 center;
  double radius;
};

}

}

#endif
