#include <iostream>
using namespace std;
#define MAX_SIZE 100

class Set
{
private:
	int *elem;
	int n;
public:
	Set();
	Set(const Set& s);
	~Set();
	void Add(int a[], int len);
	bool Contains(int e);
	Set Intersect(const Set& s);
	Set Union(const Set& s);
	Set Diffirence(const Set s);
	void Show();
	void Rank();
};
void main()
{
	int n1, n2;
	int a1[100], a2[100];
	Set s1 = Set();
	Set s2 = Set();
	scanf("%d%d", &n1, &n2);
	for (int i = 0; i<n1; i++)
	{
		scanf("%d", &a1[i]);
	}
	for (int i = 0; i<n2; i++)
	{
		scanf("%d", &a2[i]);
	}
	s1.Add(a1, n1);
	s2.Add(a2, n2);
	s1.Rank();
	s2.Rank();
	s1.Show();
	s2.Show();
	Set s3(s1.Union(s2));
	s3.Show();
	Set s4(s1.Intersect(s2));
	s4.Show();
	Set s5(s1.Diffirence(s2));
	s5.Show();
}

Set::Set() :n(0)	//构造函数
{
	elem = new int[MAX_SIZE];
}

bool Set::Contains(int e)	//判断元素是否重复
{
	for (int i = 0; i < n; i++)
		if (elem[i] == e) return true;
	return false;
}


Set::Set(const Set& s)	//拷贝构造函数
{
	n = s.n;
	elem = new int[MAX_SIZE];
	for (int i = 0; i<s.n; i++)
	{
		elem[i] = s.elem[i];
	}
}

Set::~Set()	//析构函数
{
	delete[] elem;
}


void Set::Add(int a[], int len)		//添加元素
{
	for (int i = 0; i < len; i++)
	{
		if (!Contains(a[i]))
			elem[n++] = a[i];
	}
}


void Set::Rank()	//增序排序
{
	int temp = 0;
	for (int i = 0; i<n - 1; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (elem[i]>elem[j])
			{
				temp = elem[i];
				elem[i] = elem[j];
				elem[j] = temp;
			}
		}
	}
}

Set Set::Union(const Set& s)	//并
{
	Set un = Set();
	un.Add(s.elem, s.n);
	un.Add(elem, n);
	un.Rank();
	return un;
}
Set Set::Intersect(const Set& s)	//交
{
	Set in = Set();
	for (int i = 0; i < s.n; i++)
	{
		if (Contains(s.elem[i]))
			in.Add(s.elem + i, 1);
	}
	in.Rank();
	return in;
}
Set Set::Diffirence(const Set s)		//差
{
	Set di = Set();
	di.Add(elem, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j<s.n; j++)
		{
			if (di.elem[i] == s.elem[j])
			{
				for (int k = i; k < di.n - 1; k++) {
					di.elem[k] = di.elem[k + 1];
				}
				di.n--;
			}
		}
	}
	di.Rank();
	return di;
}
void Set::Show()
{
	if (n <= 0 )
	{
		cout << "{}" << endl;
	}
	else {
		cout << "{";
		for (int i = 0; i < n - 1; i++) {
			cout << elem[i] << ",";
		}
		cout << elem[n - 1] << "}" << endl;
	}
}

/*
题目描述

请设计实现集合类，元素类型为整形。该集合类支持集合元素增加、删除、查询；并支持集合并、交、差运算（作为类成员函数），；利用你设计的集合类，实现本题要求。程序应体现面向对象程序设计思想，结构合理。为保证结果唯一，集合元素递增排列。假设集合元素个数不超100个。要求并、交、差运算结果先保存在集合对象内（如需要可继续参加集合运算），再利用集合显示功能显示。集合元素保存在数组中。

输入描述

开始为两个正整数m,n；后续m个整数构成集合A,再后续n个整数构成集合B

输出描述

集合A、B和他们的并、交、差集；每个集合元素间以,分隔；不同集合显示在不同行

输入样例

3 5
1 2 3
3 5 8 2 1

输出样例

{1,2,3}
{1,2,3,5,8}
{1,2,3,5,8}
{1,2,3}
{}
*/
