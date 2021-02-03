#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>
#include <utility>

#include <iostream>
#include <string>


template <typename T>
std::string ToString(std::vector<T> v);

template <typename T>
void Print(std::vector<T> v);

template <typename T>
void PrintLine(std::vector<T> v);


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