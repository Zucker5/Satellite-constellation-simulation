cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(Satellite_constellation_simulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(SCS src/main.cpp)