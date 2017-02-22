#include <uv.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "server.h"
#include "callbacks.h"

namespace server {

void test(Message message) {
  std::cout << "asdfasdf "<< message.data << std::endl;
}

Server::Server() {}
Server::~Server() {}

int Server::start() {
  auto loop = uv_default_loop();

  register_observer(test);

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

void Server::register_observer(Observer observer) {
  observers.push_back(observer);
}

void Server::write(Message message) {
  return;
}


void Server::notify_observers(Message message) {
  for(const auto& observer : observers) observer(message);
}

void Server::write_cb(uv_write_t* req, int status) {
  if(status < 0) abort();
}

void Server::read_cb(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
  if (nread <= 0) return;

  std::string message_data;
  std::istringstream iss(buf->base);
  while (std::getline(iss, message_data, '\r')) {
    if (message_data.empty()) continue;
    ((Server*)handle->data)->notify_observers({ handle, message_data });
  }

  uv_write_t req;
  uv_write(&req, handle, buf, 1, write_cb);
}

void Server::alloc_cb(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
  *buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

void Server::connection_cb(uv_stream_t *server, int status) {
  if (status < 0) {
    fprintf(stderr, "New connection error %s\n", uv_strerror(status));
    abort();
  }

  auto loop = uv_default_loop();
  uv_tcp_t* client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, client);
  if (uv_accept(server, (uv_stream_t*) client) == 0) {
    client->data = server->data;
    uv_read_start((uv_stream_t*) client, alloc_cb, read_cb);
  }
  else {
    uv_close((uv_handle_t*) client, NULL);
  }
}

}
