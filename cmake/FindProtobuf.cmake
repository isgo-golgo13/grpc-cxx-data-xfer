# FindProtobuf.cmake
find_package(PkgConfig)

# Use pkg-config to find protobuf
pkg_check_modules(Protobuf REQUIRED protobuf)

# Set the include directories for Protobuf
find_path(Protobuf_INCLUDE_DIR
    NAMES google/protobuf/message.h
    HINTS ${Protobuf_INCLUDE_DIRS})

# Find the protobuf compiler
find_program(Protobuf_PROTOC
    NAMES protoc
    HINTS ${Protobuf_LIBDIR}/../bin ${Protobuf_BINDIR})

# Find the protobuf library
find_library(Protobuf_LIBRARIES
    NAMES protobuf
    HINTS ${Protobuf_LIBDIR})

if (NOT Protobuf_INCLUDE_DIR OR NOT Protobuf_PROTOC OR NOT Protobuf_LIBRARIES)
    message(FATAL_ERROR "Could not find Protobuf")
endif()

# Define CMake variables
set(Protobuf_LIBRARIES ${Protobuf_LIBRARIES})
set(Protobuf_INCLUDE_DIRS ${Protobuf_INCLUDE_DIR})
set(Protobuf_PROTOC_EXECUTABLE ${Protobuf_PROTOC})

# Export as a CMake target
add_library(Protobuf::Protobuf IMPORTED INTERFACE)
set_target_properties(Protobuf::Protobuf PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${Protobuf_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${Protobuf_LIBRARIES}"
)
