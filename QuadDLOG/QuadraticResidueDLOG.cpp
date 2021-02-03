#include "QuadraticResidueDLOG.h"
#include "MathsFunctions.h"
#include "ModuloComprasion.h"
#include <cmath>   

using namespace boost::multiprecision;
using namespace Math;

boost::multiprecision::cpp_int ToRoot(boost::multiprecision::cpp_int val, boost::multiprecision::cpp_int twoPow)
{
    cpp_int two = 2;
    auto twoPart = (cpp_int)pow((int)two, (int)twoPow);
    //auto twoPart = std::pow(two, twoPow);
    auto primePart = FindBiggestPrimeNumInNum(twoPart, val);

    std::cout << "������� ������: " << twoPart << " ������� �����: " << primePart;

    return twoPart * primePart;
}

bool CheckRoot(cpp_int g, cpp_int n, cpp_int p, cpp_int root) { return powm(g, root, p) == n; }

res_container CalcLevel(res_container n_values, cpp_int p)
{
    res_container next_level_data;

    for (auto n : n_values)
    {
        auto res = ModuloComprasion(n, p);
        if (res)
        {
            next_level_data.push_back(res.value()[0]);
            next_level_data.push_back(res.value()[1]);
        }
    }

    return next_level_data;
}

boost::multiprecision::cpp_int FindRoot(cpp_int g, cpp_int n, cpp_int p)
{
    std::cout << g << "^x = " << n << "(mod " << p << ")" << std::endl;
    int level = 0;
    level_data all_levels;
    res_container levelData = { n };

    while (!levelData.empty())
    {
        //if (level > 6) return -1;

        std::cout << "level = " << level++ << ":";
        for (auto val : levelData)
        {
            std::cout << " " << val;
        }
        std::cout << std::endl;

        levelData = CalcLevel(levelData, p);
        auto it = std::find(std::begin(all_levels), std::end(all_levels), levelData);
        if (it != std::end(all_levels))
        {
            std::cout << "��������� �������: ";
            for (auto num : levelData) { std::cout << num << " "; }
            std::cout << " �������� ����������� ������ " << std::distance(std::begin(all_levels), it) + 1;
            return -1;
        }

        if (std::find(std::begin(levelData), std::end(levelData), n) != std::end(levelData))
        {
            std::cout << "�������� " << n << ". �������� ������:";
            for (auto val : levelData)
            {
                std::cout << std::endl << "��������: " << val << std::endl;
                auto possibleRoot = ToRoot(val, level);
                std::cout << std::endl << "������: " << possibleRoot;
                auto checkResult = CheckRoot(g, n, p, possibleRoot);
                std::cout << std::endl << "�������� �����: " << (checkResult ? "��������" : "�� ��������");
                if (checkResult) return possibleRoot;
                std::cout << std::endl << "--------------------------------";
            }

            std::cout << std::endl;
        }

        all_levels.push_back(levelData);
    }

    std::cout << "��� n = " << n << " � " << " p = " << p << " ��� ������";
    return -1;
}
