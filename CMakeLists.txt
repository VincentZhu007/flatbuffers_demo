cmake_minimum_required(VERSION 3.14)

project(flatbuffers_demo
        LANGUAGES CXX
        VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(tests)
