# common sources
file(GLOB SOURCES
    "*.cpp"
)

add_library(
    ${PROJECT_NAME}_objs
    OBJECT ${SOURCES}
)

target_compile_options(${PROJECT_NAME}_objs PRIVATE -fsanitize=address)
target_link_options(${PROJECT_NAME}_objs PRIVATE -fsanitize=address)

target_link_libraries(${PROJECT_NAME}_objs PRIVATE sfml-graphics)
include_directories(
    "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(${PROJECT_NAME}_objs
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_definitions(${PROJECT_NAME}_objs PRIVATE RESOURCE_FOLDER="${RESOURCE_FOLDER}")