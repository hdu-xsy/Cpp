#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class BigInteger
{
private:

	
public:	
	int *n;
	int length;
	BigInteger(string str);
	BigInteger operator=(const BigInteger &b);
	BigInteger operator+(const BigInteger &b);
	BigInteger operator-(const BigInteger &b);
	BigInteger operator*(const BigInteger &b);	
	~BigInteger();
};

BigInteger::BigInteger(string str)
{
	length = str.length();
	n = (int*)calloc(length,sizeof(int));
	for (int i = 0; i < str.length(); i++)
	{
		if (str[str.length()-i-1] >= '0'&& str[str.length() - i - 1] <= '9')
		{
			n[i] = str[str.length() - i - 1] - '0';
		}
	}
}

BigInteger BigInteger::operator+(const BigInteger &b)
{
	return *this;
}
BigInteger::~BigInteger()
{
	delete[] n;
}
void main()
{
	string s1;
	cin >> s1;
	BigInteger b1 = BigInteger(s1);
	cout << b1.length  << endl << b1.n[1];
	system("pause");

	
}
