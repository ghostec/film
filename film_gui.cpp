#include <QApplication>
#include <QtNetwork>

#include "gui/gui.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  film::GUI gui;

  QHostAddress addr("127.0.0.1");
  quint16 port = 3000;

  gui.connectToHost(addr, port);

  return app.exec();
}
