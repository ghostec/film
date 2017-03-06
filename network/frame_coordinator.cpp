#include "frame_coordinator.h"

namespace film {
FrameCoordinator::FrameCoordinator() {}
FrameCoordinator::~FrameCoordinator() {}

void FrameCoordinator::jobSent(quint16 frameId) {
  mutex.lock();
  auto& frame = frames[frameId];
  frame.jobsTotal += 1;
  mutex.unlock();
}

void FrameCoordinator::jobReceived(quint16 frameId) {
  mutex.lock();
  auto& frame = frames[frameId];
  frame.jobsReceived += 1;
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
  return frames[frameId].film;
}
}
