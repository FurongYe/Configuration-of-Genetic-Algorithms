######################################################################################
# Project settings
######################################################################################

cmake_minimum_required(VERSION 3.6)

enable_language(CXX) # C++

## Current version
set(VERSION_MAJOR 0 CACHE STRING "Major version number" )
set(VERSION_MINOR 0 CACHE STRING "Minor version number" )
set(VERSION_PATCH 0 CACHE STRING "Patch version number" )
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

# set the project name and version
project(IOHexperimenter VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_OUTPUT_PATH "build/Cpp/")
# specify the CXX FLAGS
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

######################################################################################
# Gather source files
######################################################################################

# set source file directorys and prepare for adding libraries.
SET(SRC "src/")
FILE (GLOB SRC_CPP "${SRC}/*.cpp")
FILE (GLOB SRC_INCLUDE "${SRC}/*.h")

SET(PROBLEMS_BBOB_DIR "IOH/src/Problems/BBOB")
FILE (GLOB PROBLEMS_BBOB_SRC "${PROBLEMS_BBOB_DIR}/*.hpp")
FILE (GLOB PROBLEMS_BBOB_INCLUDE "${PROBLEMS_BBOB_DIR}/*.hpp")

SET(PROBLEMS_BBOB_COMMON_DIR "IOH/src/Problems/BBOB/bbob_common_used_functions")
FILE (GLOB PROBLEMS_BBOB_COMMON_SRC "${PROBLEMS_BBOB_COMMON_DIR}/*.cpp" "${PROBLEMS_BBOB_COMMON_DIR}/*.hpp")
FILE (GLOB PROBLEMS_BBOB_COMMON_INCLUDE "${PROBLEMS_BBOB_COMMON_DIR}/*.hpp")

SET(PROBLEMS_COMMON_DIR "IOH/src/Problems/common_used_functions")
FILE (GLOB PROBLEMS_COMMON_SRC  "${PROBLEMS_COMMON_DIR}/*.hpp" )
FILE (GLOB PROBLEMS_COMMON_INCLUDE  "${PROBLEMS_COMMON_DIR}/*.hpp" )

SET(PROBLEMS_PBO_DIR "IOH/src/Problems/PBO")
FILE (GLOB PROBLEMS_PBO_SRC "${PROBLEMS_PBO_DIR}/*.hpp" )
FILE (GLOB PROBLEMS_PBO_INCLUDE "${PROBLEMS_PBO_DIR}/*.hpp" )

SET(PROBLEMS_WMODEL_DIR "IOH/src/Problems/WModel")
FILE (GLOB PROBLEMS_WMODEL_SRC  "${PROBLEMS_WMODEL_DIR}/*.hpp")
FILE (GLOB PROBLEMS_WMODEL_INCLUDE  "${PROBLEMS_WMODEL_DIR}/*.hpp")

SET(PROBLEMS_PYTHON_DIR "IOH/src/Problems/Python")
FILE (GLOB PROBLEMS_PYTHON_SRC "")
FILE (GLOB PROBLEMS_PYTHON_INCLUDE "${PROBLEMS_Python_DIR}/*.h" "${PROBLEMS_Python_DIR}/*.hpp")

SET(SUITES_DIR "IOH/src/Suites")
FILE (GLOB SUITES_SRC "${SUITES_DIR}/*.h" "${SUITES_DIR}/*.hpp")
FILE (GLOB SUITES_INCLUDE "${SUITES_DIR}/*.h" "${SUITES_DIR}/*.hpp")

SET(TEMPLATE_DIR "IOH/src/Template")
FILE (GLOB TEMPLATE_SRC "${TEMPLATE_DIR}/*.cpp" "${TEMPLATE_DIR}/*.hpp" "${TEMPLATE_DIR}/*.h")
#aux_source_directory(src/Template/ DIR_TEMP)
FILE (GLOB TEMPLATE_INCLUDE "${TEMPLATE_DIR}/*.h" "${TEMPLATE_DIR}/*.hpp")

SET(TEMPLATE_EXPERIMENTS_DIR "IOH/src/Template/Experiments")
FILE (GLOB TEMPLATE_EXPERIMENTS_SRC "${TEMPLATE_EXPERIMENTS_DIR}/*.hpp" "${TEMPLATE_EXPERIMENTS_DIR}/*.cpp")
FILE (GLOB TEMPLATE_EXPERIMENTS_INCLUDE "${TEMPLATE_EXPERIMENTS_DIR}/*.h" "${TEMPLATE_EXPERIMENTS_DIR}/*.hpp")

SET(TEMPLATE_LOGGERS_DIR "IOH/src/Template/Loggers")
FILE (GLOB TEMPLATE_LOGGERS_SRC "${TEMPLATE_LOGGERS_DIR}/*.cpp" "${TEMPLATE_LOGGERS_DIR}/*.hpp")
FILE (GLOB TEMPLATE_LOGGERS_INCLUDE "${TEMPLATE_LOGGERS_DIR}/*.h" "${TEMPLATE_LOGGERS_DIR}/*.hpp")

SET(IOHEXPERIMENTER_SRC
  "${SRC_CPP}"
  "${PROBLEMS_COMMON_SRC}"
  "${PROBLEMS_BBOB_SRC}"
  "${PROBLEMS_BBOB_COMMON_SRC}"
  "${PROBLEMS_PBO_SRC}"
  "${PROBLEMS_WMODEL_SRC}"
  "${PROBLEMS_PYTHON_SRC}"
  "${SUITES_SRC}"
  "${TEMPLATE_SRC}"
  "${TEMPLATE_EXPERIMENTS_SRC}"
  "${TEMPLATE_LOGGERS_SRC}"
)

SET(IOHEXPERIMENTER_DIR
  "${SRC}"
  "${PROBLEMS_COMMON_DIR}"
  "${PROBLEMS_BBOB_DIR}"
  "${PROBLEMS_BBOB_COMMON_DIR}"
  "${PROBLEMS_PBO_DIR}"
  "${PROBLEMS_WMODEL_DIR}"
  "${PROBLEMS_PYTHON_DIR}"
  "${SUITES_DIR}"
  "${TEMPLATE_DIR}"
  "${TEMPLATE_EXPERIMENTS_DIR}"
  "${TEMPLATE_LOGGERS_DIR}"
)

SET(IOHEXPERIMENTER_INCLUDE
  "${SRC_INCLUDE}"
  "${PROBLEMS_COMMON_INCLUDE}"
  "${PROBLEMS_BBOB_INCLUDE}"
  "${PROBLEMS_BBOB_COMMON_INCLUDE}"
  "${PROBLEMS_PBO_INCLUDE}"
  "${PROBLEMS_WMODEL_INCLUDE}"
  "${PROBLEMS_PYTHON_INCLUDE}"
  "${SUITES_INCLUDE}"
  "${TEMPLATE_INCLUDE}"
  "${TEMPLATE_EXPERIMENTS_INCLUDE}"
  "${TEMPLATE_LOGGERS_INCLUDE}"
)


######################################################################################
# Binaries
######################################################################################

# add the binary tree to the search path for include files
# so that we will find header files of IOHexperimenter.
include_directories(${IOHEXPERIMENTER_DIR})

# add the IOH library
add_library(ConfGA ${IOHEXPERIMENTER_SRC})

######################################################################################
# Installation
######################################################################################

# install. set name of the installed library as 'IOH'.
install (TARGETS ConfGA DESTINATION lib)
install (FILES ${IOHEXPERIMENTER_INCLUDE} DESTINATION include)
