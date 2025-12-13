cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(spaceship LANGUAGES CXX)

file(GLOB_RECURSE SOURCES 
    src/main.cpp
    src/ship.cpp
    src/world.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib)

target_link_libraries(${PROJECT_NAME}
    m
    pthread
    dl
    rt
    X11
)
