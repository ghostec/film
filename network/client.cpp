#include <QtDebug>
#include <QtNetwork>

#include "client.h"

Client::Client() {
  dataStream.setDevice(&tcpSocket);
  dataStream.setVersion(QDataStream::Qt_4_0);

  connect(&tcpSocket, &QIODevice::readyRead, this, &Client::read);
}

void Client::connectToHost(QHostAddress addr, quint16 port) {
  tcpSocket.connectToHost(addr, port);
  connectionCb();
}

void Client::read() {
  dataStream.startTransaction();

  message_t messageType;
  dataStream >> messageType;

  handleMessage(messageType);
}

#include "moc_client.cpp"
