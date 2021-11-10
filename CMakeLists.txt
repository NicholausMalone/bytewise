# CMakeList.txt : CMake project for bytewise, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("bytewise")

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES bytewise.c)

# Add source to this project's executable.
add_executable (bytewise ${SOURCE_FILES})

#add_library(bytewise SHARED ${SOURCE_FILES})

# Set startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT bar)

# TODO: Add tests and install targets if needed.
