#include "CantorZassenhaus.h"

#include <algorithm>
#include <chrono>
#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>

std::vector<std::pair<Polynomial, int>> SquareFreeDecomposition(const Polynomial& poly, const boost::multiprecision::cpp_int& modp) {
    std::vector<std::pair<Polynomial, int>> result;

    Polynomial a = poly;
    Polynomial c;
    int m = 1;

    do {
        auto ad = a.Diff(modp);
        c = GCD(a, ad, modp);
        auto w = Polynomial::Div(a, c, modp);
        int i = 1;
        while (!w.IsOne()) {
            auto y = GCD(w, c, modp);
            auto qq = Polynomial::Div(w, y, modp);
            if (!qq.IsOne()) {
                result.push_back({ qq, i * m });
            }
            w = y;
            c = Polynomial::Div(c, y, modp);
            i++;
        }
        if (!c.IsOne()) {
            a = c.Zip(static_cast<int>(modp));
            m = m * static_cast<int>(modp);
        }
    } while (!c.IsOne());

	return result;
}

std::vector<std::pair<Polynomial, int>> DistinctDegreeFactorization(const Polynomial& poly, const boost::multiprecision::cpp_int& modp) {
    std::vector<std::pair<Polynomial, int>> result;

    Polynomial h("1x^1");
    Polynomial href = h;
    auto f = poly;
    int i = 1;

    while (!f.IsOne()) {
        h = ModPow(h, modp, poly, modp);
        auto sbs = Polynomial::Sub(h, href, modp);
        auto g = GCD(sbs, f, modp);
        if (!g.IsOne()) {
            result.push_back({ g, i });
            f = Polynomial::Div(f, g, modp);
        }
        i++;
    }

    return result;
}



std::vector<Polynomial> EqualDegreeFactorization(const Polynomial& poly, int degree, const boost::multiprecision::cpp_int& modp) {
    if (static_cast<int>(poly.GetDegree()) == degree) {
        return std::vector<Polynomial>({ poly });
    }

    std::vector<Polynomial> result;

    Polynomial g = Polynomial::GetOne();
    Polynomial genpol;

    while (g.IsOne() || g == poly) {
        int deg = static_cast<int>(poly.GetDegree()) - 1;
        genpol = Polynomial::GetRandomPolynomial(deg, modp);
        auto gp = Polynomial::Mod(genpol, poly, modp);
        g = GCD(gp, poly, modp);
        if (g.IsOne()) {
            Polynomial h;
            if (modp == 2) {
                for (size_t j = 0; j < degree; j++)
                {
                    boost::multiprecision::cpp_int t = boost::multiprecision::pow(boost::multiprecision::cpp_int(2), 2);

                    auto t2 = ModPow(gp, t, poly, modp);
                    h = Polynomial::Mod(Polynomial::Add(h, t2, modp), poly, modp);
                }
            } else {

                boost::multiprecision::cpp_int t = boost::multiprecision::pow(modp, degree);
                t /= 2;

                h = ModPow(gp, t, poly, modp);
                h = Polynomial::Sub(h, Polynomial::GetOne(), modp);
            }
            g = GCD(h, poly, modp);
        }
    }
    auto g2 = Polynomial::Div(poly, g, modp);
    auto r1 = EqualDegreeFactorization(g, degree, modp);
    auto r2 = EqualDegreeFactorization(g2, degree, modp);

    result.insert(result.end(), r1.begin(), r1.end());
    result.insert(result.end(), r2.begin(), r2.end());

    return result;
}


std::vector<Polynomial> FactorSquareFree(const Polynomial& poly, const boost::multiprecision::cpp_int& modp) {
    std::vector<Polynomial> result;

    auto distDeg = DistinctDegreeFactorization(poly, modp);

    for (auto t : distDeg) {
        auto r1 = EqualDegreeFactorization(t.first, t.second, modp);
        result.insert(result.end(), r1.begin(), r1.end());
    }

    return result;
}

std::vector<boost::multiprecision::cpp_int> CantorModularComprassion(int n, boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int p)
{
    //std::cout << std::endl << "Вызов кантора: n = " << n << ", a = " << a << " , p = " << p << std::endl;

    if (a >= p || a < 0)
    {
        auto modWithNegative = [](boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b)
        {
            boost::multiprecision::cpp_int r = a % b;
            return r < 0 ? r + b : r;
        };

        a = modWithNegative(a, p);
    }

    //std::cout << std::endl << "a = " << a;
    //std::cout << std::endl << "Итог: n = " << n << ", p - a = " << p - a << " , p = " << p << std::endl;
    auto roots = CantorCalcModularComprassionRaw(n, p - a, p);

    //std::cout << "Корни: ";

    //for (const auto& root : roots)
    //{
    //    std::cout << root << ", ";
    //}

    //std::cout << std::endl;

    return CantorCalcModularComprassionRaw(n, p - a, p);
}

std::vector<boost::multiprecision::cpp_int> CantorCalcModularComprassionRaw(int n, boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int p)
{
    Polynomial poly(n, a);

    //std::cout << std::endl << "Полином: " << poly << std::endl;

    std::vector<boost::multiprecision::cpp_int> result;
    std::vector<std::pair<Polynomial, int>> sqrfree = SquareFreeDecomposition(poly, p);

    for (auto const& value : sqrfree)
{
        auto r1 = FactorSquareFree(value.first, p);
        for (auto& el : r1)
        {
            if (el.GetDegree() == 1)
            {
                result.push_back({ static_cast<boost::multiprecision::cpp_int>(el) });
            }
        }
    }

    return result;
}

std::vector<std::pair<Polynomial, int>> Factor(const Polynomial& poly, const boost::multiprecision::cpp_int& modp) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::vector<std::pair<Polynomial, int>> result;
    std::vector<std::pair<Polynomial, int>> sqrfree = SquareFreeDecomposition(poly, modp);

	for (auto const& value : sqrfree) {
        auto r1 = FactorSquareFree(value.first, modp);
        for (auto& el : r1) result.push_back({ el, value.second });
	}

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Computation time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

	return result;
}

