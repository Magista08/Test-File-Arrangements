cmake_minimum_required(VERSION 3.17)
project(TestFilesArrangement C)

set(CMAKE_C_STANDARD 11)
LINK_LIBRARIES(m)

add_executable(TestFilesArrangement TestFilesArrangement.c)