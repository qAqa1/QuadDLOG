#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <utility>

#include <iostream>
#include <string>
#include <vector>

namespace std
{
    template <typename T>
    inline ostream& operator<<(ostream& os, const vector<boost::multiprecision::cpp_int> v);

    template <typename T>
    inline ostream& operator<<(ostream& os, const vector<int> v);

//    template <typename T>
//    inline string to_string(const vector<T> v);
}  // namespace std

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const std::vector<T> v)
{
	if (v.size() == 0)
    {
	    os << "{}";
        return os;
    }
	os << "{" << v.front();
	std::for_each(std::begin(v) + 1, std::end(v), [&os](T val) { os << ", " << val; });
	os << "}";
	return os;
}

//template <typename T>
//inline std::string std::to_string(const std::vector<T> v)
//{
//    std::stringstream ss;
//    ss << v;
//    return ss.str();
//}
