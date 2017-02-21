#include <uv.h>
#include <string>

namespace server {

struct Message {
  uv_stream_t* handle;
  std::string data;
};

class Server {
public:
  Server();
  ~Server();
  int start();
  void write(Message message);
private:
};

};
