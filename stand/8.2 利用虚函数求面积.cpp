#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

const	double	PI = 3.1416;
class	CShape {
public :
	virtual	double	GetArea () const = 0;
};
class	CCircle : public CShape {
	double	m_radius;
public :
	CCircle (double radius);
	virtual	double	GetArea () const;
};

CCircle::CCircle (double radius) : m_radius (radius) {}
double	CCircle::GetArea  () const{
	return PI * m_radius * m_radius;
}

class	CTriangle : public CShape {
	double	m_a, m_b, m_c;
public :
	CTriangle (double a, double b, double c);
	virtual	double	GetArea () const;
};

CTriangle::CTriangle (double a, double b, double c) : m_a (a), m_b(b), m_c (c) {}
double	CTriangle::GetArea () const {
	return sqrt ((m_a+m_b+m_c) * (m_a+m_b-m_c) * (m_a+m_c-m_b) * (m_b+m_c-m_a)) /4.0;
}

class	CRectangle : public CShape {
	double	m_a, m_b;
public :
	CRectangle (double a, double b);
	virtual	double	GetArea () const;
};

CRectangle::CRectangle (double a, double b) : m_a (a), m_b(b) {}
double	CRectangle::GetArea () const {
	return m_a * m_b;
}
int main()
{
	vector<CShape *>	vecShapes;
	string	strShape;

	double	sum = 0;

	while (cin >> strShape) {
		if (strShape == "circle") {
			double	radius;
			cin >> radius;
			vecShapes.push_back (new CCircle (radius));
		} else if (strShape == "triangle") {
			double	a,b,c;
			cin >> a>>b>> c;
			vecShapes.push_back (new CTriangle (a,b,c));
		} else if (strShape == "rectangle") {
			double	a,b;
			cin >> a>>b;
			vecShapes.push_back (new CRectangle (a,b));
		} else {
		}
	}
	for (int i = 0; i < vecShapes.size (); i++) {
		sum += vecShapes[i]->GetArea ();
		delete vecShapes[i];
	}

	cout << fixed << setprecision (4) << sum << endl;

	return 0;
}

/*
题目描述

定义抽象基类Shape，由它派生出3个派生类：Circle（圆形）、Rectangle（ 长方形）、
和Triangle （三角形），用虚函数分别计算面积。编写求面积和函数double TotalArea
(Shape  * A [], int  n)，该函数利用基类指针数组，它的每一个元素指向一个派生类
的图形对象。编写测试解释器，读入各种图形信息，生成各种图形对象，由指针数组管理,
图形个数不超过100个。利用求面积虚函数，输出面积总和，要求正确释放空间。PI取3.1416

输入描述

circle 后跟半径
rectangle后跟长和宽
triangle后跟三条边

输出描述

结果保留小数点后4位

输入样例

circle  5.2 circle  6.0
rectangle  3.4 2
triangle  3 4 5
rectangle  4.4 10

输出样例

254.8465

*/
