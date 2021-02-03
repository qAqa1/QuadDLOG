#pragma once

#include <boost/multiprecision/cpp_int.hpp>

namespace Math
{
	const int MILLER_RABIN_TEST_COUNT = 5;
	bool IsPrime(boost::multiprecision::cpp_int test);
}
