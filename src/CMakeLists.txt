# Headers
file(GLOB HEADERS
CONFIGURE_DEPENDS "${KRPG_SOURCE_DIR}/include/*.hpp")

# Sources
file(GLOB SOURCES
    "*.cpp"
)

# Make an automatic library - will be static or dynamic based on user setting
add_library(${PROJECT_NAME}_objs OBJECT ${SOURCES})

# We need this directory, and users of our library will need it too
target_include_directories(${PROJECT_NAME}_objs PUBLIC ../include)
#target_include_directories(${PROJECT_NAME}_objs
#    PUBLIC
#    ${CMAKE_CURRENT_LIST_DIR}
#)

target_compile_options(${PROJECT_NAME}_objs PRIVATE -fsanitize=address)
target_link_options(${PROJECT_NAME}_objs PRIVATE -fsanitize=address)

target_link_libraries(${PROJECT_NAME}_objs PRIVATE sfml-graphics)

target_compile_definitions(${PROJECT_NAME}_objs PRIVATE RESOURCE_FOLDER="${RESOURCE_FOLDER}")

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
