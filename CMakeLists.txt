cmake_minimum_required(VERSION 3.20)

project(cpp_systems_lab VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(cpsys
    src/RegisterMap.cpp
    src/SimpleDevice.cpp
)

target_include_directories(cpsys PUBLIC include)

target_compile_options(cpsys PRIVATE
    -Wall -Wextra -Wpedantic
)

add_executable(cpsys_demo src/main.cpp)
target_link_libraries(cpsys_demo PRIVATE cpsys)

add_executable(smoke_test tests/smoke_test.cpp)
target_link_libraries(smoke_test PRIVATE cpsys)

add_executable(register_access_bench benchmarks/register_access_bench.cpp)
target_link_libraries(register_access_bench PRIVATE cpsys)
