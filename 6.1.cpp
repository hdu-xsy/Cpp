#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define CHUNKSIZE 3
class CString {
private:
		char *ch;
		int length;
public:
	CString();					//构造
	CString(char *chars);
	~CString();					//析构
	void StrPrint();			//输出
	CString(const CString &rhs);	//拷贝构造
	CString concat(const CString &rhs) const;		//连接
	bool strEmpty();		//判断是否为空
	CString & operator = (CString &rhs);	//复制赋值
	CString SubString(int i,int j);	//截取字符串
};

CString::CString()
{	
	ch = NULL;
	length = 0;
}

CString::CString(char *chars)
{
	int i, j;
	i = strlen(chars);
	ch = (char*)malloc(i * sizeof(char));
	if (!ch)	exit(-3);
	for (j = 0; j < i; j++)
	ch[j] = chars[j];
	length = i;
}

CString::~CString()
{
	delete[] ch;
}

void CString::StrPrint()
{
	int i;
		for (i = 0; i < length; i++)
		{
			cout << ch[i];
		}
	cout << endl;
}

bool CString::strEmpty()
{
	if (length == 0 && ch == NULL)
		return false;
	else
		return true;
}

CString CString::concat(const CString &rhs) const
{
	CString sp;
	sp.length = length + rhs.length;
	sp.ch = (char*)malloc(sp.length * sizeof(char));
	for (int i = 0; i < length; i++)
		sp.ch[i] = ch[i];
	for (int i = 0; i < rhs.length; i++)
		sp.ch[length + i] = rhs.ch[i];
	return sp;
}


CString::CString(const CString &rhs)
{
		if (strEmpty())
		{
			ch = (char*)malloc(rhs.length * sizeof(char));
			if (!ch) exit(-3);
			for (int i = 0; i < rhs.length; i++)
			{
				ch[i] = rhs.ch[i];
			}
			length = rhs.length;
		}
}

CString & CString::operator=(CString &rhs)
{
	if (this != &rhs)
	{
		if (rhs.strEmpty())
		{
			ch = (char*)malloc(rhs.length * sizeof(char));
			if (!ch) exit(-3);
			for (int i = 0; i < rhs.length; i++)
			{
				ch[i] = rhs.ch[i];
			}
			length = rhs.length;
		}
	}
	return *this;
}

CString CString::SubString(int i,int j)
{
	CString sp;
	sp.length = j;
	sp.ch = (char*)malloc(sp.length * sizeof(char));
	for (int k=i; k < i + j; k++)
	{
		sp.ch[k - i] = ch[k];
	}
	return sp;
}
void main()
{
	char c;
	char c1[201];
	char c2[201];
	cin >> c1 >> c2;
	CString s[4];
	s[0] = CString(c1);
	s[1] = CString(c2);
	while (cin >> c)
	{
		if (c == 'P')
		{
			int n1;
			cin >> n1;
			s[n1 - 1].StrPrint();
		}
		else if (c == 'C')
		{
			int n1, n2, n3;
			cin >> n1 >> n2 >> n3;
			s[n3 - 1] = s[n1 - 1].concat(s[n2 - 1]);
		}
		else if (c == 'F')
		{
			int n1, n2, n3, n4;
			cin >> n1 >> n2 >> n3 >> n4;
			s[n4 - 1] = s[n1 - 1].SubString(n2, n3);
		}
	}
}