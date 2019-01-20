cmake_minimum_required(VERSION 2.8)
project(libgenc C)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
enable_testing()

if(CMAKE_VERSION VERSION_LESS "3.1")
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_C_FLAGS "-std=gnu11 ${CMAKE_C_FLAGS}")
  endif()
else()
    set(CMAKE_C_STANDARD 11)
endif()

execute_process(COMMAND git shortlog --all -nse HEAD OUTPUT_FILE "${CMAKE_SOURCE_DIR}/AUTHORS")

add_subdirectory(src)
add_subdirectory(test)
