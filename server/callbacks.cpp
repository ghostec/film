#include <stdio.h>
#include <stdlib.h>
#include "callbacks.h"

namespace server {

void after_read(uv_write_t* req, int status) {
  if(status < 0) abort();
  if(req && req->data) free(req->data);
  if(req) free(req);
}

void on_read(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
  if (nread <= 0) return;
  uv_write_t* req;
  if (!(req = (uv_write_t*) malloc(sizeof(uv_write_t)))) abort();
  req->data = buf->base;
  uv_write(req, handle, buf, 1, after_read);
}

void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
  *buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

void on_new_connection(uv_stream_t *server, int status) {
  if (status < 0) {
    fprintf(stderr, "New connection error %s\n", uv_strerror(status));
    abort();
  }

  auto loop = uv_default_loop();
  uv_tcp_t* client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, client);
  if (uv_accept(server, (uv_stream_t*) client) == 0) {
    uv_read_start((uv_stream_t*) client, alloc_buffer, on_read);
  }
  else {
    uv_close((uv_handle_t*) client, NULL);
  }
}

}
