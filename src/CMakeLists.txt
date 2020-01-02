# setting source variable
set(
	SOURCE_DIR
	core/db
	core/discovery
	core/state
	io/adaptor
	utils/thing
)

set(SRC_PATHS "")
set(SRC_INCLUDE_PATHS "")

foreach(DIR ${SOURCE_DIR})
	# iterativly append include path variable
	set(
		SRC_INCLUDE_PATHS
		${SRC_INCLUDE_PATHS}
		${DIR}/inc
	)
	# iterativly append src path variable
	aux_source_directory(
		{$DIR}/src
		SRC_PATHS
	)
endforeach(DIR)

# library header file locations
include_directories(
	${SRC_INCLUDE_PATHS}
    ${CMAKE_CURRENT_BINARY_DIR}/../protos
)

message(WARNING ${CMAKE_CURRENT_BINARY_DIR}/protos)
# create executable
add_executable(${PROJECT_NAME} ${SRC_PATHS} ./main.cpp)

# linking executable with required libraries
target_link_libraries(
	${PROJECT_NAME} 
  LINK_PUBLIC protos ${Boost_LIBRARIES}
)
