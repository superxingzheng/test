# Updated on June 6 2017

cmake_minimum_required(VERSION 2.8)

project(test CXX)

add_executable(test main.cpp)

target_link_libraries(test pqxx pq)
