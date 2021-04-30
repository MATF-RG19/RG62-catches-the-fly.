cmake_minimum_required(VERSION 3.13.4cd)
project(catches_the_fly VERSION 1.0.0)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

#set(CFILE src/image.c)
#SET_SOURCE_FILES_PROPERTIES(${CFILE} PROPERTIES LANGUAGE CXX)

file(GLOB_RECURSE CFILES "${CMAKE_SOURCE_DIR}/*.c")
SET_SOURCE_FILES_PROPERTIES(${CFILES} PROPERTIES LANGUAGE CXX)

#SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
#SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
#SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

#SET(CMAKE_CXX_FLAGS "-g")
#SET(CMAKE_C_FLAGS "-g")

add_library(
    texture_loader
    STATIC
    headers/image.h 
    src/image.c
)

set(HEADERS
    headers/spider.hpp
    headers/enemy.hpp
    headers/platform.hpp
)

set(SOURCES
    src/catch_the_fly.cpp
    src/spider.cpp
    src/enemy.cpp
    src/platform.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} texture_loader)