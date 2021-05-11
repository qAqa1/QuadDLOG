// QuadDLOG.cpp : Defines the entry point for the application.

#include "TonelliShanks.h"
#include "QuadraticResidueDLOG.h"

#include <chrono>

using namespace std;

int main()
{
//	setlocale(LC_ALL, "Russian");

	//auto root = FindRoot(41, 15, 7);

//    SetConsoleCP(1251); //установка кодовой страницы win-cp 1251 в поток ввода
//    SetConsoleOutputCP(1251); //установка кодовой страницы win-cp 1251 в поток

//    SetConsoleCP(866);
//    SetConsoleOutputCP(866);

    setlocale(LC_ALL, "ru_RU.UTF-8");
    auto starTimer = chrono::steady_clock::now();

	//auto primePart = FindBiggestPrimeNumInNum(4, 21);
	//cout << primePart;
//	auto root = FindRoot(54696545758787, 100001, 70606432933607);
//	auto root = FindRoot(3, 13, 17);
//	auto root = FindRoot(31, 15, 61);
//	auto root = FindRoot(27, 520, 547);
    auto root = FindRoot(10, 64, 107); // 20 или 562949953421312
//	auto root = FindRoot(31, 46, 61);

//	auto root = FindRoot(2, 24322, 30203); // 1267650600228229401496703205376
//	auto root = FindRoot(2, 21740, 30323);
//	auto root = FindRoot(2, 28620, 30539);
//    auto root = FindRoot(5, 30994, 31607);

//	auto root = FindRoot(2, 16190, 30803);
//	auto root = FindRoot(13, 10, 9973);

    auto endTimer = chrono::steady_clock::now();

	if (root)
		std::cout << std::endl << "Корень: " << *root;

    cout << endl << endl << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>((endTimer - starTimer)).count() << "ms";

//	auto rez = CantorCalcModularComprassionRaw(3, 4, 7);

//	auto rez = CantorCalcModularComprassionRaw(3, 28620 , 30539);
//	auto rez = CantorModularComprassion(3, 28620 , 30539);
//
//	for (auto num : rez) {
//		cout << num << std::endl;
//	}

	//Polynomial p1 = Polynomial("x^12+x^11+2x^9+2x^8+2x^6+x^5+2x^4+2x^3");

	//std::cout << p1.DebugDescription();

	//auto rez = Factor(p1, 61);

	//for (auto p : rez) {
	//	cout << p.second << " " << p.first << " | " << p.first.DebugDescription() << endl;
	//}

	//int a = 15;

	//auto rez = CantorModularComprassionRaw(2, a, 61);

	//for (auto num : rez) {
	//	cout << num << std::endl;
	//}

	//std::cout << "---------------";

	//auto res = TonelliShanks(a, 61);
	//Print(res);

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
