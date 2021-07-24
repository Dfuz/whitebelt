#include <iostream>
#include <cmath>
using namespace std;

// Комментарии, которые говорят, что именно нужно реализовать в этой программе
class Rational
{
private:
	int num;
	int den;

public:	int gcd(int a, int b)
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

};

int main()
{
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }
	cout << "OK" << endl;
	return 0;
}