cmake_minimum_required(VERSION 3.16)
project(hw12)
set(CMAKE_CXX_STANDARD 20)
add_executable(hw12 hw12.cpp)
find_package( range-v3 REQUIRED )
target_link_libraries( ${PROGRAM_NAME} range-v3::range-v3 )
target_link_libraries(hw12 range-v3)
set_target_properties(hw12
  PROPERTIES
  CXX_FLAGS "-I${TACC_RANGEV3_INC}"
)