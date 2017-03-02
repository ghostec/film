#ifndef RENDERER_MATHNORMALH
#define RENDERER_MATHNORMALH

#include "vec3.h"

namespace film { namespace math {

class normal {
public:
  double x, y, z;

  normal();
  normal(double a);
  normal(double _x, double _y, double _z);
  normal(const normal& n);
  normal(const vec3& v);
  ~normal();
  normal& operator=(const normal& rhs);
  normal operator-() const;
  normal operator+(const normal& n) const;
  normal& operator+=(const normal& n);
  double operator*(const vec3& v) const;
  normal operator*(const double a) const;
  void normalize();
};

} }

#endif
