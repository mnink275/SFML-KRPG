cmake_minimum_required(VERSION 3.15)
project(
    KRPG
    VERSION 1.0
    DESCRIPTION "A simple rpg game"
    LANGUAGES CXX
)

include(FetchContent)

include(cmake/CompileOptions.cmake)
include(cmake/Sanitizers.cmake)
include(cmake/VisualStudio.cmake)

add_subdirectory(third_party/SFML)
add_subdirectory(core)

add_executable(
    ${PROJECT_NAME} main.cpp
)

target_link_libraries(
    ${PROJECT_NAME} ${PROJECT_NAME}_objs sfml-graphics
)
