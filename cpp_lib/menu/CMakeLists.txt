# =============================================================================
# This is the CMake file for the menu library.
# =============================================================================
cmake_minimum_required(VERSION 3.16)
project(libmenu VERSION 1.0 DESCRIPTION "Library for command line menus.")

# Compiler standereds to use.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files to add.
set(SOURCES "")
list(APPEND SOURCES src/menu.cpp)
list(APPEND SOURCES src/menu_item.cpp)

add_library(libmenu STATIC ${SOURCES})
set_target_properties(libmenu PROPERTIES VERSION ${PROJECT_VERSION})

# Add include directories.
target_include_directories(libmenu PUBLIC include)
