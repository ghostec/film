#include <iostream>
#include <cmath>
#include <cstdlib>

double PI = 3.1415926535;
double OVER_PI = 1.0 / PI;

class vec3 {
private:
  double v_[3];
public:
  vec3() : v_{0, 0, 0} {}
  vec3(double v) : v_{v, v, v} {}
  vec3(double a, double b, double c) : v_{a, b, c} {}
  double operator[](const size_t i) const { return v_[i]; }
  vec3 operator+(const vec3 b) const { return vec3(v_[0] + b[0], v_[1] + b[1], v_[2] + b[2]); }
  vec3 operator-(const vec3 b) const { return vec3(v_[0] - b[0], v_[1] - b[1], v_[2] - b[2]); }
  vec3 operator*(const vec3 b) const { return vec3(v_[0] * b[0], v_[1] * b[1], v_[2] * b[2]); }
  vec3 operator*(const double b) const { return vec3(v_[0] * b, v_[1] * b, v_[2] * b); }
  double length() const { return sqrt(v_[0]*v_[0] + v_[1]*v_[1] + v_[2]*v_[2]); }
  vec3 hat() const { return *this * (1.0 / length()); }
  vec3& normalize() { return *this = hat(); }
  double dot(const vec3 b) const { return v_[0] * b[0] + v_[1] * b[1] + v_[2] * b[2]; }
  vec3 cross(const vec3 b) const {
    return vec3(v_[1]*b[2] - v_[2]*b[1], v_[2]*b[0] - v_[0]*b[2], v_[0]*b[1] - v_[1]*b[0]);
  }
};

class ray {
private:
  vec3 o_, d_;
public:
  ray(vec3 o, vec3 d) : o_(o), d_(d) {}
  vec3 origin() const { return o_; }
  vec3 direction() const { return d_; }
};

enum class refl_t { diffusal, specular, refractive };

class sphere {
private:
  double r_;        // radius
  vec3 p_, e_, c_;  // position, emission, color
  refl_t refl_;
public:
  sphere(double r, vec3 p, vec3 e, vec3 c, refl_t refl) : r_(r), p_(p), e_(e), c_(c), refl_(refl) {}
  double intersect(const ray r) const {
    vec3 op = p_ - r.origin();
    double t, eps = 1e-4;
    double b = op.dot(r.direction());
    double det = b * b - op.dot(op) + r_*r_;
    if(det < 0) return 0;
    det = sqrt(det);
    return (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
  }
};

sphere spheres[] = {//Scene: radius, position, emission, color, material 
   sphere(1e5, vec3( 1e5+1,40.8,81.6), vec3(),vec3(.75,.25,.25),refl_t::diffusal),   //Left 
   sphere(1e5, vec3(-1e5+99,40.8,81.6),vec3(),vec3(.25,.25,.75),refl_t::diffusal),   //Rght 
   sphere(1e5, vec3(50,40.8, 1e5),     vec3(),vec3(.75,.75,.75),refl_t::diffusal),   //Back 
   sphere(1e5, vec3(50,40.8,-1e5+170), vec3(),vec3(),           refl_t::diffusal),   //Frnt 
   sphere(1e5, vec3(50, 1e5, 81.6),    vec3(),vec3(.75,.75,.75),refl_t::diffusal),   //Botm 
   sphere(1e5, vec3(50,-1e5+81.6,81.6),vec3(),vec3(.75,.75,.75),refl_t::diffusal),   //Top 
   sphere(16.5,vec3(27,16.5,47),       vec3(),vec3(1,1,1)*.999, refl_t::specular),   //Mirr 
   sphere(16.5,vec3(73,16.5,78),       vec3(),vec3(1,1,1)*.999, refl_t::refractive), //Glas 
   sphere(600, vec3(50,681.6-.27,81.6),vec3(12,12,12),  vec3(), refl_t::diffusal)    //Lite 
};

double clamp(double x) { return x < 0 ? 0 : x > 1 ? 1 : x; }

int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

bool intersect(const ray r, double t, int id) {
  double n = sizeof(spheres) / sizeof(sphere);
  double d;
  double inf = t = 1e20;

  for(int i = int(n); i--;) {
    if((d = spheres[i].intersect(r)) && d < t) {
      t = d;
      id = i;
    }
  }
  
  return t < inf;
}

int main(int argc, char *argv[]) {
  int w = 1024, h = 768, samps = (argc == 2) ? atoi(argv[1]) / 4 : 1; // # samples 
  ray cam(vec3(50,52,295.6), vec3(0,-0.042612,-1).normalize());       // cam pos, dir 
  vec3 cx(w*.5135/h), cy = (cx.cross(cam.direction())).normalize()*.5135, r, *c = new vec3[w * h]; 
#pragma omp parallel for schedule(dynamic, 1) private(r)       // OpenMP  
  return 0;
}
