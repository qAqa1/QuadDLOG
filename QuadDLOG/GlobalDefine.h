#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>
#include <utility>

#include <iostream>
#include <string>

using roots = std::optional<std::pair<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int>>;
#define MAKE_ROOT(root1, root2) std::make_optional(std::make_pair(root1, root2));

std::string ToString(roots r);
void Print(roots r);