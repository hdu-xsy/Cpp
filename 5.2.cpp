#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class BigInteger
{
private:
	int length;
	int n[201];
	int sign;
public:		
	BigInteger();
	BigInteger(string str);
	BigInteger operator=(const BigInteger &b);
	BigInteger operator+(const BigInteger &b);
	BigInteger operator-(const BigInteger &b);	
	BigInteger plus(const BigInteger &b);
	BigInteger minus(const BigInteger &b);
	void print();
};
BigInteger::BigInteger()
{
	for (int i = 0; i < 201; i++)
	{
		n[i] = 0;
	}
	length = 201;
	sign = 1;
}
BigInteger::BigInteger(string str)
{
	int si=0;
	for (int i = 0; i < 201; i++)
	{
		n[i] = 0;
	}
	length = str.length();
	if (str[0] == '-')
	{
		si = 1;
		sign = -1;
	}
	else
	{
		si = 0;
		sign = 1;
	}
	for (int i = 0; i < str.length()-si; i++)
	{
		if (str[str.length()-i-1] >= '0'&& str[str.length() - i - 1] <= '9')
		{
			n[i]= str[str.length() - i - 1] - '0';
		}
	}
}


BigInteger BigInteger::operator=(const BigInteger &b)
{
	if (this != &b)
	{
		for (int i = 0; i < 201 ; i++)
		{
			n[i]=b.n[i];
		}
	}
	sign = b.sign;
	length = b.length;
	return *this;
}

BigInteger BigInteger::operator+(const BigInteger &b)
{
	BigInteger c;
	if (sign == b.sign)
	{
		c = this->plus(b);		
		c.sign = sign;
	}
	else
	{
		c = this->minus(b);
		c.sign *= sign;
	}
	return c;
}
BigInteger BigInteger::operator-(const BigInteger &b)
{
	BigInteger c;
	if (sign == b.sign)
	{
		c = this->minus(b);
		c.sign = sign * c.sign;
	}
	else
	{
		c = this->plus(b);		
		c.sign = sign;
	}
	return c;
}

BigInteger BigInteger::plus(const BigInteger &b)
{
	int p = 0;
	BigInteger c;
	for (int i = 0; i < b.length; i++)
	{
		c.n[i] = (n[i] + b.n[i] + p) % 10;
		p = (n[i] + b.n[i] + p) / 10;
	}
	for (int i = b.length; i < length; i++)
	{
		c.n[i] = n[i];
	}
	c.n[b.length] += p;
	return c;
}

BigInteger BigInteger::minus(const BigInteger &b)
{
	int p = 0;
	BigInteger c;
	BigInteger big;
	BigInteger small;
	if (length == b.length)
	{
		for (int i = 0; i < length; i++)
		{
			if (n[i] < b.n[i])
			{
				small = *this;
				big = b;
				c.sign = -1;
				break;
			}
			else
			{
				big = *this;
				small = b;
				c.sign = 1;
				break;
			}
		}
	}
	else if(length < b.length)
	{
		small = *this;
		big = b;
		c.sign = -1;
	}	
	else
	{
		big = *this;
		small = b;
		c.sign = 1;
	}
	for (int i = 0; i < small.length; i++)
	{
		if (big.n[i] - small.n[i] + p < 0)
		{
			c.n[i] = 10 + big.n[i] - small.n[i] + p;
			p = -1;
		}
		else
		{
			c.n[i] = big.n[i] - small.n[i] + p;
			p = 0;
		}
	}
	for (int i = small.length; i < length; i++)
	{
		c.n[i] = big.n[i];
	}
	c.n[small.length] += p;
	return c;
}

void BigInteger::print()
{
	int begin = 0;
	for (int i = 200; i >= 0; i--)
	{
		if (n[i] != 0)
		{
			begin = i;
			break;
		}
	}
	if (begin == 0 && n[0] == 0)
	{
		sign = 1;
	}
	if (sign == -1)
	{
		cout << "-";
	}
	for (int i = begin; i >= 0; i--)
	{
		cout << n[i];
	}
	cout << endl;
}

void main()
{
	string s1,s2;
	cin >> s1 >> s2;
	BigInteger b1 = BigInteger(s1);
	BigInteger b2 = BigInteger(s2);
	BigInteger b3 = b1+b2;
	b3.print();
	b3 = b1-b2;
	b3.print();
	system("pause");

	
}


