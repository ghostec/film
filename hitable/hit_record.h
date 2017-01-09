#ifndef HITRECORDH
#define HITRECORDH

#include "math/point3.h"
#include "math/normal.h"
#include "math/rgb.h"

namespace film {

namespace hitable {

struct hit_record {
  bool hit;
  math::point3 hit_point;
  math::normal normal;
  math::rgb color;
};

}

}

#endif
