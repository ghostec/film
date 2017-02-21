#include <uv.h>

namespace server {

void after_read(uv_write_t* req, int status);
void on_read(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);
void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
void on_new_connection(uv_stream_t *server, int status);

}
