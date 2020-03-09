# setting source variable
set(
	SOURCE_DIR
	config
	utils/async_manager
	utils/short_time_data
	utils/log
	core/db
	core/discovery
	core/state
	io/adaptor/tcp
	io/adaptor/udp
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
		${DIR}/src
		SRC_PATHS
	)
endforeach(DIR)

# library header file locations
include_directories(
	${SRC_INCLUDE_PATHS}
)

# create executable
add_executable(${PROJECT_NAME} ${SRC_PATHS} ./main.cpp)

# linking executable with required libraries
target_link_libraries(
	${PROJECT_NAME} 
  LINK_PUBLIC protos rxcpp ${Boost_LIBRARIES} cpr sqlite3
)
