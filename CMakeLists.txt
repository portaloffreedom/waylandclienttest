cmake_minimum_required(VERSION 3.0)

project(waylandclient)

add_executable(waylandclient main.cpp)

install(TARGETS waylandclient RUNTIME DESTINATION bin)
