# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("QuadDLOG")


SET(BOOST_ROOT "" CACHE PATH "Hint for `find_package(boost)`")
# SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "D:/cpp/boost_1_75_0/bin.v2/libs")


#include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
#target_link_libraries(myapp ${Boost_LIBRARIES})

# Include sub-projects.
add_subdirectory ("QuadDLOG")

# include_directories(SYSTEM CMAKE_INCLUDE_PATH)
# target_link_libraries(myapp CMAKE_LIBRARY_PATH)
