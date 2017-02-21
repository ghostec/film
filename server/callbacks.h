#include <uv.h>

namespace server {

void write_cb(uv_write_t* req, int status);
void read_cb(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);
void alloc_cb(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
void connection_cb(uv_stream_t *server, int status);

}
