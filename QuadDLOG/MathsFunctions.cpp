#include "MathsFunctions.h"

#include <boost/math/special_functions/prime.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

using namespace boost::multiprecision;
using namespace boost::random;

namespace
{
	mt11213b base_gen(clock());
	independent_bits_engine<mt11213b, 256, cpp_int> gen(base_gen);
}

bool Math::IsPrime(boost::multiprecision::cpp_int test) { return miller_rabin_test(test, Math::MILLER_RABIN_TEST_COUNT, gen); }
