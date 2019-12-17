# minimum cmake version requirement
cmake_minimum_required(VERSION 3.10)

# set project name
project(lattice_hub)

# set compiler c++ standard
set(CMAKE_CXX_STANDARD 11)

# set binary output directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate build directory for build files.
")
endif()



# library header file locations
include_directories(
	libs/crow/inc
)

# internal module header file locations
include_directories(
	io/adaptor/http/inc
)

# adding libraries
# BOOST components
FIND_PACKAGE( Boost 1.52 COMPONENTS system thread regex REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


# create executable
add_executable(server ./main.cpp)

# linking executable with libraries
TARGET_LINK_LIBRARIES( server LINK_PUBLIC ${Boost_LIBRARIES} )