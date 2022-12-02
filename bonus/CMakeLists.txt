cmake_minimum_required(VERSION 2.8.12)

project(bonus)

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

# create the main executable
## change .cpp files if needed
add_executable(${PROJECT_NAME} main.cc)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
