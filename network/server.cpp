#include <QVector>
#include <QtDebug>
#include <QtNetwork>
#include <vector>

#include "message_t.h"
#include "qdatastream.h"
#include "server.h"

namespace film {
Server::Server() : coordinator(800, 600) {
  connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()),
          Qt::QueuedConnection);
  connect(this, SIGNAL(filmJobResult(QDataStream*)), this,
          SLOT(handleFilmJobResult(QDataStream*)), Qt::QueuedConnection);
  connect(this, SIGNAL(registerGUI(QTcpSocket*)), this,
          SLOT(handleRegisterGUI(QTcpSocket*)), Qt::QueuedConnection);
  connect(this, SIGNAL(registerWorker(QTcpSocket*)), this,
          SLOT(handleRegisterWorker(QTcpSocket*)), Qt::QueuedConnection);
}

void Server::listen(QHostAddress addr, quint16 port) {
  tcpServer.listen(addr, port);
}

void Server::acceptConnection() {
  auto socket = tcpServer.nextPendingConnection();
  connect(socket, SIGNAL(readyRead()), this, SLOT(read()),
          Qt::QueuedConnection);

  // save QDataStream object to QMap `clients` member
  auto dataStreamPtr = new QDataStream(socket);
  dataStreamPtr->setVersion(QDataStream::Qt_4_0);
  sockets[socket] = dataStreamPtr;
}

void Server::read() {
  auto socketPtr = (QTcpSocket*)QObject::sender();
  auto dataStreamPtr = sockets[socketPtr];

  dataStreamPtr->startTransaction();
  // remember to commitTransaction at each handler

  message_t messageType;
  (*dataStreamPtr) >> messageType;

  switch (messageType) {
    case message_t::REGISTER_WORKER:
      return emit registerWorker(socketPtr);
    case message_t::REGISTER_GUI:
      return emit registerGUI(socketPtr);
    case message_t::FILM_JOB_RESULT:
      return emit filmJobResult(dataStreamPtr);
  }
}

void Server::handleRegisterWorker(QTcpSocket* socket) {
  if (!sockets[socket]->commitTransaction()) return;
  workers.append(socket);
  sendFilmJob(sockets[socket]);
}

void Server::handleRegisterGUI(QTcpSocket* socket) { gui = socket; }

void Server::handleFilmJobResult(QDataStream* dataStreamPtr) {
  film_job_t job;
  QVector<rgb> qPixels;

  (*dataStreamPtr) >> job >> qPixels;

  if (!dataStreamPtr->commitTransaction()) return;

  sendFilmJob(dataStreamPtr);
}

void Server::sendFilmJob(QDataStream* dataStreamPtr) {
  (*dataStreamPtr).startTransaction();
  (*dataStreamPtr) << message_t::FILM_JOB;
  (*dataStreamPtr) << coordinator.nextJob();
  (*dataStreamPtr).commitTransaction();
}
}

#include "moc_server.cpp"
