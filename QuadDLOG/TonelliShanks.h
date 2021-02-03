#pragma once

#include "Root.h"

//#include <boost/multiprecision/cpp_int.hpp>
//
//#include <optional>
//#include <utility>
//
//using roots = std::optional<std::pair<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int>>;
//#define MAKE_ROOT(root1, root2) std::make_optional(std::make_pair(root1, root2));

roots TonelliShanks(boost::multiprecision::cpp_int n, boost::multiprecision::cpp_int p);