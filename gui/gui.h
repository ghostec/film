#ifndef GUI_GUIH
#define GUI_GUIH

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "network/client.h"

namespace film {
class GUI : public Client {
  Q_OBJECT
 public:
  GUI();
  ~GUI();
  void setPixmapItem(QGraphicsPixmapItem* pixmapItemPtr);

 private:
  QGraphicsPixmapItem* pixmapItemPtr;
  QGraphicsScene* scenePtr;
  QGraphicsView* viewPtr;

  virtual void connectionCb();
  virtual void handleMessage(const message_t messageType);
  void handleFrame();
};
}

#endif
