#ifndef NETWORK_CONSTANTSH
#define NETWORK_CONSTANTSH

#include <string>

namespace film { namespace network {

static const std::string WORKER = "WORKER";
static const std::string CLIENT = "CLIENT";
static constexpr const char* const CONNECTED_MESSAGE = "CONNECTED";
static constexpr const char* const REGISTER_WORKER_MESSAGE = "WORKER";

} }

#endif
