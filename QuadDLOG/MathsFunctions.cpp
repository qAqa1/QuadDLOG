#include "MathsFunctions.h"
#include "MathsFunctions.h"

//#include <boost/math/special_functions/prime.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

#include <utility>

using namespace boost::multiprecision;
using namespace boost::random;

namespace
{
	mt11213b base_gen(clock());
	independent_bits_engine<mt11213b, 256, cpp_int> gen(base_gen);
}

bool Math::IsPrime(boost::multiprecision::cpp_int test) { return miller_rabin_test(test, Math::MILLER_RABIN_TEST_COUNT, gen); }

boost::multiprecision::cpp_int Math::FindBiggest2DeegreeInNum(cpp_int num)
{
    cpp_int two = 2;
    auto powResult = two;
    while (powResult * two <= num)
    {
        powResult *= two;
    }
    return powResult;
}

cpp_int Math::NextPrimeNum(cpp_int primeNum)
{
    do
    {
        primeNum++;
    } while (!IsPrime(primeNum));

    return primeNum;
}

int Math::NextPrimeInt(int primeNum)
{
    do
    {
        primeNum++;
    } while (!IsPrime(primeNum));

    return primeNum;
}

cpp_int Math::FindBiggestPrimeNumInNum(cpp_int factor, cpp_int maxValue)
{
    cpp_int primeNum     = 1,
            prevPrimeNum = 1;

    while (true)
    {
        if (primeNum * factor > maxValue) return prevPrimeNum;
        prevPrimeNum = std::exchange(primeNum, NextPrimeNum(primeNum));
    }
}

cpp_int Math::Pow(cpp_int num, cpp_int pow)
{
    if (pow == 0)
        return 1;
    else if (pow == 1)
        return num;
    else if (pow % 2 == 0)
        return Pow(num * num, pow / 2);
    else
        return Pow(num * num, pow / 2) * num;
}
