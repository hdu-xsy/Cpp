#include <iostream>
using namespace std;

class CSet{
private:
	enum	{MaxSIZE = 100};
	int	m_datas [MaxSIZE]; //集合元素在递增排序表示
	int m_count; // 此元素个数
public:
	//构造函数
	CSet();
	//增加元素
	bool Add(int x);
	//显示集合
	void Display() const;
	//并集
	CSet UnionWith (const CSet &rhs) const;
	//交集
	CSet IntersectionWith (const CSet &rhs) const;
	//差集
	CSet DifferentWith (const CSet &rhs) const;
	//是否包含元素x
	bool In (int x) const;
	//删除元素x
	bool Remove(int x);
	//集合清空
	void Clear ();
};


//构造函数
CSet::CSet()
{
	m_count = 0;
}

//集合清空
void	CSet::Clear ()
{
	m_count = 0;
}

//增加元素
bool CSet::Add(int x)
{
	if (In (x))
		return false; //元素已在集合中
	if (m_count >= MaxSIZE)
		throw "OverFlow";  //集合已满, 抛出异常待处理
	int	i = m_count-1;
	while (i >= 0 && x < m_datas [i]) {
		m_datas [i+1] = m_datas [i];
		i --;  //从后往前,元素后移
	}
	m_datas [i+1] = x; //填入元素
	m_count ++;        //调整元素个数
	return true;
}

//显示集合
void CSet::Display() const
{
	cout << "{";
	int		i;
	for (i = 0; i < m_count-1; i++) {
		cout << m_datas [i] << ",";
	}
	if (i < m_count)
		cout << m_datas [i];
	cout << "}" << endl;
}

//结果为A、B并集，效率为O（M+N)
//并集
CSet CSet::UnionWith (const CSet &rhs) const
{
	CSet	result;
	int	i,j;
	i=j=0;
	while (i < m_count && j < rhs.m_count) {
		if  (result.m_count >= MaxSIZE)
			throw "OverFlow";  //集合已满, 抛出异常待处理
		//元素小先处理
		if (m_datas [i] < rhs.m_datas [j]) {
			result.m_datas [result.m_count++] = m_datas [i];
			i++;
		} else if  (m_datas [i] == rhs.m_datas [j]) {
			result.m_datas [result.m_count++] = m_datas [i];
			i++;
			j++;
		} else {
			result.m_datas [result.m_count++] = rhs.m_datas [j];
			j++;
		}
	}
	while (i < m_count ) {//抄送其余元素
		if  (result.m_count >= MaxSIZE)
			throw "OverFlow";  //集合已满, 抛出异常待处理
		result.m_datas [result.m_count++] = m_datas [i];
		i++;
	}
	while ( j < rhs.m_count) {//抄送rhs其余元素
		if  (result.m_count >= MaxSIZE)
			throw "OverFlow";  //集合已满, 抛出异常待处理
		result.m_datas [result.m_count++] = rhs.m_datas [j];
		j++;
	}
	return result;
}

//交集
//本例为简化逻辑直接调用成员函数，效率为O（M*N）；实际应参考UnionWithh展开，效率可为O（M+N）
CSet CSet::IntersectionWith (const CSet &rhs) const
{
	CSet	result;

    for (int i = 0; i < m_count; i++) {
		if (rhs.In (m_datas [i]))
			result.Add (m_datas [i]);
	}
	return result;
}

//本例为简化逻辑直接调用成员函数，效率为O（M*N）；实际应参考UnionWith展开，效率可为O（M+N）
//差集
CSet CSet::DifferentWith (const CSet &rhs) const
{
	CSet	result;

    for (int i = 0; i < m_count; i++) {
		if (!rhs.In (m_datas [i]))
			result.Add (m_datas [i]);
	}
	return result;
}

//删除元素
bool CSet::Remove(int x)
{
	int	i = 0;
	while (i < m_count && x < m_datas [i])
		i++;
	if (i >= m_count || x != m_datas [i]) {
		return false;//元素未在集合中
	}
	while (i+1 < m_count) {
		m_datas [i] = m_datas [i+1];
		i++; //后续元素前移
	}
	m_count --; //调整元素个数
	return true;
}

//是否包含元素x
bool CSet::In(int x) const
{
	int	i = 0;
	while (i < m_count && x > m_datas [i])
		i++;
	if (i < m_count && x == m_datas [i])
		return true;
	return false;
}


int main()
{
	CSet A,B,S;
	int i,m,n,x;

	cin >> m >> n;
	//建立A 集
	for(i = 0; i < m; i++)
	{
		cin >> x;
		A.Add(x);
	}

	//建立B 集
	for(i = 0; i < n ; i++)
	{
		cin >> x;
		B.Add(x);
	}

	A.Display();
	B.Display();


	S = A.UnionWith (B);
	S.Display();

	S = A.IntersectionWith (B);
	S.Display();

	S = A.DifferentWith (B);
	S.Display();

	return 0;
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
