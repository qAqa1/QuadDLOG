#pragma once

// https://github.com/stormtrooper1859/CantorZassenhaus

#include <vector>
#include <string>

#include <boost/multiprecision/cpp_int.hpp>

class Polynomial
{
private:
    std::vector<boost::multiprecision::cpp_int> coeff;

    void Prune();

    Polynomial(std::vector<boost::multiprecision::cpp_int> coeff) : coeff(coeff) {};

    static std::pair<Polynomial, Polynomial> DivInternal(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp);

public:
    Polynomial() {}

    Polynomial(std::string s);

    /// From x^n + a
    Polynomial(int n, boost::multiprecision::cpp_int a);

    Polynomial(const Polynomial &polynomial) : coeff(polynomial.coeff) {};

    Polynomial &operator= (const Polynomial &polynomial) = default;

    size_t GetDegree() const;

    std::string ToString(std::string default_variable_name = "x") const;
    operator std::string() const;
    explicit operator boost::multiprecision::cpp_int() const;

    Polynomial Diff(const boost::multiprecision::cpp_int& modp);

    Polynomial Zip(const int n) const;

    static Polynomial Add(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp);
    static Polynomial Sub(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp);
    static Polynomial Mul(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp);
    static Polynomial Div(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp);
    static Polynomial Mod(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp);
    static Polynomial GetOne();
    static Polynomial GetRandomPolynomial(int max_degree, const boost::multiprecision::cpp_int& modq);

    Polynomial Normalize(const boost::multiprecision::cpp_int& modp) const;

    bool IsZero() const;
    bool IsOne() const;

    friend bool operator== (const Polynomial &poly1, const Polynomial &poly2);
    friend bool operator< (const Polynomial &poly1, const Polynomial &poly2);
    friend bool operator!= (const Polynomial &poly1, const Polynomial &poly2);

    std::string DebugDescription() const;
};

std::ostream & operator<<(std::ostream & Str, Polynomial const & v);

Polynomial GCD(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp);
Polynomial ModPow(const Polynomial& a, boost::multiprecision::cpp_int b, const Polynomial& mod, const boost::multiprecision::cpp_int& modp);
