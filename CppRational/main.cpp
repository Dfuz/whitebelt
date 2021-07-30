#include <iostream>
#include <cmath>
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
			return Rational{ num * rhs.den + rhs.num * den, den * rhs.den };
		}
		else return Rational{ num + rhs.num, den };
	}
	Rational& operator-(const Rational& rhs) const
	{
		if (den != rhs.den)
		{
			return Rational{ num * rhs.den - rhs.num * den, den * rhs.den };
		}
		else return Rational{ num - rhs.num, den };
	}
	bool operator==(const Rational& rhs) const
	{
		return num == rhs.num && den == rhs.den;
	}
};

int main()
{
	{
		Rational r1(4, 6);
		Rational r2(2, 3);
		bool equal = r1 == r2;
		if (!equal) {
			cout << "4/6 != 2/3" << endl;
			return 1;
		}
	}

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a + b;
		bool equal = c == Rational(2, 1);
		if (!equal) {
			cout << "2/3 + 4/3 != 2" << endl;
			return 2;
		}
	}

	{
		Rational a(5, 7);
		Rational b(2, 9);
		Rational c = a - b;
		bool equal = c == Rational(31, 63);
		if (!equal) {
			cout << "5/7 - 2/9 != 31/63" << endl;
			return 3;
		}
	}
	cout << "OK" << endl;
	return 0;
}