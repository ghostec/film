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
#include "tracers/singlesphere.h"

void work(film::scene::renderer* renderer) {
  film::scene::film* film_ptr = new film::scene::film(400, 300);
  film::scene::scenegraph* scenegraph_ptr = new film::scene::scenegraph();
  film::tracers::tracer* tracer_ptr = new film::tracers::singlesphere(scenegraph_ptr);
  
  scenegraph_ptr->Build();

  renderer->SetFilm(film_ptr);
  renderer->SetSceneGraph(scenegraph_ptr);
  renderer->SetTracer(tracer_ptr);

  renderer->Render();
  film_ptr->SavePPM();
}

int main(int argc, char *argv[]) {
  film::scene::renderer renderer;

  std::thread t(work, &renderer);
  t.join();

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
