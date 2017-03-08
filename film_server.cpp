#include <Magick++.h>
#include <QtCore>

#include "hitable/sphere.h"
#include "network/server.h"
#include "renderer/scene.h"

int main(int argc, char *argv[]) {
  Magick::InitializeMagick(*argv);
  QCoreApplication app(argc, argv);

  film::Server server;

  QHostAddress addr("127.0.0.1");
  quint16 port = 3000;

  auto cameraPtr =
      new film::Camera({0, 0, 1}, {0, 0, -1}, {0, 1, 0}, 90, 800.0f / 600.0f);
  auto worldPtr = new film::Sphere({0, 0, -1}, 0.5);
  auto scenePtr = new film::Scene();
  scenePtr->setCamera(cameraPtr);
  scenePtr->setWorld(worldPtr);

  server.setScene(scenePtr);

  server.listen(addr, port);

  return app.exec();
}
