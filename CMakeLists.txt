cmake_minimum_required(VERSION 3.10)
project(mpc)

set(CMAKE_CXX_STANDARD 14)

IF(APPLE)
find_package(LLVM REQUIRED CONFIG)
include_directories(/usr/local/opt/llvm/include)
string(APPEND CMAKE_CXX_FLAGS " -Wno-c++11-narrowing")
ENDIF(APPLE)

add_subdirectory(src)
add_subdirectory(test)
