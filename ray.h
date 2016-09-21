#ifndef RAYH
#define RAYH

#include "vec3.h"

class ray {
 private:
  vec3 o_, d_;

 public:
  ray(vec3 o, vec3 d) : o_(o), d_(d) {}
  vec3 origin() const { return o_; }
  vec3 direction() const { return d_; }
};

#endif /* ifndef RAYH */
