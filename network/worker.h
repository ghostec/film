#ifndef WORKERH
#define WORKERH

#include "network/client.h"

class Worker : public Client {
 public:
  Worker();

 private:
  virtual void connectionCb();
  virtual void handleMessage(const message_t messageType);
};

#endif
