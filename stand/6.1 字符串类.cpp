#include <iostream>
#include <cstring>
using	namespace	std;

//下述3行是VC6.0特殊要求
class	CString;
CString operator+ (const CString &S1, const CString &S2);
ostream & operator << (ostream &out, const CString &rhs);

class	CString {
public :
	CString (); //无参构造，构造空串
	CString (const char *str); //传统字符串构造
	CString (const CString &rhs); //拷贝构造
//	CString (CString &&rhs)  //移动构造
//	{
//	    m_pBuffer = rhs.m_pBuffer; rhs.m_pBuffer = NULL;
//	    m_length = rhs.m_length;
//	}
	CString   substr (int start, int len); //取子串
	friend	CString operator + (const CString &S1, const CString &S2); //字符串连接
	CString & operator = (const CString &rhs); //复制赋值运算符重载
//	CString & operator = (CString &&rhs) //移动赋值运算符重载
//	{
//	    char	*t = m_pBuffer;
//	    m_pBuffer = rhs.m_pBuffer; rhs.m_pBuffer = t;
//	    m_length = rhs.m_length;
//	    return *this;
//	}
	friend ostream & operator << (ostream &out, const CString &rhs);  //插入运算符重载
	~CString () //析构函数，释放字符串占用的资源
	{
		delete [] m_pBuffer;
	}
	char& operator [] (int index);  //下标运算符，可用于左值
	const char& operator [] (int index) const; //下标运算符，只能可用于右值
	operator const char * () const; //转换运算符
private :
	explicit CString (int length)  //构造函数，便于＋、取子串等运算
	{
		m_pBuffer = new char [length +1];
		m_length = length;
	}
	char	*m_pBuffer;  //存放字符串内容
	int		m_length;    //字符串长度，便于＋运算；也可不设置
};

//无参构造，构造空串
CString::CString ()
{
	m_length = 0;
	m_pBuffer = new char [1];
	m_pBuffer [0] = '\0';
}

//传统字符串构造
CString::CString (const char *str)
{
	m_length = strlen (str);
	m_pBuffer = new char [m_length +1];
	strcpy (m_pBuffer, str);
}

//拷贝构造
CString::CString (const CString &rhs)
{
	m_length = rhs.m_length ;
	m_pBuffer = new char [m_length +1];
	strcpy (m_pBuffer, rhs.m_pBuffer);
}

//取子串
CString   CString::substr (int start, int len)
{
	CString	tempStr (len);
	strncpy (tempStr.m_pBuffer, m_pBuffer+start, len);
	tempStr.m_pBuffer [len] = '\0';
	return tempStr;
}

//字符串连接
CString operator + (const CString &S1, const CString &S2)
{
	CString	tempStr (S1.m_length + S2.m_length);
	strcpy (tempStr.m_pBuffer, S1.m_pBuffer);
	strcat (tempStr.m_pBuffer, S2.m_pBuffer );
	return tempStr;
}

//赋值运算符重载
CString & CString::operator = (const CString &rhs)
{
	if (this == &rhs) //特殊处理
		return *this;
	delete [] m_pBuffer; //释放原空间

	m_length = rhs.m_length ;
	m_pBuffer = new char [m_length +1];
	strcpy (m_pBuffer, rhs.m_pBuffer);
	return *this;  //返回当前对象引用，便于连续赋值
}

//插入运算符重载
ostream & operator << (ostream &out, const CString &rhs)
{
	out << rhs.m_pBuffer;
	return out;
}

//下标运算符，只能可用于右值
const char& CString::operator [] (int index) const
{
	if (index < 0 || index > m_length) {
		static	char	c;
		return c;
	}
	return m_pBuffer [index];
}

//下标运算符，可用于左值
char& CString::operator [] (int index)
{
	if (index < 0 || index > m_length) {
		static	char	c;
		return c;
	}
	return m_pBuffer [index];
}

//转换运算符
CString::operator const char * () const
{
	return	m_pBuffer;
}

//测试用例，命令解释器
int main()
{
	char	bufs1 [256], bufs2 [256];

	cin >> bufs1 >> bufs2;
	CString	s [4] = {CString (bufs1), CString (bufs2)};

	char  op;
	int	i,j,k,l,pos;

	while (cin>> op) {
		switch (op) {
		case 'P':
			cin >> i;
			cout << s [i-1] << endl;
			break;
		case 'A':
			cin >> i >> j;
			s [j-1] = s[i-1];
			break;
		case 'C':
			cin >> i >> j >> k;
			s [k-1] = s [i-1] + s[j-1];
			break;
		case 'F':
			cin >> i >> pos >> l >> k ;
			s [k-1] = s [i-1].substr (pos, l);
			break;
		}
	}
	return 0;
}


/*
字符串类

题目描述

模拟标准库字符串类实现你自己的字符串类。该类需具有构造，字符串连接、取子串和复制、赋值、输出等功能。要求使用动态分配存储字符串内容。不可使用STL string类

输入描述

测试程序有4个字符串，每个样例前两行含长度不超过200的俩字符串，赋值给前2个字符串对象，后面若干指令，每个指令占一行，分别由指令码和所需参数组成，空格分隔，每个指令码具有不同参数和意义; 指令有下述几种 ： 指令P  i代表输出字符串i; 指令A  i j代表字符串i赋值给字符串j;  指令C i j  k 代表将字符串i和字符串j连接后赋值给字符串k; 指令F i s l k代表从字符串i位置s开始的长度为l的子串赋值给字符串k;所有操作指令和参数肯定是有校的。

输出描述

每个字符串输出占1行

输入样例

Hello
HDU
P 1
P 2
C 1 2 3
P 3
F 3 5 3 4
P 4

输出样例

Hello
HDU
HelloHDU
HDU

*/
