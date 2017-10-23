#include<cstdio>
using namespace std;
#define pi 3.1415926

class Circle
{
	public:;
		Circle(float n);
		void Cal();
		void Show();
	private:
		float r,l,s,m;
	protected:
};

Circle::Circle(float n):r(n),l(0.00),s(0.00),m(0.00)
{

}
void Circle::Cal()
{
		s=pi*r*r;
		l=2*pi*r;
		m=20*s+35*l;
}
void Circle::Show()
{
	printf("%.2f",m);
}
void main()
{
	float n;
	while(cin>>n)
	{
		Circle C(n);
		C.Cal();
		C.Show();
	}
}



/*
题目描述

（Circle类）一个圆形的旱冰场地，场地内抹水泥，造价为每平方米20元，围栏用木条围成，每米造价35元。设计一个Circle类，可以求出圆的面积和边长，进而支持求出旱冰场的等价。请在下面提示的基础上完成程序，其中需要做的工作包括：（1）在类声明中声明相关的公共成员函数；（2）在类声明和main()函数之间，定义声明的成员函数。PI采用3.1415926

输入描述

请输入旱冰场的半径

输出描述

旱冰场的造价,小数点后保留2位

输入样例

5.5

输出样例

3110.18
*/
