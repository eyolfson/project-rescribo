cmake_minimum_required(VERSION 3.8.2)

project(ProjectRescribo LANGUAGES CXX)

if(NOT DEFINED ENV{JAVA_HOME})
  message(FATAL_ERROR "JAVA_HOME not set")
endif()
include_directories(
  include/project-rescribo
  $ENV{JAVA_HOME}/include
  $ENV{JAVA_HOME}/include/linux
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -fno-rtti")

add_subdirectory(src)

install(DIRECTORY include/project-rescribo
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.hpp"
)
