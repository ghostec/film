#include <QtDebug>
#include <QtNetwork>

#include "network/message_t.h"
#include "server.h"

namespace film {
Server::Server() : coordinator(800, 600) {
  connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
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
  connect(socket, SIGNAL(readyRead()), this, SLOT(read()));

  // save QDataStream object to QMap `clients` member
  auto dataStreamPtr = new QDataStream(socket);
  dataStreamPtr->setVersion(QDataStream::Qt_4_0);
  sockets[socket] = dataStreamPtr;
}

void Server::read() {
  auto socketPtr = (QTcpSocket*)QObject::sender();
  auto dataStreamPtr = sockets[socketPtr];

  dataStreamPtr->startTransaction();

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
  workers.append(socket);
  sendFilmJob(socket);
}

void Server::handleRegisterGUI(QTcpSocket* socket) { gui = socket; }

void Server::handleFilmJobResult(QDataStream* dataStreamPtr) {
  film_job_t job;
  (*dataStreamPtr) >> job;

  if (!dataStreamPtr->commitTransaction()) return;

  qDebug() << "[Server] New message:";
  qDebug() << job.width;
}

void Server::sendFilmJob(QTcpSocket* socket) {
  auto dataStream = sockets[socket];
  (*dataStream).startTransaction();
  (*dataStream) << message_t::FILM_JOB;
  (*dataStream) << coordinator.nextJob();
  (*dataStream).commitTransaction();
}
}

#include "moc_server.cpp"
