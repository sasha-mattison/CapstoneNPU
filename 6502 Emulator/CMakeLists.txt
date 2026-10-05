cmake_minimum_required(VERSION 3.10.0)
project(CapstoneNPU VERSION 0.1.0 LANGUAGES C CXX)

add_executable(
    CapstoneNPU main.cpp
    include/npu.h
    src/npu.cpp
)

target_include_directories(CapstoneNPU PRIVATE include)

