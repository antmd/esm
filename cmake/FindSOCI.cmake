## Find SOCI
##
## Copyright (c) 2010 Jamie Jones <jamie_jones_au@yahoo.com.au>
## This file is licensed under the GNU GPLv2 or any later versions,
##
## This module defines
## SOCI_LIBRARIES
## SOCI_FOUND, if false, do not try to link to SOCI
## SOCI_INCLUDE_DIRS, where to find the headers
##

FIND_PATH(SOCI_INCLUDE_DIRS soci.h
    ${SOCI_DIR}/include
    ${SOCI_DIR}/include/soci
    $ENV{SOCI_DIR}/include
    $ENV{SOCI_DIR}/include/soci
    $ENV{SOCI_DIR}
    /usr/local/include
    /usr/local/include/soci
    /usr/include
    /usr/include/soci
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
)

FIND_LIBRARY(SOCI_LIBRARIES
  IF(WIN32)
    NAMES libsoci_core
  ELSE(WIN32)
    NAMES soci_core
  ENDIF(WIN32)
    PATHS
    ${SOCI_DIR}/lib
    $ENV{SOCI_DIR}/lib
    $ENV{SOCI_DIR}/bin
    $ENV{SOCI_DIR}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/local/lib64
    /usr/lib
    /usr/lib64
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
)

IF(SOCI_LIBRARIES)
    IF (NOT SOCI_FIND_QUIETLY)
    MESSAGE(STATUS "Found the SOCI library at ${SOCI_LIBRARIES}")
    MESSAGE(STATUS "Found the SOCI headers at ${SOCI_INCLUDE_DIRS}")
    ENDIF (NOT SOCI_FIND_QUIETLY)
ENDIF(SOCI_LIBRARIES)

IF(NOT SOCI_LIBRARIES)
    IF (SOCI_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "SOCI Not Found.Check Environment Variable SOCI_DIR")
    ENDIF (SOCI_FIND_REQUIRED)
ENDIF(NOT SOCI_LIBRARIES)
