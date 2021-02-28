#include "QuadraticResidueDLOG.h"
#include "MathsFunctions.h"
#include "ModuloComprasion.h" 

using namespace boost::multiprecision;
using namespace Math;

cpp_int ToRoot(cpp_int val, cpp_int twoPow)
{
    cpp_int two = 2;
    //cpp_int twoPart = powm(two, twoPow, val);
    cpp_int twoPart = Pow(two, twoPow);
    auto primePart = FindBiggestPrimeNumInNum(twoPart, val);
    std::cout << "Степень двойки: " << twoPart << " Простое число: " << primePart;
    return twoPart * primePart;
}

bool CheckRoot(cpp_int g, cpp_int n, cpp_int p, cpp_int root) { return powm(g, root, p) == n; }

res_container CalcLevel(res_container n_values, cpp_int p, int degree)
{
    res_container next_level_data;

    for (auto n : n_values)
    {
        //std::cout << std::endl << "p в CalcLevel = " << p << std::endl;
        auto res = ModuloComprasion(degree, n, p);
        if (res)
        {
            auto roots = res.value();
            for (const auto &root : roots)
            {
                next_level_data.push_back(root);
            }        
        }
    }

    return next_level_data;
}

std::optional<boost::multiprecision::cpp_int> CalcDegree(int degree, cpp_int g, cpp_int n, cpp_int p)
{
    cpp_int level = 0;
    level_data all_levels;
    res_container levelData = { n };

    while (!levelData.empty())
    {
        //if (level > 6) return -1;

        levelData = CalcLevel(levelData, p, degree);

        std::cout << "level = " << level++ << ":";
        for (auto val : levelData)
        {
            std::cout << " " << val;
        }
        std::cout << std::endl;

        auto it = std::find(std::begin(all_levels), std::end(all_levels), levelData);
        if (it != std::end(all_levels))
        {
            std::cout << "Следующий уровень: ";
            for (auto num : levelData) { std::cout << num << " "; }
            std::cout << " является повторением уровня " << std::distance(std::begin(all_levels), it) + 1;
            return std::nullopt;
        }

        if (std::find(std::begin(levelData), std::end(levelData), n) != std::end(levelData))
        {
            std::cout << "Содержит " << n << ". Проверка уровня:";
            for (auto val : levelData)
            {
                std::cout << std::endl << "Значение: " << val << std::endl;
                auto possibleRoot = ToRoot(val, level);
                std::cout << std::endl << "Корень: " << possibleRoot;
                auto checkResult = CheckRoot(g, n, p, possibleRoot);
                std::cout << std::endl << "Проверка корня: " << (checkResult ? "Подходит" : "Не подходит");
                if (checkResult) return std::make_optional(possibleRoot);
                std::cout << std::endl << "--------------------------------";
            }

            std::cout << std::endl;
        }

        all_levels.push_back(levelData);
    }

    std::cout << "Когда степень равна " << degree << ", при n = " << n << " и p = " << p << " нет корней";
    return std::nullopt;
}

std::optional<cpp_int> FindRoot(cpp_int g, cpp_int n, cpp_int p)
{
    std::cout << g << "^x = " << n << "(mod " << p << ")" << std::endl;

    int prime = 2;

    while (true)
    {
        std::cout << "Рассчет " << prime << " степени:" << std::endl;
        auto possibleRoot = CalcDegree(prime, g, n, p);
        if (possibleRoot.has_value()) return possibleRoot;
        prime = NextPrimeInt(prime);
        std::cout << std::endl << std::endl;
    }

    //return CalcDegree(7, g, n, p);
}
