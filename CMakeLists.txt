cmake_minimum_required(VERSION 3.11.4)
project(Encryptions LANGUAGES CXX)

# require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# cygwin doesn't define _POSIX_C_SOURCE by default
if (CMAKE_SYSTEM_NAME STREQUAL "CYGWIN")
   add_definitions(-D_POSIX_C_SOURCE=200809L)
endif()

add_library(Encryptions_static STATIC Encryptions.h)
set_target_properties(Encryptions_static PROPERTIES OUTPUT_NAME "Encryptions")
install(TARGETS Encryptions_static DESTINATION lib)

# build a separate set of object files with PIC enabled
set(BUILD_SHARED_LIB ON CACHE BOOL "Build a shared library")
if (BUILD_SHARED_LIB)
   add_library(Encryptions_shared SHARED Encryptions.h)
   set_target_properties(Encryptions_shared PROPERTIES OUTPUT_NAME "Encryptions")
   install(TARGETS Encryptions_shared DESTINATION lib)
endif()

add_subdirectory(common)
add_subdirectory(Encryptions)
add_subdirectory(modes)
enable_testing()
add_subdirectory(tests)

INSTALL(FILES Encryptions.h
        DESTINATION include)
