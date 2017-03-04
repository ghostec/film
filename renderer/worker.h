#ifndef RENDERER_WORKERH
#define RENDERER_WORKERH

#include <uv.h>
#include "renderer.h"
#include "film-network/client.h"

namespace film { namespace renderer {

struct RenderJob {
  size_t frame_id, first_row, last_row;
  size_t width, height;
};

class Worker {
public:
  static Worker* create(const char* ip, int port);
  network::Client* get_network_client();
  void loop();
private:
  network::Client* network_client;
  uv_stream_t* server;
  RenderJob render_job;
  bool has_render_job;
  Renderer renderer;

  Worker(const char* ip, int port);
  void register_handlers();
  void handle_render_job_message(network::Message message);
  void set_render_job(RenderJob render_job);
  void send_job_result();
};

} }

#endif
