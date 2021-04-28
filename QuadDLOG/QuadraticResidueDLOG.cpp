#include <execution>

#include "QuadraticResidueDLOG.h"
#include "MathsFunctions.h"
#include "ModuloComprasion.h"

using namespace boost::multiprecision;
using namespace Math;

bool CheckRoot(cpp_int g, cpp_int n, cpp_int p, cpp_int root) { return powm(g, root, p) == n; }

namespace
{
    std::mutex m;;
}

res_container CalcLevel(res_container n_values, cpp_int p, int degree)
{
    res_container next_level_data;

	std::for_each(std::execution::par, std::begin(n_values), std::end(n_values), [&](boost::multiprecision::cpp_int n)
		{
			auto res = ModuloComprasion(degree, n, p);
			if (res)
			{
				auto roots = res.value();
				std::lock_guard<std::mutex> guard(m);
				std::copy(std::begin(roots), std::end(roots), std::back_inserter(next_level_data));
			}
		});

    return next_level_data;
}

std::optional<cpp_int> k1;
cpp_int find_value;

std::optional<boost::multiprecision::cpp_int> CalcDegree(int degree, cpp_int a, cpp_int b, cpp_int c) {
    std::cout << a << "^x = " << b << "(mod " << c << ")" << std::endl;

    cpp_int level = 0;
    level_data all_levels;
    res_container levelData = {b};

    while (!levelData.empty()) {
        if (!k1) {
            k1 = degree;
            find_value = powm(a, *k1, c);
            std::cout << std::endl << "Число для поиска: " << find_value << std::endl;
        }

        levelData = CalcLevel(levelData, c, degree);

        std::cout << "level = " << ++level << ":";
        for (auto &val : levelData) std::cout << " " << val;
        std::cout << std::endl;

        auto it = std::find(std::begin(all_levels), std::end(all_levels), levelData);
        if (it != std::end(all_levels)) {
            std::cout << "Следующий уровень: ";
            std::copy(std::begin(levelData), std::end(levelData), std::ostream_iterator<cpp_int>{std::cout, " "});
            std::cout << " является повторением уровня " << std::distance(std::begin(all_levels), it) + 1;
            return std::nullopt;
        }

        if (std::find(std::begin(levelData), std::end(levelData), find_value) != std::end(levelData))
        {
            std::cout << "Содержит " << find_value << ". Проверка уровня:";
            auto possibleRoot = *k1 * Pow(degree, level);
            std::cout << std::endl << "Корень: " << possibleRoot;
            auto checkResult = CheckRoot(a, b, c, possibleRoot);
            std::cout << std::endl << "Проверка корня: " << (checkResult ? "Подходит" : "Не подходит");
            if (checkResult) return std::make_optional(possibleRoot);
            std::cout << std::endl << "--------------------------------";
            std::cout << std::endl;
        }

        all_levels.push_back(levelData);
    }

    std::cout << "Когда степень равна " << degree << ", при b = " << b << " и p = " << c << " нет корней";
    return std::nullopt;
}

std::optional<cpp_int> FindRoot(cpp_int a, cpp_int b, cpp_int c) {
    k1 = std::nullopt;

    std::cout << a << "^x = " << b << "(mod " << c << ")" << std::endl;

    int prime = 2;

    while (true) {
        std::cout << "______________________________________________________" << std::endl;
        std::cout << "Рассчет " << prime << " степени:" << std::endl;
        auto possibleRoot = CalcDegree(prime, a, b, c);
        if (possibleRoot) return possibleRoot;
        prime = NextPrimeInt(prime);
        std::cout << std::endl << std::endl;
    }

//	return CalcDegree(3, a, b, c);
}
