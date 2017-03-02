#ifndef NETWORK_CONSTANTSH
#define NETWORK_CONSTANTSH

#include <string>
#include <regex>

namespace film { namespace network {

static const std::string WORKER = "WORKER";
static const std::string CLIENT = "CLIENT";
static const std::regex REGEX_RENDER_JOB("RENDER_JOB (-?[0-9]+) (-?[0-9]+) ([0-9]+)");
static const std::regex REGEX_RENDER_JOB_RESULT("RENDER_JOB_RESULT ([0-9]+) ([0-9]+) ([0-9]+)");
static constexpr const char* const CONNECTED_MESSAGE = "CONNECTED";
static constexpr const char* const REGISTER_WORKER_MESSAGE = "WORKER";
static constexpr const char* const REGISTER_CLIENT_MESSAGE = "CLIENT";
static constexpr const char* const RENDER_JOB_MESSAGE = "RENDER_JOB";
static constexpr const char* const RENDER_JOB_RESULT_MESSAGE = "RENDER_JOB_RESULT";
static constexpr const char* const FRAME_MESSAGE = "FRAME";

} }

#endif
