#ifndef SERVER_MESSAGEH
#define SERVER_MESSAGEH

#include <uv.h>

namespace film { namespace server {

struct Message {
  uv_stream_t* handle;
  const char* data;
  size_t length;
};

} }

#endif
