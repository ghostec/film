#include <QtCore>
#include <QtNetwork>

#include "hitable/sphere.h"
#include "network/worker.h"
#include "renderer/scene.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  film::Worker worker;

  QHostAddress addr("127.0.0.1");
  quint16 port = 3000;

  auto cameraPtr =
      new film::Camera({0, 0, 1}, {0, 0, -1}, {0, 1, 0}, 90, 800.0f / 600.0f);
  auto worldPtr = new film::Sphere({0, 0, -1}, 0.5);
  auto scenePtr = new film::Scene();
  scenePtr->setCamera(cameraPtr);
  scenePtr->setWorld(worldPtr);

  worker.setScene(scenePtr);

  worker.connectToHost(addr, port);

  return app.exec();
}
