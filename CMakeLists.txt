cmake_minimum_required(VERSION 2.8.4)
project(inotify_daemon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

set(SOURCE_FILES main.cpp daemon/inotify-cxx.cpp daemon/sync-daemon.cpp daemon/basedaemon.cpp daemon/logger.cpp)
add_executable(inotify_daemon ${SOURCE_FILES})