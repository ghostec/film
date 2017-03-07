#ifndef MATH_VEC3H
#define MATH_VEC3H

namespace film {
class normal;

class vec3 {
 public:
  double x, y, z;

  vec3();
  vec3(double a);
  vec3(double _x, double _y, double _z);
  vec3(const vec3& v);
  vec3(const normal& n);
  ~vec3();
  vec3& operator=(const vec3& rhs);
  vec3 operator-() const;
  vec3 operator*(const double a) const;
  vec3 operator/(const double a) const;
  vec3 operator-(const vec3& v) const;
  vec3 operator+(const vec3& v) const;
  vec3& operator+=(const vec3& v);
  vec3& operator-=(const vec3& v);
  double operator*(const vec3& v) const;
  vec3 operator^(const vec3& v) const;
  double length() const;
  double length_squared() const;
  void normalize();
  vec3 hat() const;
};

vec3 operator*(const double a, const vec3& v);
}

#endif
