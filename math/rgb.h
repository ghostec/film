#ifndef RGBH
#define RGBH

namespace film {

namespace math {

class rgb {
public:
  double r, g, b;

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
  rgb Pow(float p) const;
  float Average() const;
};

}

}

#endif
