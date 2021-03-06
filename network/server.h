#ifndef SERVER_H
#define SERVER_H

#include <QDataStream>
#include <QMap>
#include <QTcpServer>
#include <QVector>

#include "coordinator.h"
#include "renderer/scene.h"

namespace film {
class Server : public QObject {
  Q_OBJECT

 public:
  Server();
  void listen(QHostAddress addr, quint16 port);
  void setScene(Scene* scenePtr);
  void sendSceneToWorkers();

 private slots:
  void acceptConnection();
  void read();
  void handleFilmJobResult(QDataStream* dataStreamPtr);
  void handleRegisterGUI(QTcpSocket* socket);
  void handleRegisterWorker(QTcpSocket* socket);
  void handleFrame(Film* filmPtr);
  void updateScene();

 signals:
  void filmJobResult(QDataStream* dataStream);
  void registerGUI(QTcpSocket* socket);
  void registerWorker(QTcpSocket* socket);

 private:
  QTcpServer tcpServer;
  QMap<QTcpSocket*, QDataStream*> sockets;
  QVector<QTcpSocket*> workers;
  QTcpSocket* gui;
  Coordinator coordinator;
  Scene* scenePtr;

  void sendFilmJob(QDataStream* dataStreamPtr);
};
}

#endif
