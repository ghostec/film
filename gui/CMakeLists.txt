project(GUI)
set(SOURCE_FILES gui.cpp)
add_library(GUI ${SOURCE_FILES})
target_link_libraries(GUI Qt5::Network Qt5::Widgets)
