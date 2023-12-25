cmake_minimum_required(VERSION 3.15)
project(
    ${CMAKE_PROJECT_NAME}_utility
    VERSION 1.0
    DESCRIPTION "Utility"
    LANGUAGES CXX
)

file(
    GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
)
file(
    GLOB_RECURSE HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

add_library(
    ${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS}
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(
    ${PROJECT_NAME} fmt
)
