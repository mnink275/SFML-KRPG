FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        f8d7d77c06936315286eb55f8de22cd23c188571 # 1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(
    ${PROJECT_NAME}_test
    Room/DoorTest.cpp
)

target_include_directories(
    ${PROJECT_NAME}_test PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}_test GTest::gtest_main ${PROJECT_NAME}_objs
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
