cmake_minimum_required(VERSION 3.15)
project(CEngine C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(CEngine
        src/main.c
        src/entities/E_test.c
        src/systems/S_value_increase.c

        ECS/src/ecs_core.c
        ECS/src/components_tags.c
)

target_include_directories(CEngine PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/ECS/include
)