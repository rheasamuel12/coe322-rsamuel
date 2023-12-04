cmake_minimum_required(VERSION 3.17)
project(finalproject VERSION 1.0)

##
## Extra packages: catch2
##
find_package(PkgConfig REQUIRED)
pkg_check_modules(CATCH2 REQUIRED catch2-with-main)

##
## Executable for test cases
##

add_executable(test infectiousdisease.cpp infectiousdisease.hpp)

target_include_directories(
    test PUBLIC ${CATCH2_INCLUDE_DIRS}
)

target_link_directories(
    test PUBLIC ${CATCH2_LIBRARY_DIRS}
)

target_link_libraries(
    test PUBLIC ${CATCH2_LIBRARIES}
)

set_target_properties(
    test PROPERTIES
    BUILD_RPATH "${CATCH2_LIBRARY_DIRS}"
    INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
)

target_compile_features(test PRIVATE cxx_std_17)
install(TARGETS test DESTINATION .)

##
## Executable for simulation without mutation
##

add_executable(finalproject infectiousdisease.cpp infectiousdisease.hpp main.cpp)

target_include_directories(
    finalproject PUBLIC ${CATCH2_INCLUDE_DIRS}
)

target_link_directories(
    finalproject PUBLIC ${CATCH2_LIBRARY_DIRS}
)

target_link_libraries(
    finalproject PUBLIC ${CATCH2_LIBRARIES}
)

set_target_properties(
    finalproject PROPERTIES
    BUILD_RPATH "${CATCH2_LIBRARY_DIRS}"
    INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
)

target_compile_features(finalproject PRIVATE cxx_std_17)
install(TARGETS finalproject DESTINATION .)

##
## Executable for simulation with mutation
##

add_executable(finalprojectmutation infectiousdisease.cpp infectiousdisease2.hpp infectiousdisease.hpp main2.cpp)

target_include_directories(
    finalprojectmutation PUBLIC ${CATCH2_INCLUDE_DIRS}
)

target_link_directories(
    finalprojectmutation PUBLIC ${CATCH2_LIBRARY_DIRS}
)

target_link_libraries(
    finalprojectmutation PUBLIC ${CATCH2_LIBRARIES}
)

set_target_properties(
    finalprojectmutation PROPERTIES
    BUILD_RPATH "${CATCH2_LIBRARY_DIRS}"
    INSTALL_RPATH "${CATCH2_LIBRARY_DIRS}"
)

target_compile_features(finalprojectmutation PRIVATE cxx_std_17)
install(TARGETS finalprojectmutation DESTINATION .)