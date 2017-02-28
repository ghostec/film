project(Renderer)
set(RendererFiles worker.cpp)

add_subdirectory(math)

set(LIBRARIES RendererMath)

add_library(Renderer ${RendererFiles})
target_link_libraries(Renderer ${LIBRARIES})
