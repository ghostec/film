#ifndef HITABLECOMPOSEH
#define HITABLECOMPOSEH

#include <vector>

#include "hitable.h"

namespace film {

namespace hitable {

class hitable_compose : public hitable {
public:
  hitable_compose();
  virtual bool hit(const math::ray& ray, double& t_min, hit_record& rec) const;
  void add(hitable* _hitable);
private:
  std::vector<hitable*> hitables;
};

}

}

#endif

