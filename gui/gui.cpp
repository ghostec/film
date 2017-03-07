#include <QImage>
#include <QtDebug>

#include "gui.h"

namespace film {
GUI::GUI() {
  auto image = QImage(800, 600, QImage::Format_Indexed8);
  image.fill(0);
  pixmapItemPtr = new QGraphicsPixmapItem(QPixmap::fromImage(image));
  scenePtr = new QGraphicsScene();
  scenePtr->addItem(pixmapItemPtr);
  viewPtr = new QGraphicsView();
  viewPtr->setScene(scenePtr);
  viewPtr->show();
}

GUI::~GUI() {}

void GUI::connectionCb() { dataStream << message_t::REGISTER_GUI; }

void GUI::handleMessage(const message_t messageType) {
  switch (messageType) {
    case message_t::FRAME:
      return handleFrame();
  }
}

void GUI::handleFrame() {
  quint16 width, height;
  QByteArray bytes;
  dataStream >> bytes;

  if (!dataStream.commitTransaction()) return;

  auto image = QImage::fromData(bytes);
  auto pixmapItemPtr = new QGraphicsPixmapItem(QPixmap::fromImage(image));
  setPixmapItem(pixmapItemPtr);
}

void GUI::setPixmapItem(QGraphicsPixmapItem* pixmapItemPtr) {
  auto ref = this->pixmapItemPtr;
  scenePtr->removeItem(ref);
  delete ref;

  this->pixmapItemPtr = pixmapItemPtr;
  scenePtr->addItem(pixmapItemPtr);

  viewPtr->show();
}
}

#include "moc_gui.cpp"
