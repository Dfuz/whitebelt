#include <iostream>
#include <sstream>
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
};

int main()
{
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("");
		Rational r;
		bool correct = !(input >> r);
		if (!correct) {
			cout << "Read from empty stream works incorrectly" << endl;
			return 3;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 4;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 5;
		}
	}

	{
		istringstream input1("1*2"), input2("1/"), input3("/4");
		Rational r1, r2, r3;
		input1 >> r1;
		input2 >> r2;
		input3 >> r3;
		bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
		if (!correct) {
			cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
				<< r1 << " " << r2 << " " << r3 << endl;

			return 6;
		}
	}

	cout << "OK" << endl;
	return 0;
}