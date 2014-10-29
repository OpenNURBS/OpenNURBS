# OpenNURBS CMake Build system
# see GNU GENERAL PUBLIC LICENSE, version 2, attached

cmake_minimum_required(VERSION 2.8)

project(OpenNURBS)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION "0.0")

option(BUILD_VERBOSE    "Verbose build:" ON)
if(BUILD_VERBOSE)
  set(CMAKE_VERBOSE_MAKEFILE true)
endif()
message(STATUS "cmake -v:      ${CMAKE_VERSION}")
message(STATUS "localhost:     ${CMAKE_SYSTEM}")
message(STATUS "hardware:      ${CMAKE_SYSTEM_PROCESSOR}")

option(BUILD_SHARED_LIBS   "Build shared libraries:" ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  INCLUDE(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG(-std=c++11 HAVE_STD11)
  if (HAVE_STD11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  else()
    message(FATAL_ERROR "C++11 support is required to build this project (-std=c++11 not defined).")
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
  INCLUDE(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG(-std=c++11 HAVE_STD11)
  if (HAVE_STD11)
    if (APPLE)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
  else()
    message(FATAL_ERROR "cxx11 needs clang support, please install or update clang.")
  endif()
endif()

message(STATUS "cxx compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "cxx flags:       ${CMAKE_CXX_FLAGS}")
message(STATUS "cxx link flags:  ${CMAKE_CXX_LINK_FLAGS}")
message(STATUS "build shared libs: ${BUILD_SHARED_LIBS}")

add_subdirectory(src)

