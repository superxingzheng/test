cmake_minimum_required(VERSION 2.6)

project(learning_sem CXX)

add_executable(sem_wait sem_wait.cpp)
add_executable(sem_post sem_post.cpp)

target_link_libraries(sem_wait pthread)
target_link_libraries(sem_post pthread)

