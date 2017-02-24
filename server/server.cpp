#include <uv.h>
#include <uv_msg_framing.h>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "server.h"
#include "write.h"

namespace film { namespace server {

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

void Server::register_observer(Observer observer) {
  observers.push_back(observer);
}

// Private members

void Server::notify_observers(Message message) {
  auto loop = uv_default_loop();

  struct ObserverMessage { Observer observer; Message message; };

  for(const auto& observer : observers) {
    uv_work_t* req = new uv_work_t();

    req->data = (void*) new ObserverMessage {
      .observer = observer,
      .message = message
    };

    uv_queue_work(loop, req,
      [](uv_work_t* req) -> void {
        auto om = (ObserverMessage*) req->data;
        om->observer(om->message);
      },
      [](uv_work_t* req, int status) -> void {
        delete (ObserverMessage*) req->data;
        delete req;
    });
  }
}

void Server::delete_buf_cb(uv_handle_t* handle, void* ptr) {
   delete ptr;
}

void Server::msg_read_cb(uv_stream_t *handle, void *msg, int size) {
  if (size <= 0) return;

  printf("new message here (%d bytes): %s\n", size, (char*)msg);
  write({ .handle = handle, .data = (char*) msg, .length = (size_t) size });
}

void Server::read_cb(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
  if (nread <= 0) return;

  std::string message_data;
  std::istringstream iss(buf->base);
  while (std::getline(iss, message_data, '\r')) {
    if (message_data.empty()) continue;
    auto data = new char[message_data.size() + 1];
    memcpy(data, message_data.c_str(), message_data.size());
    ((Server*)handle->data)->notify_observers({ handle, data });
  }

  delete buf->base;
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
