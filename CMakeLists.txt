cmake_minimum_required(VERSION 3.0)
project(clana)

set(CMAKE_CXX_STANDARD 11)

add_executable(
  clana 
  src/clana.cpp 
  src/file.cpp
  src/utils.cpp
)
target_include_directories(clana PRIVATE include)
