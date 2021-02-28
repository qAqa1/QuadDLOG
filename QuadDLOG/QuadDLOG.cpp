﻿// QuadDLOG.cpp : Defines the entry point for the application.
//

#include "QuadDLOG.h"
#include "TonelliShanks.h"
#include "Util.h"
#include "Root.h"
#include "MathsFunctions.h"
#include "QuadraticResidueDLOG.h"

#include "CantorZassenhaus.h"

//#include <boost/multiprecision/cpp_int.hpp>
//#include <boost/math/special_functions/prime.hpp>
//#include <boost/multiprecision/miller_rabin.hpp>
//#include <iomanip>

//#include <boost/math/tools/polynomial.hpp>

#include <iostream>

using namespace std;

int main()
{
	//boost::math::tools::polynomial p;
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


	//using namespace boost::multiprecision;
	//auto res = TonelliShanks(5, 61);
	//Print(res);

	//setlocale(LC_ALL, "Russian");

 //   //auto root = FindRoot(41, 15, 7);
 //   //auto root = FindRoot(54696545758787, 100001, 70606432933607);
 //   auto root = FindRoot(31, 15, 61);
	//std::cout << std::endl << "Корень: " << root;




	//Polynomial p1 = Polynomial("x^12+x^11+2x^9+2x^8+2x^6+x^5+2x^4+2x^3");

	//std::cout << p1.DebugDescription();

	//auto rez = Factor(p1, 61);

	//for (auto p : rez) {
	//	cout << p.second << " " << p.first << " | " << p.first.DebugDescription() << endl;
	//}

	int a = 15;

	auto rez = CantorCantorModularComprassion(2, a, 61);

	for (auto num : rez) {
		cout << num << std::endl;
	}

	std::cout << "---------------";

	auto res = TonelliShanks(a, 61);
	Print(res);

	//std::cout << ToRoot(2, 5) << std::endl;
	//std::cout << "end";

	//std::cout << boost::multiprecision::powm(boost::multiprecision::cpp_int(2), boost::multiprecision::cpp_int(10), boost::multiprecision::cpp_int(5)) << std::endl;
	//std::cout << "end";
	//system("pause");

	//auto val = Math::FindBiggestPrimeNumInNum(3, 100);
	//auto val = Math::NextPrimeNum(7);
	//std::cout << val << std::endl;
	//std::cout << "end";
	////system("pause");

	return 0;
}
