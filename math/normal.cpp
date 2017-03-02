#include <cmath>
#include "normal.h"

namespace film { namespace math {

normal::normal() : x(0), y(0), z(0) {}
normal::normal(double a) : x(a), y(a), z(a) {}
normal::normal(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
normal::normal(const normal& n) : x(n.x), y(n.y), z(n.z) {}
normal::normal(const vec3& v) : x(v.x), y(v.y), z(v.z) {}

normal::~normal() {}

normal& normal::operator=(const normal& rhs) {
  if(this == &rhs) return *this;

  x = rhs.x; y = rhs.y; z = rhs.z;

  return *this;
}

normal normal::operator-() const {
  return normal(-x, -y, -z);
}

normal normal::operator+(const normal& n) const {
  return normal(x + n.x, y + n.y, z + n.z);
}

normal& normal::operator+=(const normal& n) {
  x += n.x; y += n.y; z += n.z;
  return *this;
}

double normal::operator*(const vec3& v) const {
  return x * v.x + y * v.y + z * v.z;
}

normal normal::operator*(const double a) const {
  return normal(x * a, y * a, z * a);
}

void normal::normalize() {
  auto invl = sqrt(x * x + y * y + z * z);
  x *= invl; y *= invl; z *= invl;
}

} }
