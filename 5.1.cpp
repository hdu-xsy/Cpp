#include <iostream>
#include <string>
using namespace std;

class BigInteger
{
private:
	int length;
	int n[402];
public:		
	BigInteger();
	BigInteger(string str);
	BigInteger operator=(const BigInteger &b);
	BigInteger operator+(const BigInteger &b);
	BigInteger operator-(const BigInteger &b);
	BigInteger operator*(const BigInteger &b);	
	void print();
};
BigInteger::BigInteger()
{
	for (int i = 0; i < 402; i++)
	{
		n[i] = 0;
	}
	length = 402;
}
BigInteger::BigInteger(string str)
{
	for (int i = 0; i < 402; i++)
	{
		n[i] = 0;
	}
	length = str.length();
	for (int i = 0; i < str.length(); i++)
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
		for (int i = 0; i < 402 ; i++)
		{
			n[i]=b.n[i];
		}
	}
	return *this;
}

BigInteger BigInteger::operator+(const BigInteger &b)
{
	int p = 0;
	BigInteger c;
	for (int i = 0; i < b.length; i++)
	{
		c.n[i] = (n[i] + b.n[i]+p) % 10;
		p = (n[i]+b.n[i]+p)/10;
	}
	for (int i = b.length; i < length; i++)
	{
		c.n[i] = n[i];
	}
	c.n[b.length] += p;
	return c;
}
BigInteger BigInteger::operator-(const BigInteger &b)
{
	int p = 0;
	BigInteger c;
	for (int i = 0; i < b.length; i++)
	{
		if (n[i] - b.n[i] < 0)
		{
			c.n[i] = 10 + n[i] - b.n[i] + p;
			p = -1;
		}
		else
		{
			c.n[i] = n[i] - b.n[i] + p;
			p = 0;
		}
	}
	for (int i = b.length; i < length; i++)
	{
		c.n[i] = n[i];
	}
	c.n[b.length] += p;
	return c;
}

BigInteger BigInteger::operator*(const BigInteger &b)
{
	BigInteger c;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < b.length; j++)
		{
			c.n[i + j ] += (n[i] * b.n[j]) % 10;
			c.n[i + j +1] += (n[i] * b.n[j]) / 10;
		}
	}
	for (int i = 0; i < 402; i++)
	{
		c.n[i + 1] += c.n[i] / 10;
		c.n[i] = c.n[i] % 10;
	}
	return c;
}
void BigInteger::print()
{
	int begin = 0;
	for (int i = 401; i >= 0; i--)
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
	cin >> s1 >> s2;
	BigInteger b1 = BigInteger(s1);
	BigInteger b2 = BigInteger(s2);
	BigInteger b3;
	b3 = b1 + b2;
	b3.print();
	b3 = b1 - b2;
	b3.print();
	b3 = b1 * b2;
	b3.print();
	
}
