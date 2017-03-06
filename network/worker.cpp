#include <QtDebug>

#include "film_job_t.h"
#include "worker.h"

namespace film {
Worker::Worker() {
  connect(this, SIGNAL(filmJob()), this, SLOT(handleFilmJob()),
          Qt::QueuedConnection);
}

void Worker::connectionCb() {
  dataStream.startTransaction();
  dataStream << message_t::REGISTER_WORKER;
  dataStream.commitTransaction();
}

void Worker::handleMessage(const message_t messageType) {
  switch (messageType) {
    case message_t::FILM_JOB:
      return emit filmJob();
  }
}

void Worker::handleFilmJob() {
  film_job_t job;
  dataStream >> job;

  if (!dataStream.commitTransaction()) return;
}
}

#include "moc_worker.cpp"
