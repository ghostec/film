#include <uv.h>
#include "server.h"
#include "callbacks.h"

namespace server {

Server::Server() {}
Server::~Server() {}

int Server::start() {
  auto loop = uv_default_loop();

  uv_tcp_t server;
  uv_tcp_init(loop, &server);

  sockaddr_in addr;
  uv_ip4_addr("0.0.0.0", 3000, &addr);

  uv_tcp_bind(&server, (const struct sockaddr*) &addr, 0);
  int r = uv_listen((uv_stream_t*) &server, SOMAXCONN, on_new_connection);
  if (r) {
    fprintf(stderr, "Listen error %s\n", uv_strerror(r));
    return 1;
  }

  return uv_run(loop, UV_RUN_DEFAULT);
}

}
