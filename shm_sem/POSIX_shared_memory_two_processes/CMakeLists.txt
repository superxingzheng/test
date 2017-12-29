cmake_minimum_required(VERSION 2.6)

project(shm_test_3 CXX)

add_executable(mmap-write mmap-write.cpp)
add_executable(mmap-read mmap-read.cpp)

target_link_libraries(mmap-write rt)
target_link_libraries(mmap-read rt)
