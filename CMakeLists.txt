cmake_minimum_required(VERSION 3.16)
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
