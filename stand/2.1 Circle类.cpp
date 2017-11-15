#include  <iostream>
using namespace std;
const double Pi=3.1415926;
class Circle
{
public:
	void setRadius(double r);	//���ð뾶
	double area();				//��Բ�����
	double circumference();		//��Բ���ܳ�
private:
	double radius;
};
void Circle::setRadius(double r)	//���ð뾶
{
	radius=r;
}
double Circle::area()				//��Բ�����
{
	return Pi * radius * radius;
}
double Circle::circumference()		//��Բ���ܳ�
{
	return 2*Pi*radius;
}
int main()
{
	double r;
//	cout<<"�����뺵�����İ뾶: ";
	cin>>r;
	Circle c;
	c.setRadius(r);
	printf ("%.2lf\n", 20*c.area()+35*c.circumference());
	return 0;
}

/*
��Ŀ����
��Circle�ࣩһ��Բ�εĺ������أ�������Ĩˮ�࣬���Ϊÿƽ����20Ԫ��Χ����ľ��Χ�ɣ�ÿ�����35Ԫ�����һ��Circle�࣬�������Բ������ͱ߳�������֧������������ĵȼۡ�����������ʾ�Ļ�������ɳ���������Ҫ���Ĺ�����������1������������������صĹ�����Ա��������2������������main()����֮�䣬���������ĳ�Ա������PI����3.1415926

��������

�����뺵�����İ뾶

�������

�����������,С�������2λ

��������

5.5

�������

3110.18
*/
