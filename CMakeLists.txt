cmake_minimum_required(VERSION 3.27.8)
project(project_elevator C)

set(CMAKE_C_STANDARD 99)

add_executable(project_elevator src/apps/main.c
        src/apps/main.c
        src/modules/script_reader.c
        src/headers/script_reader.h
        src/modules/elevator_system.c
        src/headers/elevator_system.h
)


