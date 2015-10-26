project(OpenVDB)
cmake_minimum_required(VERSION 2.8)

find_package(Boost REQUIRED)
include_directories (${Boost_INCLUDE_DIR})

set(ZLIB_INCLUDE_DIR "" CACHE STRING "zlib include directory")
set(OpenEXR_INCLUDE_DIR "" CACHE STRING "openexr include directory")
set(TBB_INCLUDE_DIR "" CACHE STRING "tbb include directory")

include_directories (${ZLIB_INCLUDE_DIR})
include_directories (${OpenEXR_INCLUDE_DIR})
include_directories (${TBB_INCLUDE_DIR})

include_directories (.)
add_subdirectory (openvdb)

install (DIRECTORY openvdb DESTINATION include FILES_MATCHING PATTERN "*.h")