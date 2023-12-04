cmake_minimum_required( VERSION 3.17 )
project( finalproject VERSION 1.0 )


##
## Extra packages: catch2
##
find_package( PkgConfig REQUIRED )
pkg_check_modules( CATCH2 REQUIRED catch2-with-main )

##
## main
##

add_executable( finalproject infectiousdisease.cpp main.cpp infectiousdisease.hpp)

target_include_directories( 
	finalproject PUBLIC ${CATCH2_INCLUDE_DIRS}
	)

target_link_directories(
	finalproject PUBLIC	${CATCH2_LIBRARY_DIRS}
	)
target_link_libraries(
	finalproject PUBLIC ${CATCH2_LIBRARIES}
	)

set_target_properties(
	finalproject PROPERTIES
	BUILD_RPATH   "${CATCH2_LIBRARY_DIRS}"
	INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
    )

target_compile_features( finalproject PRIVATE cxx_std_17 )
install( TARGETS finalproject DESTINATION . )