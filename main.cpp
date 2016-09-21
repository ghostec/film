#include <math.h>    // smallpt, a Path Tracer by Kevin Beason, 2008
#include <stdio.h>   //        Remove "-fopenmp" for g++ version < 4.2
#include <stdlib.h>  // Make : g++ -O3 -fopenmp smallpt.cpp -o smallpt
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "refl_t.h"

sphere spheres[] = {
    // Scene: radius, position, emission, color, material
    sphere(1e5, vec3(1e5 + 1, 40.8, 81.6), vec3(), vec3(.75, .25, .25),
           refl_t::diffuse),  // Left
    sphere(1e5, vec3(-1e5 + 99, 40.8, 81.6), vec3(), vec3(.25, .25, .75),
           refl_t::diffuse),  // Rght
    sphere(1e5, vec3(50, 40.8, 1e5), vec3(), vec3(.75, .75, .75),
           refl_t::diffuse),  // Back
    sphere(1e5, vec3(50, 40.8, -1e5 + 170), vec3(), vec3(),
           refl_t::diffuse),  // Frnt
    sphere(1e5, vec3(50, 1e5, 81.6), vec3(), vec3(.75, .75, .75),
           refl_t::diffuse),  // Botm
    sphere(1e5, vec3(50, -1e5 + 81.6, 81.6), vec3(), vec3(.75, .75, .75),
           refl_t::diffuse),  // Top
    sphere(16.5, vec3(27, 16.5, 47), vec3(), vec3(1, 1, 1) * .999,
           refl_t::specular),  // Mirr
    sphere(16.5, vec3(73, 16.5, 78), vec3(), vec3(1, 1, 1) * .999,
           refl_t::refractive),  // Glas
    sphere(600, vec3(50, 681.6 - .27, 81.6), vec3(12, 12, 12), vec3(),
           refl_t::diffuse)  // Lite
};

inline double clamp(double x) { return x < 0 ? 0 : x > 1 ? 1 : x; }

inline int toInt(double x) { return int(pow(clamp(x), 1 / 2.2) * 255 + .5); }

inline bool intersect(const ray r, double &t, int &id) {
  double n = sizeof(spheres) / sizeof(sphere), d, inf = t = 1e20;
  for (int i = int(n); i--;)
    if ((d = spheres[i].intersect(r)) && d < t) {
      t = d;
      id = i;
    }
  return t < inf;
}

vec3 radiance(const ray r, int depth, unsigned short *Xi) {
  double t;                                 // distance to intersection
  int id = 0;                               // id of intersected object
  if (!intersect(r, t, id)) return vec3();  // if miss, return black
  const sphere &obj = spheres[id];          // the hit object
  vec3 x = r.origin() + r.direction() * t, n = (x - obj.position()).normalize(),
       nl = n.dot(r.direction()) < 0 ? n : n * -1, f = obj.color();
  double p = f[0] > f[1] && f[0] > f[2]
                 ? f[0]
                 : f[1] > f[2] ? f[1] : f[2];  // max refl
  if (++depth > 5)
    if (erand48(Xi) < p)
      f = f * (1 / p);
    else
      return obj.emission();            // R.R.
  if (obj.refl() == refl_t::diffuse) {  // Ideal refl_t::diffuse reflection
    double r1 = 2 * M_PI * erand48(Xi), r2 = erand48(Xi), r2s = sqrt(r2);
    vec3 w = nl,
         u = ((fabs(w[0]) > .1 ? vec3(0, 1) : vec3(1)).cross(w)).normalize(),
         v = w.cross(u);
    vec3 d =
        (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).normalize();
    return obj.emission() + f * radiance(ray(x, d), depth, Xi);
  } else if (obj.refl() ==
             refl_t::specular)  // Ideal refl_t::specular reflection
    return obj.emission() +
           f * radiance(ray(x, r.direction() - n * 2 * n.dot(r.direction())),
                        depth, Xi);
  ray reflray(
      x,
      r.direction() -
          n * 2 * n.dot(r.direction()));  // Ideal dielectric refl_t::refractive
  bool into = n.dot(nl) > 0;              // ray from outside going in?
  double nc = 1, nt = 1.5, nnt = into ? nc / nt : nt / nc,
         ddn = r.direction().dot(nl), cos2t;
  if ((cos2t = 1 - nnt * nnt * (1 - ddn * ddn)) <
      0)  // Total internal reflection
    return obj.emission() + f * radiance(reflray, depth, Xi);
  vec3 tdir =
      (r.direction() * nnt - n * ((into ? 1 : -1) * (ddn * nnt + sqrt(cos2t))))
          .normalize();
  double a = nt - nc, b = nt + nc, R0 = a * a / (b * b),
         c = 1 - (into ? -ddn : tdir.dot(n));
  double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re, P = .25 + .5 * Re,
         RP = Re / P, TP = Tr / (1 - P);
  return obj.emission() +
         f * (depth > 2
                  ? (erand48(Xi) < P ?  // Russian roulette
                         radiance(reflray, depth, Xi) * RP
                                     : radiance(ray(x, tdir), depth, Xi) * TP)
                  : radiance(reflray, depth, Xi) * Re +
                        radiance(ray(x, tdir), depth, Xi) * Tr);
}

int main(int argc, char *argv[]) {
  int w = 1024, h = 768,
      samps = argc == 2 ? atoi(argv[1]) / 4 : 1;  // # samples
  ray cam(vec3(50, 52, 295.6),
          vec3(0, -0.042612, -1).normalize());  // cam pos, dir
  vec3 cx = vec3(w * .5135 / h),
       cy = (cx.cross(cam.direction())).normalize() * .5135, r,
       *c = new vec3[w * h];
#pragma omp parallel for schedule(dynamic, 1) private(r)  // OpenMP
  for (int y = 0; y < h; y++) {  // Loop over image rows
    fprintf(stderr, "\rRendering (%d spp) %5.2f%%", samps * 4,
            100. * y / (h - 1));
    for (unsigned short x = 0,
                        Xi[3] = {0, 0, static_cast<unsigned short>(y * y * y)};
         x < w; x++)  // Loop cols
      for (int sy = 0, i = (h - y - 1) * w + x; sy < 2;
           sy++)                                      // 2x2 subpixel rows
        for (int sx = 0; sx < 2; sx++, r = vec3()) {  // 2x2 subpixel cols
          for (int s = 0; s < samps; s++) {
            double r1 = 2 * erand48(Xi),
                   dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
            double r2 = 2 * erand48(Xi),
                   dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
            vec3 d = cx * (((sx + .5 + dx) / 2 + x) / w - .5) +
                     cy * (((sy + .5 + dy) / 2 + y) / h - .5) + cam.direction();
            r = r +
                radiance(ray(cam.origin() + d * 140, d.normalize()), 0, Xi) *
                    (1. / samps);
          }  // Camera rays are pushed ^^^^^ forward to start in interior
          c[i] = c[i] + vec3(clamp(r[0]), clamp(r[1]), clamp(r[2])) * .25;
        }
  }
  FILE *f = fopen("image.ppm", "w");  // Write image to PPM file.
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  for (int i = 0; i < w * h; i++)
    fprintf(f, "%d %d %d ", toInt(c[i][0]), toInt(c[i][1]), toInt(c[i][2]));
}
