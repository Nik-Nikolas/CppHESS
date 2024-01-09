cmake_minimum_required(VERSION 3.15)

project(CppHESS
  VERSION
    1.0
  DESCRIPTION
    "CppHESS"
  LANGUAGES
    CXX
)

find_package(Threads REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

add_subdirectory(source)
