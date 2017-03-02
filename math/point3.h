#ifndef MATH_POINT3H
#define MATH_POINT3H

#include "vec3.h"

namespace film { namespace math {

class point3 {
public:
  double x, y, z;
  
  point3();
  point3(double a);
  point3(double _x, double _y, double _z);
  point3(const point3& p);
  ~point3();
  point3& operator=(const point3& rhs);
  point3 operator-() const;
  point3 operator*(const double a) const;
  vec3 operator-(const point3& p) const;
  point3 operator-(const vec3& v) const;
  point3 operator+(const vec3& v) const;
  double distance(const point3 p) const;
  double distance_squared(const point3 p) const;
};

} }

#endif
