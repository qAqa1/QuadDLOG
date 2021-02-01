// QuadDLOG.cpp : Defines the entry point for the application.
//

#include "QuadDLOG.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/special_functions/prime.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <iomanip>

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	using namespace boost::multiprecision;
	using namespace boost::random;
	mt11213b base_gen(clock());
	independent_bits_engine<mt11213b, 256, cpp_int> gen(base_gen);
	mt19937 gen2(clock());
	cpp_int n = gen();
	cpp_int mybignum = 18446744073709551615ull;
	//std::cout << mybignum * mybignum << std::endl;
	std::cout << miller_rabin_test(7, 25, gen) << std::endl;
	std::cout << miller_rabin_test(10, 25, gen);
	//cpp_int x = boost::multiprecision::powm(1, 1, 1);
	
	return 0;
}
