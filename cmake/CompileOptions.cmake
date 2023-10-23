add_compile_options(-Wall -Wextra -Wpedantic -g)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RESOURCE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/resource")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)