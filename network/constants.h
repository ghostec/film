#ifndef NETWORK_CONSTANTSH
#define NETWORK_CONSTANTSH

#include <string>
#include <regex>

namespace film { namespace network {

static const std::string WORKER = "WORKER";
static const std::string CLIENT = "CLIENT";
static const std::regex REGEX_SET_FILM("SET_FILM ([0-9]+) ([0-9]+)");
static constexpr const char* const CONNECTED_MESSAGE = "CONNECTED";
static constexpr const char* const REGISTER_WORKER_MESSAGE = "WORKER";
static constexpr const char* const REGISTER_CLIENT_MESSAGE = "CLIENT";
static constexpr const char* const SET_FILM_MESSAGE = "SET_FILM";

} }

#endif
