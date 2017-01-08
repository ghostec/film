#ifndef VEC3H
#define VEC3H

namespace film {

namespace math {

class vec3 {
public:
  double x, y, z;
  
  vec3();
  vec3(double a);
  vec3(double _x, double _y, double _z);
  vec3(const vec3& v);
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
  double Length() const;
  double LengthSquared() const;
  void Normalize();
  vec3 Hat() const;
};

}

}

#endif
