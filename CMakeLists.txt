cmake_minimum_required(VERSION 3.8.2)

project(ProjectTotusInstrumentation LANGUAGES CXX)

if(NOT DEFINED ENV{JAVA_HOME})
  message(FATAL_ERROR "JAVA_HOME not set")
endif()
include_directories(
  $ENV{JAVA_HOME}/include
  $ENV{JAVA_HOME}/include/linux
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -fno-rtti")

add_library(project-rescribo SHARED
  annotation.cpp
  annotations.cpp
  attribute.cpp
  attributes.cpp
  class_file.cpp
  code.cpp
  constant_pool.cpp
  constant_pool_entry.cpp
  field.cpp
  fields.cpp
  instruction.cpp
  interfaces.cpp
  method.cpp
  methods.cpp
  stack_map_table.cpp
)
set_property(
  TARGET project-rescribo PROPERTY CXX_STANDARD 17
)

install(TARGETS project-rescribo)
