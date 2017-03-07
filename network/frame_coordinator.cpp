#include "frame_coordinator.h"

namespace film {
FrameCoordinator::FrameCoordinator() {}
FrameCoordinator::~FrameCoordinator() {}

void FrameCoordinator::filmJobSent(quint16 frameId) {
  mutex.lock();
  auto& frame = frames[frameId];
  frame.jobsTotal += 1;
  mutex.unlock();
}

void FrameCoordinator::filmJobReceived(film_job_t job,
                                       std::vector<rgb> pixels) {
  mutex.lock();
  auto& frame = frames[job.frameId];
  frame.jobsReceived += 1;
  frame.filmPtr->setBlock(std::move(pixels), job.width * job.firstRow);
  mutex.unlock();
}

void FrameCoordinator::hasSentAllJobs(quint16 frameId) {
  mutex.lock();
  frames[frameId].hasSentAllJobs = true;
  mutex.unlock();
}

bool FrameCoordinator::frameDone(quint16 frameId) {
  mutex.lock();
  auto& frame = frames[frameId];
  auto ret = ((frame.hasSentAllJobs && (frame.jobsTotal == frame.jobsReceived))
                  ? true
                  : false);
  mutex.unlock();
  return ret;
}

Film* FrameCoordinator::getFilm(quint16 frameId) {
  return frames[frameId].filmPtr;
}
}
