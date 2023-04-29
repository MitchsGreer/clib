# =============================================================================
# Cmake list file, will add and compile all the libraries within. Projects that
# use these libraries should only use this file for example.
# =============================================================================
cmake_minimum_required(VERSION 3.25)
project(tinderbox VERSION 1.0 DESCRIPTION "Tinderbox build for C++ libraries.")

# Compiler standereds to use.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files to add.
set(SOURCES "")
# list(APPEND SOURCES src/input.c)

add_library(tinderbox SHARED ${SOURCES})
set_target_properties(tinderbox PROPERTIES VERSION ${PROJECT_VERSION})

# Add include directories.
target_include_directories(Hangman PUBLIC include)
