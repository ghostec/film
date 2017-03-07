#ifndef NETWORK_WORKERH
#define NETWORK_WORKERH

#include "film_job_t.h"
#include "network/client.h"
#include "renderer/scene.h"

namespace film {
class Worker : public Client {
  Q_OBJECT

 public:
  Worker();
  void setScene(Scene* scenePtr);

 private slots:
  void handleFilmJob();

 signals:
  void filmJob();

 private:
  Scene* scenePtr;

  virtual void connectionCb();
  virtual void handleMessage(const message_t messageType);
  void sendFilmJobResult(Film* filmPtr, film_job_t filmJob);
};
}

#endif
