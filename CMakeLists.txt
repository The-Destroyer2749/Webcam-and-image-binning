cmake_minimum_required(VERSION 3.31)
project(webcamToAscii)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
# find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

# Include ImGui files
include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        # ${OPENGL_INCLUDE_DIR}
        include/imgui
        include/imgui/backends
)

# Add your source files along with ImGui and its backends
add_executable(webcamToAscii
        src/main.cpp
        src/init.cpp
        include/variables.h
        include/helper_functions.h
        include/imgui/imgui.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_widgets.cpp
        include/imgui/imgui_tables.cpp
        # imgui/imgui_demo.cpp
        include/imgui/backends/imgui_impl_sdl2.cpp
        include/imgui/backends/imgui_impl_sdlrenderer2.cpp
        # imgui/backends/imgui_impl_opengl3.cpp
)

# Link necessary libraries
target_link_libraries(webcamToAscii
        ${OpenCV_LIBS}
        ${SDL2_LIBRARIES}
        # ${OPENGL_LIBRARIES}
)
