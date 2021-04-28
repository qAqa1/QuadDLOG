#include "MathsFunctions.h"

#include <boost/multiprecision/miller_rabin.hpp>

using namespace boost::multiprecision;
using namespace boost::random;

namespace
{
	mt11213b base_gen(clock());
	independent_bits_engine<mt11213b, 256, cpp_int> gen(base_gen);
}

bool Math::IsPrime(boost::multiprecision::cpp_int test) { return miller_rabin_test(test, Math::MILLER_RABIN_TEST_COUNT, gen); }

int Math::NextPrimeInt(int primeNum)
{
	do
	{
		primeNum++;
	} while (!IsPrime(primeNum));

	return primeNum;
}

cpp_int Math::Pow(cpp_int num, cpp_int pow)
{
	return boost::multiprecision::pow(num, static_cast<int>(pow));
}
