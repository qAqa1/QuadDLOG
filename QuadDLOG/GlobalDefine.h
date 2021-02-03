#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>
#include <utility>

#include <iostream>
#include <string>

//using roots = std::optional<std::pair<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int>>;
using roots = std::optional<std::vector<boost::multiprecision::cpp_int>>;
//#define MAKE_ROOT(root1, root2) std::make_optional(std::make_pair(root1, root2));
#define MAKE_ROOT(...) std::make_optional(std::vector<boost::multiprecision::cpp_int>{__VA_ARGS__});

template <typename T>
std::string ToString(std::vector<T> v);

template <typename T>
void Print(std::vector<T> v);


std::string ToString(roots r);
void Print(roots r);


template<typename T>
inline std::string ToString(std::vector<T> v)
{
	std::stringstream ss;
	if (v.size() == 0) return "{}";
	ss << "{" << v[0];
	std::for_each(std::begin(v) + 1, std::end(v), [&ss](T val) { ss << ", " << val; });
	ss << "}";
	return ss.str();
}

template<typename T>
inline void Print(std::vector<T> v) { std::cout << std::endl << ToString(v); }

template<typename T>
inline void PrintLine(std::vector<T> v) { std::cout << ToString(v); }