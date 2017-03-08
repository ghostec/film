#include <Magick++.h>
#include <QByteArray>
#include <QVector>
#include <QtDebug>
#include <QtNetwork>
#include <utility>
#include <vector>

#include "message_t.h"
#include "qdatastream.h"
#include "server.h"

namespace film {
Server::Server() : coordinator(800, 600), gui(nullptr) {
  connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()),
          Qt::QueuedConnection);
  connect(&coordinator, SIGNAL(frameDone(Film*)), this,
          SLOT(handleFrame(Film*)), Qt::QueuedConnection);
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

void Server::setScene(Scene* scenePtr) { this->scenePtr = scenePtr; }

void Server::sendSceneToWorkers() {
  QByteArray bytes;
  QDataStream stream(&bytes, QIODevice::WriteOnly);
  stream.setVersion(QDataStream::Qt_4_0);
  stream << scenePtr;

  for (auto& socket : sockets.keys()) {
    *(sockets.value(socket)) << bytes;
  }
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

  coordinator.filmJobReceived(job, std::move(qPixels.toStdVector()));
  sendFilmJob(dataStreamPtr);
}

void Server::handleFrame(Film* filmPtr) {
  if (!gui) return;

  QDataStream out(gui);
  out.setVersion(QDataStream::Qt_4_0);

  Magick::Image im(filmPtr->getWidth(), filmPtr->getHeight(), "RGB",
                   Magick::StorageType::FloatPixel,
                   (void*)&filmPtr->getPixels()[0]);
  im.magick("JPEG");

  Magick::Blob jpeg;
  im.write(&jpeg);

  QByteArray bytes((char*)jpeg.data(), jpeg.length());
  out << message_t::FRAME << bytes;
}

void Server::sendFilmJob(QDataStream* dataStreamPtr) {
  (*dataStreamPtr) << message_t::FILM_JOB;
  (*dataStreamPtr) << coordinator.nextJob();
}
}

#include "moc_server.cpp"
