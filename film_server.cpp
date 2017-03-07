#include <Magick++.h>
#include <QtCore>

#include "network/server.h"

int main(int argc, char *argv[]) {
  Magick::InitializeMagick(*argv);
  QCoreApplication app(argc, argv);

  film::Server server;

  QHostAddress addr("127.0.0.1");
  quint16 port = 3000;

  server.listen(addr, port);

  return app.exec();
}
