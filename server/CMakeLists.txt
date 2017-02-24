project(Server)

set(UV_MSG_FRAMING_DIR ./deps/libuv_message_framing)
set(ServerFiles server.cpp write.cpp ${UV_MSG_FRAMING_DIR}/uv_msg_framing.c)

include_directories(${UV_MSG_FRAMING_DIR})

add_library(Server ${ServerFiles})

include(${CMAKE_CURRENT_SOURCE_DIR}/FindLibUV.cmake)
target_link_libraries(Server uv)
