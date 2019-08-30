cmake_minimum_required(VERSION 3.13)
project(Systems_Programming)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)


