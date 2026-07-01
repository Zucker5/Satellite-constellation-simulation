cmake_minimum_required(VERSION 3.15)
project(Satellite_constellation_simulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SCS src/main.cpp)

target_include_directories(SCS PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/extern
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/raylib/include
)


link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/raylib/lib)


include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG        v1.90.8
)
FetchContent_MakeAvailable(imgui)





target_link_libraries(SCS PRIVATE 
    raylib
    imgui 
)