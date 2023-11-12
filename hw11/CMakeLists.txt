cmake_minimum_required( VERSION 3.12 )
project( hw11 VERSION 1.0 )

add_executable( hw11 hw11.cpp )
target_compile_features( hw11 PRIVATE cxx_std_17 )
install( TARGETS hw11 DESTINATION . )