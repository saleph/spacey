# ------------------------------------------------------------------------------
# Function to use when linking 3rd party libs to prevent warnings as
# false-positives
# ------------------------------------------------------------------------------
function(target_link_libraries_system target)
	set(libs ${ARGN})
	foreach(lib ${libs})
		get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)
		target_include_directories(${target} SYSTEM PRIVATE ${lib_include_dirs})
		target_link_libraries(${target} ${lib})
	endforeach(lib)
endfunction(target_link_libraries_system)
