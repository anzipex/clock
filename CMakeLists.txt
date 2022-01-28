cmake_minimum_required(VERSION 3.13)
project(clock)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)

add_executable(clock main.cpp pngutil.cpp textures.cpp Clock.cpp)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
find_package(PNG REQUIRED)

add_dependencies(clock OpenGL::OpenGL)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${PNG_INCLUDE_DIR})

target_link_libraries(clock ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${PNG_LIBRARY})
