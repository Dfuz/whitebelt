#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>
#include <set>
using namespace std;

// Комментарии, которые говорят, что именно нужно реализовать в этой программе
class Rational
{
private:
	int num;
	int den;

	int gcd(int a, int b)
	{
		while (a != b)
		{
			if (a > b)
				std::swap(a, b);
			b -= a;
		}
		return a;
	}
public:
	Rational()
	{
		num = 0;
		den = 1;
	}

	Rational(int numerator, int denominator)
	{
		if (numerator == 0)
		{
			num = 0;
			den = 1;
			return;
		}
		if (denominator < 0)
		{
			denominator = -denominator;
			numerator = -numerator;
		}
		int divisor = gcd(abs(numerator), denominator);
		num = (numerator /= divisor);
		den = (denominator /= divisor);
	}

	int Numerator() const
	{
		return num;
	}

	int Denominator() const
	{
		return den;
	}

	Rational& operator+(const Rational& rhs) const
	{
		if (den != rhs.den)
		{
			return Rational{num * rhs.den + rhs.num * den, den * rhs.den};
		}
		else return Rational{num + rhs.num, den};
	}
	Rational& operator-(const Rational& rhs) const
	{
		if (den != rhs.den)
		{
			return Rational{num * rhs.den - rhs.num * den, den * rhs.den};
		}
		else return Rational{num - rhs.num, den};
	}
	Rational& operator*(const Rational& rhs) const
	{
		return Rational{num * rhs.num, den * rhs.den};
	}
	Rational& operator/(const Rational& rhs) const
	{
		if (rhs.num == 0) throw std::overflow_error("Divide by zero exception");
		return Rational{num * rhs.den, den * rhs.num};
	}
	friend ostream& operator<<(ostream& out, const Rational& ratio)
	{
		out << ratio.num << '/' << ratio.den;
		return out;
	}
	friend istream& operator>>(istream& in, Rational& ratio)
	{
		int numerator = ratio.num, denomitator = ratio.den;
		in >> numerator;
		if (!in) return in;
		if (in.peek() == '/') in.ignore(1);
		in >> denomitator;
		if (!in) return in;
		ratio = Rational{numerator, denomitator};
		return in;
	}
	bool operator==(const Rational& rhs) const
	{
		return num == rhs.num && den == rhs.den;
	}
	bool operator<(const Rational& rhs) const
	{
		if (den == rhs.den) return num < rhs.num;
		else 
		{
			int newLhsNum = 0, newRhsNum = 0;
			newLhsNum = num * rhs.den;
			newRhsNum = rhs.num * den;
			return newLhsNum < newRhsNum;
		}
	}
};

int main()
{
	{
		const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
		if (rs.size() != 3) {
			cout << "Wrong amount of items in the set" << endl;
			return 1;
		}

		vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
			cout << "Rationals comparison works incorrectly" << endl;
			return 2;
		}
	}

	{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2) {
			cout << "Wrong amount of items in the map" << endl;
			return 3;
		}
	}

	cout << "OK" << endl;
	return 0;
}