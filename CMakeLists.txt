# minimum cmake version requirement
cmake_minimum_required(VERSION 3.10)

# set project name
project(lattice_hub)

# set compiler c++ standard
set(CMAKE_CXX_STANDARD 11)

# library header file locations
include_directories(
	libs/crow/inc
)

# internal module header file locations

# adding libraries
# BOOST components
FIND_PACKAGE( Boost 1.52 COMPONENTS system thread regex REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


# create executable
add_executable(server ./main.cpp)

# linking executable with libraries
TARGET_LINK_LIBRARIES( server LINK_PUBLIC ${Boost_LIBRARIES} )