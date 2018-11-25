cmake_minimum_required(VERSION 3.9)
project(a4tasks)

set(CMAKE_CXX_STANDARD 17)

add_executable(a4tasks src/a4tasks.cpp src/input_file.cpp src/input_file.h src/task_manager.cpp src/task_manager.h src/task_id.cpp src/task_id.h)