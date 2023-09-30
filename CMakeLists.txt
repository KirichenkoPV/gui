cmake_minimum_required(VERSION 3.10)
project(gui VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 17)


add_executable(gui 
    lol.cpp
)


add_subdirectory(external/glfw)
add_subdirectory(external/imgui-w)
add_subdirectory(external/implot-w)

target_link_libraries(gui PRIVATE imgui)
target_link_libraries(gui PRIVATE implot)