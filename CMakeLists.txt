cmake_minimum_required(VERSION 3.10)
project(Barebones VERSION 0.0.1
        DESCRIPTION "A small tactics/roguelike game created with the UrsineEngine.")

# Set the search path for the UrsineEngine library using
# an environment variable.
set(CMAKE_PREFIX_PATH "$ENV{URSINE_ENGINE_INSTALL_DIR}/lib/")
find_package(UrsineEngine REQUIRED)

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(INSTALL_DIR "${CMAKE_SOURCE_DIR}/install")
add_subdirectory(source)
