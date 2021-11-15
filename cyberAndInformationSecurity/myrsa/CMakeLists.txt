cmake_minimum_required(VERSION 3.17)
project(myrsa)
set(CMAKE_CXX_STANDARD 14)
include_directories(src)

file(GLOB_RECURSE SRC  
    src/*.cpp 
    src/*.h
)
file(GLOB_RECURSE TEST  
    test/*.cpp
)

add_executable(main ${SRC} main.cpp)

add_executable(unit_test  ${SRC} ${TEST})
target_link_libraries(unit_test gtest gtest_main pthread)