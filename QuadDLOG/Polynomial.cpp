#include "Polynomial.h"

#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/mod_inverse.hpp>
#include <boost/algorithm/string.hpp>

Polynomial::Polynomial(std::string str)
{
	std::vector<std::string> monoms_string;
	boost::split(monoms_string, str, boost::is_any_of("+"));
	std::vector<std::pair<boost::multiprecision::cpp_int, int>> monoms(monoms_string.size());

	for (size_t i = 0; i < monoms.size(); i++)
	{
		std::vector<std::string> ss;
		boost::split(ss, monoms_string[i], boost::is_any_of("x"));

		boost::multiprecision::cpp_int coeff;
		int pwr;

		if (ss.size() == 1) {
			pwr = 0;
		}
		else {
			if (ss[1] == "") {
				pwr = 1;
			}
			else {
				pwr = stoi(ss[1].substr(1, ss[1].size()));
			}
		}

		if (ss[0] == "") {
			coeff = 1;
		}
		else {
			coeff = boost::multiprecision::cpp_int(ss[0]);
		}
		monoms[i] = { coeff, pwr };
	}


	int pwr = monoms[0].second;
	std::vector<boost::multiprecision::cpp_int> result(static_cast<size_t>(pwr) + 1);

	for (auto pr : monoms)
	{
		result[pr.second] = pr.first;
	}

	this->coeff = result;
}

Polynomial::Polynomial(int n, boost::multiprecision::cpp_int a)
{
	coeff = std::vector<boost::multiprecision::cpp_int>(static_cast<size_t>(n) + 1);
	coeff.front() = a;
	coeff.back() = 1;
}

void Polynomial::Prune()
{
	for (int i = static_cast<int>(this->coeff.size()); i > 0 && this->coeff.back() == 0; i--)
	{
		this->coeff.pop_back();
	}
}

size_t Polynomial::GetDegree() const
{
	return this->coeff.size() - 1;
}

std::string Polynomial::ToString(std::string default_variable_name) const
{
	int degree = static_cast<int>(this->coeff.size() - 1);
	std::stringstream result;

	for (int i = degree; i >= 0; i--)
	{
		if (this->coeff[i] == 0) continue;
		if (!result.str().empty()) {
			result << "+";
		}

		if (this->coeff[i] != 1 || i == 0) {
			std::stringstream ss;
			ss << this->coeff[i];
			result << ss.str();
		}
		if (i != 0) {
			result << default_variable_name;
			if (i != 1)
			{
				result << "^" + std::to_string(i);
			}
		}
	}

	std::string resultStr = result.str();
	if (resultStr.empty()) return "0";
	return resultStr;
}

Polynomial::operator std::string() const { return ToString(); }
Polynomial::operator boost::multiprecision::cpp_int() const { return coeff.front(); }

Polynomial Polynomial::Diff(const boost::multiprecision::cpp_int& modp)
{
	std::vector<boost::multiprecision::cpp_int> v(this->GetDegree());

	for (size_t i = 0; i < this->GetDegree(); i++)
	{
		v[i] = (this->coeff[i + 1] * (i + 1)) % modp;
	}

	auto p = Polynomial(v);
	p.Prune();

	return p;
}

Polynomial Polynomial::Zip(const int n) const
{
	std::vector<boost::multiprecision::cpp_int> v(this->GetDegree() / n + 1);

	for (size_t i = 0; i <= this->GetDegree(); i += n)
	{
		v[i / n] = this->coeff[i];
	}

	return Polynomial(v);
}

std::ostream& operator<<(std::ostream& strm, const Polynomial& poly) { return strm << poly.ToString(); }

Polynomial Polynomial::Add(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp)
{
	if (a.IsZero()) return b;
	if (b.IsZero()) return a;

	const Polynomial& a1 = a.GetDegree() > b.GetDegree() ? a : b;
	const Polynomial& b1 = a.GetDegree() > b.GetDegree() ? b : a;

	std::vector<boost::multiprecision::cpp_int> v(a1.GetDegree() + 1);

	for (size_t i = 0; i <= b1.GetDegree(); i++)
	{
		v[i] = (a1.coeff[i] + b1.coeff[i] + modp) % modp;
	}

	for (size_t i = b1.GetDegree() + 1; i <= a1.GetDegree(); i++)
	{
		v[i] = a1.coeff[i];
	}

	Polynomial p = Polynomial(v);
	p.Prune();
	return p;
}

Polynomial Polynomial::Mul(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp)
{
	if (a.IsZero() || b.IsZero()) {
		return Polynomial({});
	}

	std::vector<boost::multiprecision::cpp_int> v(a.GetDegree() + b.GetDegree() + 1);

	for (size_t i = 0; i <= a.GetDegree(); ++i) {
		for (size_t j = 0; j <= b.GetDegree(); ++j) {
			v[i + j] = (v[i + j] + a.coeff[i] * b.coeff[j] % modp + modp) % modp;
		}
	}

	return Polynomial(v);
}

Polynomial Polynomial::Sub(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp)
{
	std::vector<boost::multiprecision::cpp_int> v = b.coeff;

	for (size_t i = 0; i < v.size(); i++) {
		v[i] = modp - v[i];
	}

	return Add(a, Polynomial(v), modp);
}

std::pair< Polynomial, Polynomial> Polynomial::DivInternal(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp)
{
	boost::multiprecision::cpp_int bl = b.coeff.back();
	Polynomial b2 = b.Normalize(modp);

	int degree_of_result = static_cast<int>(a.GetDegree() - b.GetDegree() + 1);

	if (degree_of_result < 1) return { Polynomial({}), a };

	std::vector<boost::multiprecision::cpp_int> coeff_result(degree_of_result);

	Polynomial at = a;

	for (size_t i = 0; i < degree_of_result; i++)
	{
		coeff_result[static_cast<size_t>(degree_of_result) - 1 - i] = at.coeff[a.GetDegree() - i];

		for (size_t j = 0; j <= b2.GetDegree(); j++)
		{
			at.coeff[a.GetDegree() - i - j] = (at.coeff[a.GetDegree() - i - j] - coeff_result[static_cast<size_t>(degree_of_result) - 1 - i] * b2.coeff[b2.GetDegree() - j]) % modp;
			at.coeff[a.GetDegree() - i - j] = (at.coeff[a.GetDegree() - i - j] + modp) % modp;
		}
	}

	Polynomial quo = Mul(Polynomial(coeff_result), Polynomial({ bl }), modp);

	at.Prune();

	return { quo, at };
}

Polynomial Polynomial::Div(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp)
{
	return Polynomial::DivInternal(a, b, modp).first;
}

Polynomial Polynomial::Mod(const Polynomial& a, const Polynomial& b, const boost::multiprecision::cpp_int& modp)
{
	return Polynomial::DivInternal(a, b, modp).second;
}

Polynomial Polynomial::GetOne() { return Polynomial({ boost::multiprecision::cpp_int(1) }); }

bool operator==(const Polynomial& poly1, const Polynomial& poly2) { return poly1.coeff == poly2.coeff; }

bool operator!=(const Polynomial& poly1, const Polynomial& poly2) { return !(poly1 == poly2); }

bool operator< (const Polynomial& poly1, const Polynomial& poly2) {
	if (poly1.coeff.size() == poly2.coeff.size()) {
		for (int i = poly1.coeff.size() - 1; i >= 0; i--) {
			if (poly1.coeff[i] != poly2.coeff[i]) {
				return poly1.coeff[i] < poly2.coeff[i];
			}
		}

		return false;
	}

	return poly1.coeff.size() < poly2.coeff.size();
}

Polynomial GCD(const Polynomial& a1, const Polynomial& b1, const boost::multiprecision::cpp_int& modp)
{
	if (a1.IsZero()) {
		return b1;
	}
	if (b1.IsZero()) {
		return a1;
	}

	auto a = a1.Normalize(modp);
	auto b = b1.Normalize(modp);

	while (!b.IsZero()) {
		a = Polynomial::Mod(a, b, modp);
		auto z = a;
		a = b;
		b = z;
	}

	return a.Normalize(modp);
}

Polynomial ModPow(const Polynomial& a, boost::multiprecision::cpp_int b, const Polynomial& mod, const boost::multiprecision::cpp_int& modp)
{
	boost::multiprecision::cpp_int power = b;
	Polynomial rez = Polynomial::GetOne();
	Polynomial aa = a;
	while (power > 0) {
		if (power % 2 == 1) {
			rez = Polynomial::Mul(rez, aa, modp);
			rez = Polynomial::Mod(rez, mod, modp);
		}
		aa = Polynomial::Mul(aa, aa, modp);
		aa = Polynomial::Mod(aa, mod, modp);
		power /= 2;
	}
	return rez;
}

boost::multiprecision::cpp_int inversed_in_ring(boost::multiprecision::cpp_int& a, const boost::multiprecision::cpp_int& modp) {
	return boost::integer::mod_inverse(a, modp);;
}

Polynomial Polynomial::Normalize(const boost::multiprecision::cpp_int& modp) const
{
	boost::multiprecision::cpp_int bl = this->coeff.back();
	boost::multiprecision::cpp_int ib = inversed_in_ring(bl, modp);

	std::vector<boost::multiprecision::cpp_int> v = this->coeff;

	for (auto& el : v) el = (el * ib) % modp;

	return Polynomial(v);
}

bool Polynomial::IsZero() const { return this->coeff.size() == 0; }

bool Polynomial::IsOne() const { return this->coeff.size() == 1 && this->coeff[0] == 1; }

std::string Polynomial::DebugDescription() const
{
	std::stringstream ss;
	if (coeff.size() == 0) return "{}";
	ss << "{" << coeff.back();
	std::for_each(std::rbegin(coeff) + 1, std::rend(coeff),
		[&ss](boost::multiprecision::cpp_int val) { ss << ", " << val; });
	ss << "}";
	return ss.str();
}

Polynomial Polynomial::GetRandomPolynomial(int max_degree, const boost::multiprecision::cpp_int& modq)
{
	long long poly_seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::mt19937 rng(poly_seed);

	std::uniform_int_distribution<int> dist(0, static_cast<int>(modq) - 1);
	std::uniform_int_distribution<int> dist_degree(0, max_degree - 1);

	auto degree = dist_degree(rng) + 1;

	std::vector<boost::multiprecision::cpp_int> vr(static_cast<size_t>(degree) + 1);
	vr[degree] = 1;

	for (size_t i = 0; i < degree; i++) vr[i] = dist(rng);

	Polynomial result(vr);
	result.Prune();

	return result;
}
