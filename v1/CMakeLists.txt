cmake_minimum_required(VERSION 3.22)

project(ShuntingYardAlgorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Werror)

add_executable(
    app
    Core.cpp
    ShuntingYard.cpp
    TokenSubClass.cpp
    Main.cpp
)