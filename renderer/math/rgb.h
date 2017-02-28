#ifndef RENDERER_MATH_RGBH
#define RENDERER_MATH_RGBH

namespace film { namespace math {

float fclamp(float x);

class rgb {
public:
  float r, g, b;

  rgb();
  rgb(float a);
  rgb(float _r, float _g, float _b);
  rgb(const rgb& _rgb);
  ~rgb();
  rgb& operator=(const rgb& rhs);
  rgb operator+(const rgb& _r) const;
  rgb operator*(const rgb& _r) const;
  rgb operator/(const float a) const;
  rgb operator*(const float a) const;
  rgb& operator/=(const float a);
  rgb& operator*=(const float a);
  rgb& operator+=(const rgb& _r);
  rgb clamp() const;
  rgb pow(float p) const;
  float average() const;
};

} }

#endif
