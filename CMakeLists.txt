cmake_minimum_required(VERSION 3.20)
project(2048_c C)

set(CMAKE_C_STANDARD 11)

add_executable(2048_c
        src/main.c
        include/toolbox.c
        include/game.c)
