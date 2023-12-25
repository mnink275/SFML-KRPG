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
    ${PROJECT_NAME}_objs PUBLIC ${PROJECT_SOURCE_DIR}/core/include $<TARGET_PROPERTY:${CMAKE_PROJECT_NAME}_utility,INCLUDE_DIRECTORIES>
)
target_link_libraries(
    ${PROJECT_NAME}_objs sfml-graphics fmt ${CMAKE_PROJECT_NAME}_utility
)
set_source_files_properties(
  ${CMAKE_CURRENT_LIST_DIR}/src/Game.cpp
  PROPERTIES COMPILE_DEFINITIONS RESOURCE_FOLDER="${PROJECT_SOURCE_DIR}/resource"
)

# IDEs should put the headers in a nice place
source_group(
    TREE "${PROJECT_SOURCE_DIR}/core/include"
    PREFIX "Header Files"
    FILES ${HEADERS}
)
