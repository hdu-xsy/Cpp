#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInteger
{
private:

public:		
	vector<int> n;
	int length;
	BigInteger();
	BigInteger(string str);
	BigInteger operator=(const BigInteger &b);
	BigInteger operator+(const BigInteger &b);
	BigInteger operator-(const BigInteger &b);
	BigInteger operator*(const BigInteger &b);	
	void print();
};

BigInteger::BigInteger(string str)
{
	length = str.length();
	for (int i = 0; i < str.length(); i++)
	{
		if (str[str.length()-i-1] >= '0'&& str[str.length() - i - 1] <= '9')
		{
			n.push_back(str[str.length() - i - 1] - '0');
		}
	}
}
BigInteger BigInteger::operator=(const BigInteger &b)
{
	if (this != &b)
	{
		length = b.length;
		for (int i = 0; i < length; i++)
		{
			n.push_back(b.n[i]);
		}
	}
	return *this;
}

BigInteger BigInteger::operator+(const BigInteger &b)
{
	int p = 0;
	BigInteger c = *this;
	c.n.clear();
	for (int i = 0; i < b.length; i++)
	{
		c.n.push_back((n[i] + b.n[i]) % 10 + p);
		p = (n[i] + b.n[i]) / 10;
	}
	for (int i = b.length; i < length; i++)
	{
		c.n.push_back(n[i]);
	}
	c.n.push_back(0);
	c.n[b.length] += p;
	c.length = c.n.size();
	return c;
}
BigInteger BigInteger::operator-(const BigInteger &b)
{
	int p = 0;
	BigInteger c = *this;
	c.n.clear();
	for (int i = 0; i < b.length; i++)
	{
		if (n[i] - b.n[i] < 0)
		{
			c.n.push_back(10 + n[i] - b.n[i] + p);
			p = -1;
		}
		else
		{
			c.n.push_back(n[i] - b.n[i] + p);
			p = 0;
		}
	}
	for (int i = b.length; i < length; i++)
	{
		c.n.push_back(n[i]);
	}
	c.n.push_back(0);
	c.n[b.length] += p;
	c.length = c.n.size();
	return c;
}

BigInteger BigInteger::operator*(const BigInteger &b)
{
	BigInteger c = *this;
	c.n.clear();
	for (int i = 0; i < 402; i++)
	{
		c.n.push_back(0);
	}
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < b.length; j++)
		{
			c.n[i + j ] += (n[i] * b.n[j]) % 10;
			c.n[i + j +1] += (n[i] * b.n[j]) / 10;
		}
	}
	for (int i = 0; i < c.n.size()-1; i++)
	{
		c.n[i + 1] += c.n[i] / 10;
		c.n[i] = c.n[i] % 10;
	}
	c.length = c.n.size();
	return c;
}
void BigInteger::print()
{
	int begin = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		if (n[i] != 0)
		{
			begin = i;
			break;
		}
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
	cin >> s1;
	BigInteger b1 = BigInteger(s1);
	cin >> s2;
	BigInteger b2 = BigInteger(s2);
	BigInteger b3 = b1 + b2;
	b3.print();
	BigInteger b4 = b1 - b2;
	b4.print();
	BigInteger b5 = b1 * b2;
	b5.print();
	system("pause");

	
}
