#ifndef NETWORK_COORDINATORH
#define NETWORK_COORDINATORH

#include <mutex>
#include "renderer/film.h"

namespace film { namespace network {

struct RenderJob {
  size_t frame_id;
  int first_row, last_row;
};

class Coordinator {
public:
  Coordinator();
  ~Coordinator();
  void set_film(renderer::Film* film);
  renderer::Film* get_film();
  RenderJob next_job();
  size_t get_frame_id();
private:
  renderer::Film* film;
  int job_size;
  int current_row;
  size_t frame_id;
  std::mutex m_current_row;
};

} }

#endif
