#include <uv.h>
#include <uv_msg_framing.h>
#include <cstdio>
#include <cstdlib>
#include "server.h"

namespace film { namespace network {

Server::Server() {}
Server::~Server() {}

int Server::start() {
  auto loop = uv_default_loop();

  uv_tcp_t server;
  uv_tcp_init(loop, &server);

  sockaddr_in addr;
  uv_ip4_addr("0.0.0.0", 3000, &addr);

  uv_tcp_bind(&server, (const struct sockaddr*) &addr, 0);
  server.data = this;
  int r = uv_listen((uv_stream_t*) &server, SOMAXCONN, connection_cb);
  if (r) {
    fprintf(stderr, "Listen error %s\n", uv_strerror(r));
    return 1;
  }

  return uv_run(loop, UV_RUN_DEFAULT);
}

void Server::connection_cb(uv_stream_t *server, int status) {
  if (status < 0) {
    fprintf(stderr, "New connection error %s\n", uv_strerror(status));
    abort();
  }

  auto loop = uv_default_loop();
  uv_msg_t* client = new uv_msg_t();
  uv_msg_init(loop, client, UV_TCP);
  if (uv_accept(server, (uv_stream_t*) client) == 0) {
    client->data = server->data;
    uv_msg_read_start((uv_msg_t*) client, alloc_cb, msg_read_cb, delete_buf_cb);
  }
  else {
    uv_close((uv_handle_t*) client, NULL);
  }
}

} }