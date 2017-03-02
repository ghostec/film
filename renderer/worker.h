#ifndef RENDERER_WORKERH
#define RENDERER_WORKERH

#include <mutex>
#include "renderer.h"
#include "film-network/client.h"

namespace film { namespace renderer {

class Worker {
public:
  static Worker* create(const char* ip, int port);
  void work(uv_stream_t* handle, size_t first_row, size_t last_row, size_t film_width, size_t film_height);
  network::Client* get_network_client();
private:
  network::Client* network_client;
  Renderer renderer;

  Worker(const char* ip, int port);
  void register_handlers();
  void handle_render_job_message(network::Message message);
};

} }

#endif
