#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "callbacks.h"

namespace server {

void write_cb(uv_write_t* req, int status) {
  if(status < 0) abort();
}

void read_cb(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
  if (nread <= 0) return;
  uv_write_t req;
  uv_write(&req, handle, buf, 1, write_cb);
}

void alloc_cb(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
  *buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

void connection_cb(uv_stream_t *server, int status) {
  if (status < 0) {
    fprintf(stderr, "New connection error %s\n", uv_strerror(status));
    abort();
  }

  auto loop = uv_default_loop();
  uv_tcp_t* client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, client);
  if (uv_accept(server, (uv_stream_t*) client) == 0) {
    uv_read_start((uv_stream_t*) client, alloc_cb, read_cb);
  }
  else {
    uv_close((uv_handle_t*) client, NULL);
  }
}

}
