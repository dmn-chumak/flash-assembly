cmake_minimum_required(VERSION 3.0)
project(flash)

set(CMAKE_CXX_STANDARD      14)
set(CMAKE_CXX_FLAGS         -O3)
set(CMAKE_SYSTEM_NAME       Flash)
set(CMAKE_SYSTEM_VERSION    v0.0.1alpha)
set(CMAKE_CROSSCOMPILING    1)

file(GLOB_RECURSE SOURCE_FILES_GENERIC src/flash/generic/*.cpp)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
list(REMOVE_ITEM SOURCE_FILES ${SOURCE_FILES_GENERIC})
message(STATUS "Source files: " ${SOURCE_FILES})

add_definitions(-DWASM -DWASM_64)
include_directories(src)
add_executable(flash ${SOURCE_FILES})
