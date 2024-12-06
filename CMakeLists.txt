cmake_minimum_required(VERSION 3.23)
project(files_assignment)

set(CMAKE_CXX_STANDARD 23)

add_executable(files_assignment main.cpp menu.cpp AvaiList.cpp AvaiList.h PIndex.h PIndex.cpp SIndex.h SIndex.cpp Doc.h Doc.cpp App.h App.cpp)
