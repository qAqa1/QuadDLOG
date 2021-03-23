#include "MathsFunctions.h"
#include "MathsFunctions.h"

//#include <boost/math/special_functions/prime.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
//#include <boost/math/common_factor.hpp>

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

boost::multiprecision::cpp_int Math::PrevPrimeNum(boost::multiprecision::cpp_int primeNum)
{
	if (primeNum == 2) return 1;
	if (primeNum == 1) return 1;

	do
	{
		primeNum--;
	} while (!IsPrime(primeNum));

	return primeNum;
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
	//std::cout << "factor = " << factor << ", maxValue = " << maxValue;

	//cpp_int val    = boost::math::lcm(factor, maxValue), // наименьшее общее кратное
	//cpp_int val    = factor, // наименьшее общее кратное
	//	    preVal = 1;

	//while (true)
	//{
	//	if (val * factor > maxValue) return preVal;

	//	auto temp = val / factor;
	//	//std::cout << "temp = " << temp;
	//	if (IsPrime(temp)) preVal = temp;
	//	val = val * factor;
	//	//preVal = std::exchange(val, val * factor);
	//}

	auto del = maxValue / factor;
	if (del == 0) return 1;
	if (IsPrime(del)) return del;
	return PrevPrimeNum(del);

	//cpp_int val = factor,
	//	calcNum = 1,
	//	preVal = 1;

	//while (true)
	//{
	//	if (val + factor > maxValue) return preVal;

	//	calcNum++;
	//	//std::cout << "temp = " << temp;
	//	if (IsPrime(calcNum)) preVal = calcNum;
	//	//val = val * factor;
	//	val = val + factor;
	//	//preVal = std::exchange(val, val * factor);
	//}


	//cpp_int primeNum     = 1,
	//        prevPrimeNum = 1;

	//while (true)
	//{
	//    if (primeNum * factor > maxValue) return prevPrimeNum;
	//    prevPrimeNum = std::exchange(primeNum, NextPrimeNum(primeNum));
	//}


	//if (maxValue == 1) return 1;

	//cpp_int val = IsPrime(maxValue) ? maxValue : PrevPrimeNum(maxValue);

	//while (true)
	//{
	//	if (val % factor == 0) return val;
	//	
	//	if (factor < )

	//	val = PrevPrimeNum(val);
	//	if (val == 1) return 1;
	//}
}

cpp_int Math::Pow(cpp_int num, cpp_int pow)
{
	return boost::multiprecision::pow(num, static_cast<int>(pow));

	//if (pow == 0)
	//    return 1;
	//else if (pow == 1)
	//    return num;
	//else if (pow % 2 == 0)
	//    return Pow(num * num, pow / 2);
	//else
	//    return Pow(num * num, pow / 2) * num;
}
