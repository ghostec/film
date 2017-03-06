#include "worker.h"
#include <QtDebug>

Worker::Worker() {}

void Worker::connectionCb() {
  dataStream.startTransaction();
  dataStream << message_t::REGISTER_WORKER;
  dataStream.commitTransaction();
}

void Worker::handleMessage(const message_t messageType) {
  if (!dataStream.commitTransaction()) return;

  switch (messageType) {
    case message_t::FILM_JOB:
      qDebug() << "FILM_JOB";
  }
}
