#ifndef HITABLEH
#define HITABLEH

#include "hit_record.h"
#include "math/ray.h"

namespace film {

namespace hitable {

class hitable {
public:
  hitable();
  virtual bool hit(const math::ray& ray, double& t_min, hit_record& rec) const = 0;
protected:
  math::rgb color;
};

}

}

#endif
