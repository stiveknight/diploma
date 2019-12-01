cmake_minimum_required(VERSION 3.12)
project(nir)

set(CMAKE_CXX_STANDARD 14)

add_executable(nir main.cpp Graph.cpp Graph.h data.cpp data.h utils.h mthread.h context.h task_queue.h task_queue.cpp Graph_analysis.cpp)