#include <execution>

#include "QuadraticResidueDLOG.h"
#include "MathsFunctions.h"
#include "ModuloComprasion.h"

using namespace boost::multiprecision;
using namespace std;

using namespace Math;

bool CheckRoot(cpp_int a, cpp_int b, cpp_int c, cpp_int root) { return powm(a, root, c) == b; }

namespace
{
    mutex m;
}

res_container CalcLevel(res_container n_values, cpp_int p, int degree)
{
    res_container next_level_data;

	for_each(execution::par, begin(n_values), end(n_values), [&](cpp_int n)
		{
			auto res = ModuloComprasion(degree, n, p);
			if (res)
			{
				auto roots = res.value();
				lock_guard<mutex> guard(m);
				copy(begin(roots), end(roots), back_inserter(next_level_data));
			}
		});

    return next_level_data;
}

optional<cpp_int> k1;
cpp_int findValue;

optional<cpp_int> CalcDegree(int degree, cpp_int a, cpp_int b, cpp_int c)
{
    cpp_int level = 0;
    level_data allLevels;
    res_container levelData = {b};

    while (!levelData.empty())
    {
        if (!k1)
        {
            k1 = degree;
            findValue = powm(a, *k1, c);
            cout << "Число для поиска: " << findValue << endl;
        }

        levelData = CalcLevel(levelData, c, degree);

        cout << "Степень вычета = " << ++level << ":";
        for (auto &val : levelData) cout << " " << val;
        cout << endl;

        auto it = find(begin(allLevels), end(allLevels), levelData);
        if (it != end(allLevels))
        {
            cout << "Следующий уровень: ";
            copy(begin(levelData), end(levelData), ostream_iterator<cpp_int>{cout, " "});
            cout << "является повторением уровня " << distance(begin(allLevels), it) + 1 << endl;
            return nullopt;
        }

        if (find(begin(levelData), end(levelData), findValue) != end(levelData))
        {
            cout << "Содержит " << findValue << ". Проверка уровня:";
            auto possibleRoot = (*k1 * Pow(degree, level)) % (c - 1);
            cout << endl << "Корень: " << possibleRoot;
            auto checkResult = CheckRoot(a, b, c, possibleRoot);
            cout << endl << "Проверка корня: " << (checkResult ? "Подходит" : "Не подходит");
            if (checkResult) return make_optional(possibleRoot);
        }

        allLevels.push_back(levelData);
    }

    cout << "Когда степень равна " << degree << ", при b = " << b << " и p = " << c << " нет корней" << endl;
    return nullopt;
}

optional<cpp_int> FindRoot(cpp_int a, cpp_int b, cpp_int c)
{
    cout << a << "^x = " << b << "(mod " << c << ")" << endl;
    k1 = nullopt;
    int prime = 2;

    while (true)
    {
        cout << "Расчёт " << prime << " степени:" << endl;
        auto possibleRoot = CalcDegree(prime, a, b, c);
        if (possibleRoot) return possibleRoot;
        prime = NextPrimeInt(prime);
    }
}
