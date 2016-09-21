#ifndef SPHEREH
#define SPHEREH

#include "vec3.h"
#include "ray.h"
#include "refl_t.h"

class sphere {
 private:
  double r_;        // radius
  vec3 p_, e_, c_;  // position, emission, color
  refl_t refl_;     // reflection type (diffuse, specular, refractive)

 public:
  sphere(double r, vec3 p, vec3 e, vec3 c, refl_t refl)
      : r_(r), p_(p), e_(e), c_(c), refl_(refl) {}
  double intersect(const ray r) const {  // returns distance, 0 if nohit
    vec3 op =
        p_ - r.origin();  // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    double t, eps = 1e-4, b = op.dot(r.direction()),
              det = b * b - op.dot(op) + r_ * r_;
    if (det < 0)
      return 0;
    else
      det = sqrt(det);
    return (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
  }
  double radius() const { return r_; }
  vec3 position() const { return p_; }
  vec3 emission() const { return e_; }
  vec3 color() const { return c_; }
  refl_t refl() const { return refl_; }
};

#endif /* ifndef SPHEREH */
