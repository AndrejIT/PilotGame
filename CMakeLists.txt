cmake_minimum_required (VERSION 3.10)

project(CppTesting VERSION 1.0)


# some vierd workaround https://stackoverflow.com/questions/34143265/undefined-reference-to-symbol-pthread-createglibc-2-2-5
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SOURCES
    src/Main.cpp
    src/MyMain.h
)

add_executable(CppTesting ${SOURCES})

find_package(sdl2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(CppTesting ${SDL2_LIBRARIES})
