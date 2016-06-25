cmake_minimum_required(VERSION 2.6)

set(BALL_DIR "~/ball/build/cmake")

find_package(BALL REQUIRED)

include_directories(${BALL_INCLUDE_DIRS})

add_definitions(-std=gnu++11)

link_libraries(~/git/ball/build/lib/libBALL.so)

add_executable(MDwithBALL molecularDynamics.cpp)
