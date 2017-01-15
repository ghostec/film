#include <iostream>
#include <thread>
#include <chrono>

#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QImage>

#include "scene/film.h"
#include "scene/scenegraph.h"
#include "scene/renderer.h"
#include "tracers/multiple_objects.h"
#include "cameras/pinhole.h"

void work(film::scene::renderer* renderer_ptr) {
  film::scene::film* film_ptr = new film::scene::film(400, 300);
  film::scene::scenegraph* scenegraph_ptr = new film::scene::scenegraph();
  film::tracers::tracer* tracer_ptr = new film::tracers::multiple_objects();
  film::cameras::pinhole* camera_ptr = new film::cameras::pinhole();

  camera_ptr->SetUp({0, 1, 0});
  camera_ptr->SetEye({-10, 4, 7});
  camera_ptr->SetLookAt({0, 0, 0});
  camera_ptr->SetPlaneDistance(800);
  camera_ptr->SetNThreads(2);
  camera_ptr->ComputeUvw();

  scenegraph_ptr->Build();

  renderer_ptr->SetFilm(film_ptr);
  renderer_ptr->SetSceneGraph(scenegraph_ptr);
  renderer_ptr->SetTracer(tracer_ptr);
  renderer_ptr->SetCamera(camera_ptr);

  renderer_ptr->Render();
  film_ptr->SavePPM();
}

int main(int argc, char *argv[]) {
  film::scene::renderer renderer;

  std::thread t(work, &renderer);

  film::scene::film* film_ptr = nullptr;
  do {
    film_ptr = renderer.GetFilm();
  } while(film_ptr == nullptr);

  auto hres = film_ptr->GetHres();
  auto vres = film_ptr->GetVres();

  QApplication app(argc, argv);
  QWidget window;
  window.resize(hres, vres);
  window.show();

  QImage img = QImage(hres, vres, QImage::Format_RGB32);
  QLabel lbl;
  lbl.setParent(&window);

  std::chrono::time_point<std::chrono::system_clock> timer, time;
  timer = std::chrono::system_clock::now();

  while(true) {
    time = std::chrono::system_clock::now();
    if((time - timer).count() >= 16666) {
      for(int i = 0; i < hres; i++) {
        for(int j = 0; j < vres; j++) {
          const auto p = j * hres + i;
          const auto rgb = (*film_ptr)[p].ToIntArray();
          QRgb qrgb = qRgb(rgb[0], rgb[1], rgb[2]);
          img.setPixel(i, vres - j - 1, qrgb);
        }
      }
      lbl.setPixmap(QPixmap::fromImage(img));
      lbl.setGeometry(0, 0, img.width(), img.height());
      lbl.show();
      
      app.processEvents();
      timer = time;
    }
  }

  return app.exec();
}
