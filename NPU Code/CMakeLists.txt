cmake_minimum_required(VERSION 3.10.0)
project(NPUCode VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(NPUCode
    main.cpp
    src/npu.cpp
)

target_include_directories(NPUCode PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)