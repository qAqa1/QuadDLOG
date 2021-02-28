#pragma once

#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

#include "Polynomial.h"

/// find roots in b^n + a (mod p) -> b^n + (p - a) (mod p)
std::vector<boost::multiprecision::cpp_int> CantorCantorModularComprassion(int n, boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int p);

/// find roots in x^n + a (mod p)
std::vector<boost::multiprecision::cpp_int> CantorCalcModularComprassionRaw(int n, boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int p);

// https://github.com/stormtrooper1859/CantorZassenhaus
std::vector<std::pair<Polynomial, int>> Factor(const Polynomial& poly, const boost::multiprecision::cpp_int& modp);
