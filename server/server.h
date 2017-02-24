#ifndef SERVER_SERVERH
#define SERVER_SERVERH

#include <uv.h>
#include <vector>
#include <functional>
#include <mutex>
#include "message.h"

namespace film { namespace server {

typedef std::function<void(Message message)> Observer;

class Server {
public:
  Server();
  ~Server();
  int start();
  void register_observer(Observer observer);
private:
  std::vector<Observer> observers;

  void notify_observers(Message message);
  static void delete_buf_cb(uv_handle_t* handle, void* ptr);
  static void msg_read_cb(uv_stream_t *handle, void *msg, int size);
  static void read_cb(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);
  static void alloc_cb(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
  static void connection_cb(uv_stream_t *server, int status);
};

} }

#endif
