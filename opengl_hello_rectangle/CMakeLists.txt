cmake_minimum_required(VERSION 3.6)
project(open_gl_glad_test)

set(CMAKE_CXX_STANDARD 11)
find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(include)

link_libraries(${OPENGL_LIBRARY})
link_libraries(${X11_LIBRARIES})
link_libraries(${GLEW_LIBRARIES})

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${X11_INCLUDE_DIR})
include_directories(${GLEW_LIBRARIES})

add_executable(open_gl_glad_test src/main.cpp src/JarvisRenderer.cpp)
