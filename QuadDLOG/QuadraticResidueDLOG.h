#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include <optional>

using res_container = std::vector<boost::multiprecision::cpp_int>;
using level_data    = std::vector<res_container>;

boost::multiprecision::cpp_int ToRoot(boost::multiprecision::cpp_int val, boost::multiprecision::cpp_int twoPow);
bool CheckRoot(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b, boost::multiprecision::cpp_int c, boost::multiprecision::cpp_int root);
res_container CalcLevel(res_container n_values, boost::multiprecision::cpp_int p, int degree);
std::optional<boost::multiprecision::cpp_int> CalcDegree(int degree,boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b, boost::multiprecision::cpp_int c);
std::optional<boost::multiprecision::cpp_int> FindRoot(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b, boost::multiprecision::cpp_int c);
