#pragma once

#include <boost/multiprecision/cpp_int.hpp>

namespace Math
{
	const int MILLER_RABIN_TEST_COUNT = 5;

	bool IsPrime(boost::multiprecision::cpp_int test);
    boost::multiprecision::cpp_int NextPrimeNum(boost::multiprecision::cpp_int primeNum);
    int NextPrimeInt(int primeNum);
    boost::multiprecision::cpp_int Pow(boost::multiprecision::cpp_int num, boost::multiprecision::cpp_int pow);
}
