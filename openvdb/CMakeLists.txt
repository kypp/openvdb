set (MODULE_NAME openvdb)

# Get all compilation units.
file (GLOB ${MODULE_NAME}_SRCS *.cc io/*.cc math/*.cc metadata/*.cc util/*.cc)

# Create the library.
add_library (${MODULE_NAME} ${${MODULE_NAME}_SRCS})

install (TARGETS ${MODULE_NAME} 
		ARCHIVE DESTINATION lib 
		LIBRARY DESTINATION lib)