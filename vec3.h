#ifndef VEC3H
#define VEC3H

class vec3 {
 private:
  double v_[3];

 public:
  vec3(double x = 0, double y = 0, double z = 0) : v_{x, y, z} {}
  double operator[](const size_t i) const { return v_[i]; }
  vec3 operator+(const vec3 b) const {
    return vec3(v_[0] + b[0], v_[1] + b[1], v_[2] + b[2]);
  }
  vec3 operator-(const vec3 b) const {
    return vec3(v_[0] - b[0], v_[1] - b[1], v_[2] - b[2]);
  }
  vec3 operator*(double b) const {
    return vec3(v_[0] * b, v_[1] * b, v_[2] * b);
  }
  vec3 operator*(const vec3 b) const {
    return vec3(v_[0] * b[0], v_[1] * b[1], v_[2] * b[2]);
  }
  double length() const {
    return sqrt(v_[0] * v_[0] + v_[1] * v_[1] + v_[2] * v_[2]);
  }
  vec3 hat() const {
    return *this * (1 / length());
  }
  vec3 &normalize() {
    return *this = hat();
  }
  double dot(const vec3 b) const {
    return v_[0] * b[0] + v_[1] * b[1] + v_[2] * b[2];
  }  // cross:
  vec3 cross(const vec3 b) const {
    return vec3(v_[1] * b[2] - v_[2] * b[1], v_[2] * b[0] - v_[0] * b[2],
                v_[0] * b[1] - v_[1] * b[0]);
  }
};

#endif /* ifndef VEC3H */
