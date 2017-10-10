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

OPTION ( OPENVDB_BUILD_UNITTESTS "Build the OpenVDB unit tests" ON )
OPTION ( OPENVDB_BUILD_DOCS "Build the OpenVDB documentation" OFF )
OPTION ( OPENVDB_BUILD_PYTHON_MODULE "Build the pyopenvdb Python module" ON )
OPTION ( OPENVDB_BUILD_HOUDINI_SOPS "Build the Houdini SOPs" OFF )
OPTION ( OPENVDB_BUILD_MAYA_PLUGIN "Build the Maya plugin" OFF )
OPTION ( OPENVDB_BUILD_CORE "Build the OpenVDB core" ON )
OPTION ( OPENVDB_ENABLE_RPATH "Build with RPATH information" ON )
OPTION ( OPENVDB_ENABLE_3_ABI_COMPATIBLE "Build with OpenVDB v3 ABI" ON )
OPTION ( OPENVDB_DISABLE_BOOST_IMPLICIT_LINKING "Disable the implicit linking of Boost libraries on Windows" ON )

IF (OPENVDB_BUILD_HOUDINI_SOPS)
  SET ( OPENVDB_BUILD_PYTHON_MODULE OFF )
ENDIF ()

IF ( APPLE )
  IF ( OPENVDB_BUILD_HOUDINI_SOPS AND OPENVDB_BUILD_MAYA_PLUGIN )
	MESSAGE ( FATAL_ERROR "On OSX, Houdini linked with libc++ whereas Maya is linked with libstdc++, the different runtimes are not mutually compatible, build them Houdini SOPs and Maya plugins separately with the requisite DCC's compiler" )
  ENDIF ()
ENDIF ()

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

SET ( OPENVDB_TOP_LEVEL_DIR ${PROJECT_SOURCE_DIR} CACHE PATH "OpenVDB Top Level Directory to share among sub projects" )

INCLUDE_DIRECTORIES ( ${OPENVDB_TOP_LEVEL_DIR} ) # To make sure we pick up headers from this version of OpenVDB we are building

IF ( OPENVDB_ENABLE_3_ABI_COMPATIBLE )
  ADD_DEFINITIONS ( -DOPENVDB_3_ABI_COMPATIBLE )
ENDIF ()

IF ( OPENVDB_BUILD_CORE )
  ADD_SUBDIRECTORY ( openvdb )
ENDIF ()

IF (OPENVDB_BUILD_PYTHON_MODULE)
  ADD_SUBDIRECTORY ( openvdb/python )
ENDIF ()

IF ( OPENVDB_BUILD_HOUDINI_SOPS )
  ADD_SUBDIRECTORY ( openvdb_houdini )
ENDIF ()

IF ( OPENVDB_BUILD_MAYA_PLUGIN )
  ADD_SUBDIRECTORY ( openvdb_maya )
ENDIF ()
