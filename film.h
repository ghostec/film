#ifndef FILMH
#define FILMH

#include "server/server.h"

namespace film {

class Film {
public:
  Film();
  ~Film();
  void set_server(server::Server* server);
private:
  server::Server* server;

  void handle_message(server::Message message);
};

}

#endif
