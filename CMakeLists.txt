cmake_minimum_required(VERSION 3.9)
project(a4tasks)

set(CMAKE_CXX_STANDARD 17)
file(GLOB a4tasks_sources "src/*.cpp")

add_executable(a4tasks ${a4tasks_sources})

target_link_libraries(a4tasks pthread)