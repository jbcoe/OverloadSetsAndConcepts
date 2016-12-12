cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 14) 

include_directories(SYSTEM externals/catch/include/)

add_executable(test_me test_me.cpp)

enable_testing()
add_test(
  NAME test_me
  COMMAND test_me
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

