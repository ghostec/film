#ifndef NETWORK_WORKERH
#define NETWORK_WORKERH

#include "network/client.h"

namespace film {
class Worker : public Client {
  Q_OBJECT

 public:
  Worker();

 private slots:
  void handleFilmJob();

 signals:
  void filmJob();

 private:
  virtual void connectionCb();
  virtual void handleMessage(const message_t messageType);
};
}

#endif
