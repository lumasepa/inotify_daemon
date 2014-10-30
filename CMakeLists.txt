cmake_minimum_required(VERSION 2.8.4)
project(inotify_daemon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

set(SOURCE_FILES src/main.cpp src/daemon/inotify/inotify-cxx.cpp src/daemon/sync-daemon.cpp src/daemon/basedaemon.cpp src/daemon/logger/logger.cpp src/daemon/options/options.cpp)
add_executable(inotify_daemon ${SOURCE_FILES})