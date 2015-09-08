project(OpenVDB)
cmake_minimum_required(VERSION 2.8)

find_package(Boost REQUIRED)

include_directories (${Boost_INCLUDE_DIRS})
include_directories (${ZLIB_INCLUDE_DIRS})
include_directories (${OpenEXR_INCLUDE_DIRS})
include_directories (${TBB_INCLUDE_DIRS})

include_directories (.)
add_subdirectory (openvdb)

install (DIRECTORY openvdb DESTINATION include FILES_MATCHING PATTERN "*.h")