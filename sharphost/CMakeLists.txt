cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(sharphost)

file(GLOB_RECURSE SHARPHOST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(sharphost ${SHARPHOST_SOURCES})

target_include_directories(sharphost
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    private
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(sharphost PUBLIC
    nethost
)