#include <iostream>
using	namespace	std;

class	CYls;   //向前声明
CYls	operator + (int x, const CYls	&rhs);	//整数+有理数
ostream	&  operator << (ostream &os, const CYls &rhs); //有理数输出

class	CYls {
	friend CYls	operator + (int x, const CYls	&rhs);
	friend	ostream	&  operator << (ostream &os, const CYls &rhs);
private :
	int	m_fenZi, m_fenMu;//分子、分母
	void _Normalize ();  //化简

public :
	explicit CYls (int fenZi = 0, int fenMu = 1); //有理数构造函数
	CYls operator+ (const CYls &rhs) const;		//有理数相加
	CYls operator- (const CYls &rhs) const;		//有理数相减
	CYls operator* (const CYls &rhs)  const;	//有理数相乘
	CYls operator / (const CYls &rhs) const;	//有理数相除
	CYls operator+ (int		x) const //重载 + 运算， 有理数+整数
	{
		CYls	t (x);
		return (*this) + t;
	}
	void Display () const;
};

ostream	&  operator << (ostream &os, const CYls &rhs)
{
	if  (rhs.m_fenMu == 1)
		os << rhs.m_fenZi;
	else
		os << rhs.m_fenZi <<"/" << rhs.m_fenMu;
	return os;
}

CYls	operator + (int x, const CYls	&rhs)
{
	CYls	temp;
	temp.m_fenMu =  rhs.m_fenMu;
	temp.m_fenZi = x * rhs.m_fenMu + rhs.m_fenZi;
	temp._Normalize ();
	return temp;
}


CYls::CYls (int fenZi, int fenMu)
: m_fenZi (fenZi), m_fenMu (fenMu)
{
	this->_Normalize ();
}

CYls CYls::operator+ (const CYls &rhs) const
{
	CYls	temp;
	temp.m_fenMu = this->m_fenMu * rhs.m_fenMu;
	temp.m_fenZi =this->m_fenZi * rhs.m_fenMu + this->m_fenMu * rhs.m_fenZi;
	temp._Normalize ();
	return temp;
}

CYls CYls::operator- (const CYls &rhs) const
{
	int		fenZi, fenMu;
	fenMu = this->m_fenMu * rhs.m_fenMu;
	fenZi =this->m_fenZi * rhs.m_fenMu - this->m_fenMu * rhs.m_fenZi;
	CYls   temp(fenZi, fenMu);
	temp._Normalize ();
	return temp;
}

CYls CYls::operator * (const CYls &rhs) const
{
	int		fenZi, fenMu;
	fenMu = this->m_fenMu * rhs.m_fenMu;
	fenZi =this->m_fenZi * rhs.m_fenZi ;
	CYls   temp(fenZi, fenMu);
	temp._Normalize ();
	return temp;
}

CYls CYls::operator /  (const CYls &rhs) const
{
	int		fenZi, fenMu;
	fenZi =this->m_fenZi * rhs.m_fenMu ;
	fenMu = this->m_fenMu * rhs.m_fenZi;
	CYls   temp(fenZi, fenMu);
	temp._Normalize ();
	return temp;
}

void CYls::Display () const
{
	if  (this->m_fenMu == 1)
		cout << this->m_fenZi;
	else
		cout << this->m_fenZi <<"/" << this->m_fenMu;
}

int	GCD (int u, int  v)
{
	while (u % v) {
		int t=  u % v;
		u = v;
		v = t;
	}
	return v;
}

void CYls::_Normalize ()
{
	if  (m_fenZi == 0) {
		m_fenMu  = 1;
		return;
	}
	int		gcd = GCD (abs (m_fenZi), abs (m_fenMu));
	m_fenZi /= gcd;
	m_fenMu /= gcd;
	if (m_fenMu < 0) {
		m_fenMu = - m_fenMu;
		m_fenZi = -m_fenZi;
	}
}

int	main ()
{

	int		x1,x2,y1,y2;

	cin >> x1 >> y1 >> x2 >> y2;

	CYls	A (x1, y1), B (x2, y2);

	CYls	C, D, E, F;
	C = A+B; //A.operator+ (B);
	D = A-B;
	E = A*B;
	F = A / B;

	cout << A << endl;
	cout << B << endl;
	cout << C << '\t' << D << '\t' << E << '\t' << F  << endl;
	return 0;
}

/*
题目描述

设计有理数类，利用运算符重载实现有理数+，-，*，/运算和输出。利用该有理数类，实现两个有理数的运算和结果输出。有理数需化简，有理数分母为1时分母不输出，分母始终大于 0。

输入描述

一对分子分母代表一个有理数，分别输入两个有理数

输出描述

两个有理数（2行）和它们的和、差、积、商（1 行，利用tab键分隔）

输入样例

2  5 3 1

输出样例

2/5
3
17/5   -13/5    6/5   2/15
*/
