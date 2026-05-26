cmake_minimum_required(VERSION 3.15)
project(CEngine C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Explicitly add ONLY your source files. This completely blocks any hidden files.
add_executable(CEngine
        main.c
        ecs_core.c
        Components/TestComponent/test_component.c
        Systems/TestSystem/value_increase_system.c
        Entities/Test_Entity.c
)

# Tell CMake exactly which folders contain your headers so you can use compressed file names
target_include_directories(CEngine PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Components/TestComponent
        ${CMAKE_CURRENT_SOURCE_DIR}/Systems/TestSystem
        ${CMAKE_CURRENT_SOURCE_DIR}/Entities
)