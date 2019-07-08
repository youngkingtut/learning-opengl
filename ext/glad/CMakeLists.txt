cmake_minimum_required(VERSION 3.14)
project(Glad)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_library(glad src/glad.c)
