# minimum cmake version requirement
cmake_minimum_required(VERSION 3.10)

# set project name
project(lattice_hub)

# set compiler c++ standard
set(CMAKE_CXX_STANDARD 11)

# header file locations
include_directories(
	libs/crow/inc
)

# create executable
add_executable(server ./main.cpp)