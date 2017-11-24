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
��Ŀ����

����������Shape������������3�������ࣺCircle��Բ�Σ���Rectangle�� �����Σ���
��Triangle �������Σ������麯���ֱ�����������д������ͺ���double TotalArea
(Shape  * A [], int  n)���ú������û���ָ�����飬����ÿһ��Ԫ��ָ��һ��������
��ͼ�ζ��󡣱�д���Խ��������������ͼ����Ϣ�����ɸ���ͼ�ζ�����ָ���������,
ͼ�θ���������100��������������麯�����������ܺͣ�Ҫ����ȷ�ͷſռ䡣PIȡ3.1416

��������

circle ����뾶
rectangle������Ϳ�
triangle���������

�������

�������С�����4λ

��������

circle  5.2 circle  6.0
rectangle  3.4 2
triangle  3 4 5
rectangle  4.4 10

�������

254.8465

*/
