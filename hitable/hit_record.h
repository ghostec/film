#ifndef HITRECORDH
#define HITRECORDH

namespace film {

class math::point3;
class math::normal;
class math:rgb;

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
