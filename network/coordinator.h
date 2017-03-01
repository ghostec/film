#ifndef NETWORK_COORDINATORH
#define NETWORK_COORDINATORH

#include <mutex>
#include "renderer/film.h"

namespace film { namespace network {

struct RenderJob {
  int first_row, last_row;
};

class Coordinator {
public:
  Coordinator();
  ~Coordinator();
  void set_film(renderer::Film* film);
  renderer::Film* get_film();
  RenderJob next_job();
private:
  renderer::Film* film;
  int job_size;
  int current_row;
  std::mutex m_current_row;
};

} }

#endif
