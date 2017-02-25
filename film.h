#ifndef FILMH
#define FILMH

#include "film-network/server.h"

namespace film {

class Film {
public:
  Film();
  ~Film();
  void set_server(network::Server* server);
private:
  network::Server* server;

  void handle_message(network::Message message);
};

}

#endif
