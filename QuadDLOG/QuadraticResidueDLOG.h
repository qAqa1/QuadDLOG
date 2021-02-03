#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>

using res_container = std::vector<boost::multiprecision::cpp_int>;
using level_data    = std::vector<res_container>;

boost::multiprecision::cpp_int ToRoot(boost::multiprecision::cpp_int val, boost::multiprecision::cpp_int twoPow);
bool CheckRoot(boost::multiprecision::cpp_int g, boost::multiprecision::cpp_int n, boost::multiprecision::cpp_int p, boost::multiprecision::cpp_int root);
res_container CalcLevel(res_container n_values, boost::multiprecision::cpp_int p);
boost::multiprecision::cpp_int FindRoot(boost::multiprecision::cpp_int g, boost::multiprecision::cpp_int n, boost::multiprecision::cpp_int p);
