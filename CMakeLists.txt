cmake_minimum_required(VERSION 3.15)
project(KRPG CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

if(CMAKE_GENERATOR MATCHES "Visual Studio 17 2022")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

# common sources
file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/include/*.h"
)
add_library(${PROJECT_NAME}_objs OBJECT
    ${SOURCES}
)
target_link_libraries(${PROJECT_NAME}_objs PRIVATE sfml-graphics sfml-audio)
include_directories(
    "${PROJECT_SOURCE_DIR}/src"
)

# main.cpp file
add_executable(${PROJECT_NAME} main.cpp)

#target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/srs)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs sfml-graphics sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()

target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")

# Unit Tests
#add_executable(${PROJECT_NAME}_unittest
#    src/hello_test.cpp
#)
#target_link_libraries(${PROJECT_NAME}_unittest PRIVATE ${PROJECT_NAME}_objs userver-utest)
#add_google_tests(${PROJECT_NAME}_unittest)