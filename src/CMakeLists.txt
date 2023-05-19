# common sources
file(GLOB SOURCES
    "*.cpp"
    #"${PROJECT_SOURCE_DIR}/include/*.h"
)
add_library(${PROJECT_NAME}_objs OBJECT
    ${SOURCES}
)
target_link_libraries(${PROJECT_NAME}_objs PRIVATE sfml-graphics sfml-audio)
include_directories(
    "${PROJECT_SOURCE_DIR}/src"
)

# ft2build.h library
include_directories(/usr/include/freetype2)

target_include_directories(${PROJECT_NAME}_objs
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)