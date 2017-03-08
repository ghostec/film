#ifndef HITABLE_HITABLEH
#define HITABLE_HITABLEH

#include "math/normal.h"
#include "math/point3.h"
#include "math/ray.h"

namespace film {
enum class hitable_t : int { SPHERE };

struct HitRecord {
  bool hit;
  float t;
  point3 point;
  normal normal;
};

class Hitable {
 public:
  Hitable(hitable_t type) : type(type) {}
  ~Hitable() {}
  virtual HitRecord hit(const ray& ray, float t_min, float t_max) const = 0;
  hitable_t getType() const { return type; }

 protected:
  hitable_t type;
};
}

#endif
