#include "coordinator.h"

namespace film {
Coordinator::Coordinator(size_t filmWidth, size_t filmHeight)
    : filmWidth(filmWidth),
      filmHeight(filmHeight),
      filmJobCoordinator(filmWidth, filmHeight) {}

Coordinator::~Coordinator() {}

film_job_t Coordinator::nextJob() {
  // Get Job and create new frame if necessary
  // Another function to update frame status on FrameCoordinator

  auto job = filmJobCoordinator.nextJob();
  if (job.lastRow == filmHeight - 1) {  // last job for that frame
    frameCoordinator.hasSentAllJobs(job.frameId);
  }
  frameCoordinator.jobSent(job.frameId);
  return job;
}

void Coordinator::jobReceived(quint16 frameId) {
  frameCoordinator.jobReceived(frameId);
  if (frameCoordinator.frameDone(frameId)) {
    // emit frameDone signal to Server sendFrame slot
  }
}
}
