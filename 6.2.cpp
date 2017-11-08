#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Q
{
private:
	unsigned int numerator;
	unsigned int denominator;
	int sign;
public:		
	Q();
	Q(int a, int b);
	~Q();
	void simplify();
	Q plus(Q &r) const;
	Q minus(Q &r) const;
	Q operator=(Q &r);
	Q operator+(Q &r) const;
	Q operator-(Q &r) const;
	Q operator*(Q &r) const;
	Q operator/(Q &r) const;
	void print();
};

Q::Q()
{
	numerator = 0;
	denominator = 0;
	sign = 1;
}
Q::Q(int a, int b)
{
	if (a >= 0)
	{
		numerator = a;
		denominator = b;
		sign = 1;
	}
	else
	{
		numerator = -a;
		denominator = b;
		sign = -1;
	}
}

Q::~Q()
{

}

void Q::simplify()		//化简分数
{
	int i = numerator;
	int j = denominator;
	if (i < j)
	{
		int temp = i;
		i = j;
		j = temp;
	}
	while (j != 0)
	{
		int temp = i%j;
		i = j;
		j = temp;
	}
	numerator /= i;
	denominator /= i;
}

Q Q::plus(Q &r) const		//数值部分和运算
{
	Q c;
	c.denominator = denominator * r.denominator;
	c.numerator = numerator*r.denominator + denominator * r.numerator;
	return c;
}

Q Q::minus(Q &r) const		//数值部分差运算
{
	Q c;
	c.denominator = denominator * r.denominator;
	if (numerator * r.denominator >= r.numerator*denominator)
	{
		c.numerator = numerator*r.denominator - r.numerator *denominator;
		c.sign = 1;
	}
	else
	{
		c.numerator = r.numerator *denominator - numerator * r.denominator;
		c.sign = -1;
	}
	return c;
}

Q Q::operator=(Q &r)
{
	if (this != &r)
	{
		numerator = r.numerator;
		denominator = r.denominator;
		sign = r.sign;
	}
	return *this;
}

Q Q::operator+(Q &r) const
{
	Q c;
	if (r.sign == sign)
	{
		c = (*this).plus(r);
		c.sign = sign;
	}
	else
	{
		c = (*this).minus(r);
	}
	return c;
}

Q Q::operator-(Q &r) const
{
	Q c;
	if (r.sign == sign)
	{
		c = (*this).minus(r);
		c.sign *= sign;
	}
	else
	{
		c = (*this).plus(r);
		c.sign = sign;
	}
	return c;
}

Q Q::operator*(Q &r) const
{
	Q c;
	c.sign = sign * r.sign;
	c.numerator = numerator *r.numerator;
	c.denominator = denominator * r.denominator;
	return c;
}

Q Q::operator/(Q &r) const
{
	Q c;
	c.sign = sign * r.sign;
	c.numerator = numerator * r.denominator;
	c.denominator = denominator * r.numerator;
	return c;
}

void Q::print()		//输出分数(加入负号、考虑分母1和分子0)
{
	(*this).simplify();
	if(numerator == 0)
	{
		cout << "0";
	}
	else
	{
		if (sign == -1)
			cout << "-";
		cout << numerator;
		if (denominator != 1)
		{
			cout << "/" << denominator;
		}
	}
}


void main()
{
	int i1, i2, i3, i4;
	cin >> i1 >> i2 >> i3 >> i4;
	Q q1 = Q(i1, i2);
	Q q2 = Q(i3, i4);
	Q q3 = q1 + q2;
	q1.print();
	cout << endl;
	q2.print();
	cout << endl;
	q3.print();
	cout << "\t";
	q3 = q1 - q2;
	q3.print();
	cout << "\t";
	q3 = q1 * q2;
	q3.print();
	cout << "\t";
	q3 = q1 / q2;
	q3.print();
	
}


