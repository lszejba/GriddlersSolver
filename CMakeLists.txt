cmake_minimum_required(VERSION 3.0)

project(solver_v2)

add_executable(solver_v2 main.cpp)

install(TARGETS solver_v2 RUNTIME DESTINATION bin)
