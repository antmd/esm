# Before running make, we need to run one of the following commands:
# cmake .. (equivalent to cmake -DCMAKE_BUILD_TYPE="Debug" ..)
# cmake -DCMAKE_BUILD_TYPE="Release" ..

cmake_minimum_required(VERSION 2.6)

#add_definitions(-DO3)

project(uTrade)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
  message(STATUS "Setting Default Build Type : Debug ")
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE MATCHES "[Re][Ee][Ll][Ee][Aa][Ss][Ee]")
  set(LIBRARY_OUTPUT_PATH ${uTrade_SOURCE_DIR}/lib/release)
else(CMAKE_BUILD_TYPE MATCHES "[Re][Ee][Ll][Ee][Aa][Ss][Ee]")
  set(LIBRARY_OUTPUT_PATH ${uTrade_SOURCE_DIR}/lib/debug)
endif(CMAKE_BUILD_TYPE MATCHES "[Re][Ee][Ll][Ee][Aa][Ss][Ee]")

# get current revision of the project
IF(Subversion_FOUND)
  Subversion_WC_INFO(${CMAKE_HOME_DIRECTORY} uTrade)
  MESSAGE("Current revision is ${uTrade_WC_REVISION}")
ENDIF(Subversion_FOUND)

# configure a header file to pass some of the CMake settings
# to the source code

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(Boost 1.51 REQUIRED COMPONENTS
      python
      system
      filesystem
      serialization
      thread
      program_options
      regex
      chrono
      test_exec_monitor)

include_directories(${Boost_INCLUDE_DIRS})

# need this to statically link the libraries
# IF(WIN32)
#     SET(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
# ELSE(WIN32)
#     SET(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
# ENDIF(WIN32)

find_package(QUICKFIX REQUIRED)
include_directories(${QUICKFIX_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall ")

set(INSTALL_TARGETS_DEFAULT RUNTIME DESTINATION .)

set(EXECUTABLE_OUTPUT_PATH ${uTrade_SOURCE_DIR}/bin)

add_subdirectory(common)
add_subdirectory(esm)
