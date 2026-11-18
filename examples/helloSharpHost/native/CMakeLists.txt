set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE HELLO_SHARPHOST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(helloSharpHost ${HELLO_SHARPHOST_SOURCES})

target_include_directories(helloSharpHost PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(helloSharpHost
        PRIVATE
        sharphost
)

