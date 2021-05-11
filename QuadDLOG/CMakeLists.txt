# CMakeList.txt : CMake project for QuadDLOG, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0074 NEW) # allow to use <PackageName>_ROOT variables as hint for find_package
# SET(BOOST_ROOT "D:/cpp/boost_1_75_0")
find_package(Boost 1.75.0 REQUIRED)
message(${Boost_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (QuadDLOG
"QuadDLOG.cpp"
"TonelliShanks.h"
"TonelliShanks.cpp"
"MathsFunctions.h"
"MathsFunctions.cpp"
"QuadraticResidueDLOG.h"
"QuadraticResidueDLOG.cpp"
"Root.h"
"ModuloComprasion.h"
"ModuloComprasion.cpp"
"CantorZassenhaus.h"
"CantorZassenhaus.cpp"
"Polynomial.h"
"Polynomial.cpp"
)
target_link_libraries(QuadDLOG Boost::headers)

# TODO: Add tests and install targets if needed.
