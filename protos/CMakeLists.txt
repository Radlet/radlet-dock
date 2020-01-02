# include protobuffer header
include_directories(${CMAKE_CURRENT_BINARY_DIR}/protos)

# collecting all proto files
file(GLOB ProtoFiles "*.proto")

# compile protocol buffers
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${ProtoFiles})

# create static library
add_library(protos STATIC ${PROTO_SRCS} ${PROTO_HDRS})

# link procol buffer library to protos static lib
target_link_libraries(protos ${PROTOBUF_LIBRARY})