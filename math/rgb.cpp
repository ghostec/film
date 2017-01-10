#include <cmath>
#include "rgb.h"

namespace film {

namespace math {

rgb::rgb() : r(0), g(0), b(0) {}
rgb::rgb(float a) : r(a), g(a), b(a) {}
rgb::rgb(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
rgb::rgb(const rgb& _rgb) : r(_rgb.r), g(_rgb.g), b(_rgb.b) {}

rgb::~rgb() {}

rgb& rgb::operator=(const rgb& rhs) {
  if(this == &rhs) return *this;

  r = rhs.r; g = rhs.g; b = rhs.b;

  return *this;
}

rgb rgb::operator+(const rgb& _r) const {
  return rgb(r + _r.r, g + _r.g, b + _r.b);
}

rgb rgb::operator*(const rgb& _r) const {
  return rgb(r * _r.r, g * _r.g, b * _r.b);
}

rgb rgb::operator/(const float a) const {
  auto inva = 1.0 / a;
  return rgb(r * inva, g * inva, b * inva);
}

rgb rgb::operator*(const float a) const {
  return rgb(r * a, g * a, b * a);
}

rgb& rgb::operator/=(const float a) {
  auto inva = 1.0 / a;
  r *= inva; g *= inva; b *= inva;
  return *this;
}

rgb& rgb::operator*=(const float a) {
  r *= a; g *= a; b *= a;
  return *this;
}

rgb& rgb::operator+=(const rgb& _r) {
  r += _r.r; g += _r.g; b += _r.b;
  return *this;
}

rgb rgb::Pow(float p) const {
  return rgb(pow(r, p), pow(g, p), pow(b, p));
}

float rgb::Average() const {
  return 0.3333333333333 * (r + g + b);
}

inline double clamp(double x) { return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

std::array<int, 3> rgb::ToIntArray() const {
  return  {toInt(r), toInt(g), toInt(b)};
}

}

}
