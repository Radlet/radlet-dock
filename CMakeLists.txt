# minimum cmake version requirement
cmake_minimum_required(VERSION 3.10)

# set project name
project(lattice_hub)

# set compiler c++ standard
set(CMAKE_CXX_STANDARD 17)

# set binary output directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate build directory for build files.
")
endif()

# find libraries
# BOOST components
find_package( Boost 1.52 COMPONENTS system thread regex REQUIRED )
find_package( Protobuf REQUIRED )

# include 3rd party header files
include_directories(
  ${CMAKE_SOURCE_DIR}/libs/crow/inc
  ${CMAKE_SOURCE_DIR}/libs/sqlite3pp/inc
  ${Boost_INCLUDE_DIR}
  ${Protobuf_INCLUDE_DIRS}
)

# sub_directories
add_subdirectory(
  ${CMAKE_SOURCE_DIR}/protos
)
add_subdirectory(
  ${CMAKE_SOURCE_DIR}/src
)
