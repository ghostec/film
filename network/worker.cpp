#include <QVector>
#include <QtDebug>

#include "qdatastream.h"
#include "worker.h"

namespace film {
Worker::Worker() : scenePtr(nullptr) {
  connect(this, SIGNAL(filmJob()), this, SLOT(handleFilmJob()),
          Qt::QueuedConnection);
}

void Worker::setScene(Scene* scenePtr) { this->scenePtr = scenePtr; }

void Worker::connectionCb() { dataStream << message_t::REGISTER_WORKER; }

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

  auto filmPtr =
      new Film((size_t)job.width, (size_t)job.lastRow - job.firstRow + 1);
  scenePtr->render(filmPtr, job.firstRow, job.lastRow, job.width, job.height);
  sendFilmJobResult(filmPtr, job);
}

void Worker::sendFilmJobResult(Film* filmPtr, film_job_t filmJob) {
  dataStream << message_t::FILM_JOB_RESULT << filmJob;
  dataStream << QVector<rgb>::fromStdVector(filmPtr->getPixels());
}
}

#include "moc_worker.cpp"
