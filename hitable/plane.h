#ifndef PLANEH
#define PLANEH

#include "hitable.h"
#include "math/point3.h"
#include "math/normal.h"

namespace film {

namespace hitable {

class plane : public hitable {
public:
  plane();
  plane(const math::point3& p, const math::normal& n);
  virtual bool hit(const math::ray& ray, double& t_min, hit_record& rec) const;
private:
  math::point3 point;
  math::normal normal;
};

}

}

#endif
