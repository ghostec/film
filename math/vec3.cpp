#include <cmath>

#include "normal.h"
#include "vec3.h"

namespace film {
vec3::vec3() : x(0), y(0), z(0) {}
vec3::vec3(double a) : x(a), y(a), z(a) {}
vec3::vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
vec3::vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}
vec3::vec3(const normal& n) : x(n.x), y(n.y), z(n.z) {}

vec3::~vec3() {}

vec3& vec3::operator=(const vec3& rhs) {
  if (this == &rhs) return *this;

  x = rhs.x;
  y = rhs.y;
  z = rhs.z;

  return *this;
}

vec3 vec3::operator-() const { return vec3(-x, -y, -z); }
vec3 vec3::operator*(const double a) const { return vec3(x * a, y * a, z * a); }

vec3 vec3::operator/(const double a) const {
  auto inva = 1.0 / a;
  return vec3(x * inva, y * inva, z * inva);
}

vec3 vec3::operator-(const vec3& v) const {
  return vec3(x - v.x, y - v.y, z - v.z);
}

vec3 vec3::operator+(const vec3& v) const {
  return vec3(x + v.x, y + v.y, z + v.z);
}

vec3& vec3::operator+=(const vec3& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

vec3& vec3::operator-=(const vec3& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

double vec3::operator*(const vec3& v) const {
  return x * v.x + y * v.y + z * v.z;
}

vec3 vec3::operator^(const vec3& v) const {
  return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

double vec3::length() const { return sqrt(x * x + y * y + z * z); }

double vec3::length_squared() const { return x * x + y * y + z * z; }

void vec3::normalize() {
  auto invl = 1.0 / length();
  x *= invl;
  y *= invl;
  z *= invl;
}

vec3 vec3::hat() const {
  auto invl = 1.0 / length();
  return vec3(x * invl, y * invl, z * invl);
}

vec3 operator*(const double a, const vec3& v) {
  return vec3(a * v.x, a * v.y, a * v.z);
}
}
