# =============================================================================
# CMake list file for the example project using the menu library.
# =============================================================================
cmake_minimum_required(VERSION 3.16)
project(menu_example VERSION 1.0 DESCRIPTION "Example using the menu library.")

# Compiler standereds to use.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(../../menu ../../build)

# Source files to add.
set(SOURCES "")
list(APPEND SOURCES src/main.cpp)
list(APPEND SOURCES src/example_menu_item.cpp)

add_executable(menu_example ${SOURCES})
set_target_properties(menu_example PROPERTIES VERSION ${PROJECT_VERSION})

# Add include directories.
target_include_directories(menu_example PUBLIC include)
target_include_directories(menu_example PUBLIC ../../menu/include)
target_link_libraries(menu_example libmenu)
