cmake_minimum_required(VERSION 3.23)
project(files_assignment)

set(CMAKE_CXX_STANDARD 23)

add_executable(files_assignment main.cpp appointment.cpp doctor.cpp primaryIndex.cpp secondaryIndex.cpp menu.cpp
        AvaiList.cpp
        AvaiList.h
        QueryHandeler.cpp)
