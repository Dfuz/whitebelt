#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>
#include <set>
using namespace std;

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
		if (denominator == 0) throw invalid_argument("Invalid argument");
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

	Rational operator+(const Rational& rhs) const
	{
		if (den != rhs.den)
		{
			return Rational{num * rhs.den + rhs.num * den, den * rhs.den};
		}
		else return Rational{num + rhs.num, den};
	}
	Rational operator-(const Rational& rhs) const
	{
		if (den != rhs.den)
		{
			return Rational{num * rhs.den - rhs.num * den, den * rhs.den};
		}
		else return Rational{num - rhs.num, den};
	}
	Rational operator*(const Rational& rhs) const
	{
		return Rational{num * rhs.num, den * rhs.den};
	}
	Rational operator/(const Rational& rhs) const
	{
		if (rhs.num == 0) throw std::domain_error("Division by zero");
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
	Rational firstRatio, secondRatio, resultRatio;
	char operation;
	const set<char> allowedOperations = {'+', '-', '*', '/' };
	try
	{
		cin >> firstRatio;
		while (cin.peek() == ' ' && cin.peek() != EOF) cin.ignore(1);
		if (allowedOperations.find(cin.peek()) != end(allowedOperations))
			cin >> operation;
		else throw runtime_error("Unallowed operation readed!");
		cin >> secondRatio;

		switch (operation)
		{
		case '+':
			resultRatio = firstRatio + secondRatio;
			break;
		case '-':
			resultRatio = firstRatio - secondRatio;
			break;
		case '/':
			resultRatio = firstRatio / secondRatio;
			break;
		case '*':
			resultRatio = firstRatio * secondRatio;
			break;
		default:
			break;

		}
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		return 1;
	}
	cout << resultRatio << endl;
	return 0;
}