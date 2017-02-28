#ifndef RENDERER_WORKERH
#define RENDERER_WORKERH

#include "renderer.h"
#include "film-network/client.h"

namespace film { namespace renderer {

struct Job {
  int row_start, row_end;
};

class Worker {
public:
  static Worker* create(const char* ip, int port);
  void work(Job job);
  network::Client* get_network_client();
private:
  network::Client* network_client;
  Renderer renderer;

  Worker(const char* ip, int port);
  void register_handlers();
  void handle_set_film_message(network::Message message);
};

} }

#endif
