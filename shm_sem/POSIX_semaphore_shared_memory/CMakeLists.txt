cmake_minimum_required(VERSION 2.6)

project(shm_sem_test CXX)

add_executable(consumer consumer.cpp)
add_executable(producer producer.cpp)

target_link_libraries(consumer pthread rt)
target_link_libraries(producer pthread rt)

