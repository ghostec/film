#ifndef CLIENT_H
#define CLIENT_H

#include <QDataStream>
#include <QTcpSocket>

#include "message_t.h"

class QTcpSocket;

class Client : public QObject {
  Q_OBJECT

 public:
  Client();
  void connectToHost(const QHostAddress addr, const quint16 port);

 protected slots:
  void read();

 protected:
  QTcpSocket tcpSocket;
  QDataStream dataStream;

 private:
  virtual void connectionCb() = 0;
  virtual void handleMessage(const message_t messageType) = 0;
};

#endif
