// QuadDLOG.cpp : Defines the entry point for the application.
//

#include "QuadDLOG.h"
#include "TonelliShanks.h"

//#include <boost/multiprecision/cpp_int.hpp>
//#include <boost/math/special_functions/prime.hpp>
//#include <boost/multiprecision/miller_rabin.hpp>
//#include <iomanip>

using namespace std;

int main()
{
	//cout << "Hello CMake." << endl;
	//using namespace boost::multiprecision;
	//using namespace boost::random;
	//mt11213b base_gen(clock());
	//independent_bits_engine<mt11213b, 256, cpp_int> gen(base_gen);
	//mt19937 gen2(clock());
	//cpp_int n = gen();
	//cpp_int mybignum = 18446744073709551615ull;
	////std::cout << mybignum * mybignum << std::endl;
	//cpp_int big("83535129432751926654794119899284670605646105190886400636905174071365373973275525538155346697129240278850010057265917695774449530196452808640176870806410710903290083454243795118814994544800125905907044560499073773883483099620376278339388269978351983303471690332884877592791757135659945510849183070180951011049");
	//std::cout << miller_rabin_test(big, 25, gen) << std::endl;
	//std::cout << miller_rabin_test(++big, 25, gen) << std::endl;
	////std::cout << miller_rabin_test(10, 25, gen);
	////cpp_int x = boost::multiprecision::powm(1, 1, 1);
	

	using namespace boost::multiprecision;
	auto res = TonelliShanks(5, 61);
	Print(res);
	return 0;
}
