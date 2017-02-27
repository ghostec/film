#ifndef RENDERER_WORKERH
#define RENDERER_WORKERH

#include "film-network/client.h"

namespace film { namespace renderer {

struct Job {
  int row_start, row_end;
};

class Worker {
public:
  static Worker* create(const char* ip, int port);
  void work(Job job);
  void handle_message(network::Message message);
  network::Client* get_network_client();
private:
  network::Client* network_client;

  Worker(const char* ip, int port);
};

} }

#endif
