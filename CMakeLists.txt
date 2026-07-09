cmake_minimum_required(VERSION 3.15)
project(Satellite_constellation_simulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SCS "src/main.cpp" "src/Simulation.cpp" "include/Simulation.h" "include/Components.h" "src/Systems.cpp" "include/Systems.h")

target_include_directories(SCS PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/extern
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/raylib/include
)


add_library(raylib_imported STATIC IMPORTED)
set_target_properties(raylib_imported PROPERTIES IMPORTED_LOCATION "D:/Project/Satellite constellation simulation/Satellite constellation simulation/extern/raylib-6.0_win64_msvc16/lib/raylib.lib")


include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG        v1.90.8
)
FetchContent_MakeAvailable(imgui)

file(GLOB IMGUI_SOURCES "${imgui_SOURCE_DIR}/*.cpp")
add_library(imgui_lib STATIC ${IMGUI_SOURCES})

target_include_directories(imgui_lib PUBLIC ${imgui_SOURCE_DIR})

FetchContent_Declare(
 perturb
 GIT_REPOSITORY "https://github.com/gunvirranu/perturb"
    GIT_TAG 5723e50a54d438876b7a02e02a326e30b51ead4c 
)
FetchContent_MakeAvailable(perturb)



target_link_libraries(SCS PRIVATE 
    raylib_imported
    imgui_lib
    perturb
)