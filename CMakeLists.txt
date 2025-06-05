cmake_minimum_required(VERSION 3.10)
project(
    simulator
    VERSION 1.0
    LANGUAGES CXX
) # project name

# TODO:
# Raylib proper fetching
# RayGUI proper fetching

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.h")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include/")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

# add_library(raylib PRIVATE "${CMAKE_CURRENT_LIST_DIR}/lib/libraylib.a")
target_link_libraries(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/lib/libraylib.a")

target_compile_options(${PROJECT_NAME} PRIVATE
-Iinclude 
-Llib 
-lraylib 
# -DRAYGUI_IMPLEMENTATION
-lGL 
-lm 
-lpthread 
-ldl 
-lrt 
-lX11 
-std=c++17
)
