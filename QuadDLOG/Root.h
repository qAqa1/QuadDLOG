#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>
#include <utility>

using roots = std::optional<std::vector<boost::multiprecision::cpp_int>>;
#define MAKE_ROOT(...) std::make_optional(std::vector<boost::multiprecision::cpp_int>{__VA_ARGS__});
