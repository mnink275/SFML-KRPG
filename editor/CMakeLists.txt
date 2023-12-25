cmake_minimum_required(VERSION 3.15)
project(
    ${CMAKE_PROJECT_NAME}_editor
    VERSION 1.0
    DESCRIPTION "Simple game editor"
    LANGUAGES CXX
)

file(
    GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
)
file(
    GLOB_RECURSE HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

add_library(
    ${PROJECT_NAME}_objs OBJECT ${SOURCES} ${HEADERS}
)
target_include_directories(
    ${PROJECT_NAME}_objs PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include $<TARGET_PROPERTY:${CMAKE_PROJECT_NAME}_utility,INCLUDE_DIRECTORIES>
)

target_link_libraries(
    ${PROJECT_NAME}_objs sfml-graphics fmt ${CMAKE_PROJECT_NAME}_utility
)

add_executable(
    ${PROJECT_NAME} editor.cpp
)
target_link_libraries(
    ${PROJECT_NAME} ${PROJECT_NAME}_objs sfml-graphics fmt
)
