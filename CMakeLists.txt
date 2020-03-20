# File: CMakeLists.txt Author: Michalis Vardoulakis <mvard@ics.forth.gr>

cmake_minimum_required(VERSION 3.0.2)
include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(kreon)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  message("Debug build")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  message("Release build")
else()
  message(WARNING "No build type specified defaults to Debug build!")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

file(GLOB_RECURSE ALL_C_SOURCE_FILES ${CMAKE_SOURCE_DIR}/kreon/*.c
     ${CMAKE_SOURCE_DIR}/kreon/*.h ${CMAKE_SOURCE_DIR}/tests/*.c
     ${CMAKE_SOURCE_DIR}/tests/*.h)

file(COPY ${CMAKE_SOURCE_DIR}/scripts/mkfs.eutropia.single.sh
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/YCSB-CXX/)

file(COPY ${CMAKE_SOURCE_DIR}/scripts/mkfs.eutropia.single.sh
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests/)

file(COPY ${CMAKE_SOURCE_DIR}/YCSB-CXX/workloads
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/YCSB-CXX/)

file(COPY ${CMAKE_SOURCE_DIR}/YCSB-CXX/execution_plan.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/YCSB-CXX/)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(format COMMAND clang-format -i ${ALL_C_SOURCE_FILES})
else()
  message("Clang-format not installed!")
endif()

FetchContent_Populate(
  uthash # Recommendation: Stick close to the original name.
  GIT_REPOSITORY https://github.com/troydhanson/uthash.git
  SOURCE_DIR external-deps/src/uthash # (Relative) path within in the build
                                      # directory.
)

FetchContent_Populate(
  log # Recommendation: Stick close to the original name.
  GIT_REPOSITORY https://github.com/rxi/log.c.git
  SOURCE_DIR external-deps/log # (Relative) path within in the build directory.
)

set(Zookeeper_LIB_PATHS /usr/local/lib /opt/local/lib)
find_path(Zookeeper_INCLUDE_DIR zookeeper/zookeeper.h /usr/local/include)
find_library(
  Zookeeper_LIBRARY
  NAMES zookeeper_st
  PATHS ${Zookeeper_LIB_PATHS})

if(NOT Zookeeper_INCLUDE_DIR)
  message("Could not find zookeeper header")
else()
  message("Zookeeper headers at ${Zookeeper_INCLUDE_DIR}")
endif()

if(NOT Zookeeper_LIBRARY)
  message("Could not find zookeeper lib needs >= 3.4.5")
else()
  message("Zookeeper headers at ${Zookeeper_LIBRARY}")
  include_directories(${Zookeeper_INCLUDE_DIR}/zookeeper)
endif()

# Paths set(ZK_C_LIB "/home1/public/mvard/zookeeper_c")

include_directories(${CMAKE_BINARY_DIR}/external-deps/log/src/)
# Compiler configuration
if(NOT CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER "gcc")
endif()

if(NOT CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_COMPILER "g++")
endif()

set(CMAKE_C_FLAGS_RELEASE "-std=gnu99 -Wall -I${CMAKE_BINARY_DIR}")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -g -I${CMAKE_BINARY_DIR}")
set(CMAKE_CXX_FLAGS_RELEASE "-std=gnu++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -g")

add_subdirectory(kreon_rdma)
add_subdirectory(kreon_lib)
add_subdirectory(kreon_server)
add_subdirectory(YCSB-CXX)
add_subdirectory(utilities)
add_subdirectory(tests)