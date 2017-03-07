#include <cmath>

#include "point3.h"

namespace film {
point3::point3() : x(0), y(0), z(0) {}
point3::point3(double a) : x(a), y(a), z(a) {}
point3::point3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
point3::point3(const point3& p) : x(p.x), y(p.y), z(p.z) {}

point3::~point3() {}

point3& point3::operator=(const point3& rhs) {
  if (this == &rhs) return *this;

  x = rhs.x;
  y = rhs.y;
  z = rhs.z;

  return *this;
}

point3 point3::operator-() const { return point3(-x, -y, -z); }

point3 point3::operator*(const double a) const {
  return point3(x * a, y * a, z * a);
}

vec3 point3::operator-(const point3& p) const {
  return vec3(x - p.x, y - p.y, z - p.z);
}

point3 point3::operator-(const vec3& v) const {
  return point3(x - v.x, y - v.y, z - v.z);
}

point3 point3::operator+(const vec3& v) const {
  return point3(x + v.x, y + v.y, z + v.z);
}

double point3::distance(const point3 p) const {
  return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) +
              (z - p.z) * (z - p.z));
}

double point3::distance_squared(const point3 p) const {
  return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z);
}
}
