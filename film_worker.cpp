#include <QtCore>
#include <QtNetwork>

#include "network/worker.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  film::Worker worker;

  QHostAddress addr("127.0.0.1");
  quint16 port = 3000;

  worker.connectToHost(addr, port);

  return app.exec();
}
