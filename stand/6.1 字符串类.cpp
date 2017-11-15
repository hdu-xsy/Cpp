#include <iostream>
#include <cstring>
using	namespace	std;

//����3����VC6.0����Ҫ��
class	CString;
CString operator+ (const CString &S1, const CString &S2);
ostream & operator << (ostream &out, const CString &rhs);

class	CString {
public :
	CString (); //�޲ι��죬����մ�
	CString (const char *str); //��ͳ�ַ�������
	CString (const CString &rhs); //��������
//	CString (CString &&rhs)  //�ƶ�����
//	{
//	    m_pBuffer = rhs.m_pBuffer; rhs.m_pBuffer = NULL;
//	    m_length = rhs.m_length;
//	}
	CString   substr (int start, int len); //ȡ�Ӵ�
	friend	CString operator + (const CString &S1, const CString &S2); //�ַ�������
	CString & operator = (const CString &rhs); //���Ƹ�ֵ���������
//	CString & operator = (CString &&rhs) //�ƶ���ֵ���������
//	{
//	    char	*t = m_pBuffer;
//	    m_pBuffer = rhs.m_pBuffer; rhs.m_pBuffer = t;
//	    m_length = rhs.m_length;
//	    return *this;
//	}
	friend ostream & operator << (ostream &out, const CString &rhs);  //�������������
	~CString () //�����������ͷ��ַ���ռ�õ���Դ
	{
		delete [] m_pBuffer;
	}
	char& operator [] (int index);  //�±����������������ֵ
	const char& operator [] (int index) const; //�±��������ֻ�ܿ�������ֵ
	operator const char * () const; //ת�������
private :
	explicit CString (int length)  //���캯�������ڣ���ȡ�Ӵ�������
	{
		m_pBuffer = new char [length +1];
		m_length = length;
	}
	char	*m_pBuffer;  //����ַ�������
	int		m_length;    //�ַ������ȣ����ڣ����㣻Ҳ�ɲ�����
};

//�޲ι��죬����մ�
CString::CString ()
{
	m_length = 0;
	m_pBuffer = new char [1];
	m_pBuffer [0] = '\0';
}

//��ͳ�ַ�������
CString::CString (const char *str)
{
	m_length = strlen (str);
	m_pBuffer = new char [m_length +1];
	strcpy (m_pBuffer, str);
}

//��������
CString::CString (const CString &rhs)
{
	m_length = rhs.m_length ;
	m_pBuffer = new char [m_length +1];
	strcpy (m_pBuffer, rhs.m_pBuffer);
}

//ȡ�Ӵ�
CString   CString::substr (int start, int len)
{
	CString	tempStr (len);
	strncpy (tempStr.m_pBuffer, m_pBuffer+start, len);
	tempStr.m_pBuffer [len] = '\0';
	return tempStr;
}

//�ַ�������
CString operator + (const CString &S1, const CString &S2)
{
	CString	tempStr (S1.m_length + S2.m_length);
	strcpy (tempStr.m_pBuffer, S1.m_pBuffer);
	strcat (tempStr.m_pBuffer, S2.m_pBuffer );
	return tempStr;
}

//��ֵ���������
CString & CString::operator = (const CString &rhs)
{
	if (this == &rhs) //���⴦��
		return *this;
	delete [] m_pBuffer; //�ͷ�ԭ�ռ�

	m_length = rhs.m_length ;
	m_pBuffer = new char [m_length +1];
	strcpy (m_pBuffer, rhs.m_pBuffer);
	return *this;  //���ص�ǰ�������ã�����������ֵ
}

//�������������
ostream & operator << (ostream &out, const CString &rhs)
{
	out << rhs.m_pBuffer;
	return out;
}

//�±��������ֻ�ܿ�������ֵ
const char& CString::operator [] (int index) const
{
	if (index < 0 || index > m_length) {
		static	char	c;
		return c;
	}
	return m_pBuffer [index];
}

//�±����������������ֵ
char& CString::operator [] (int index)
{
	if (index < 0 || index > m_length) {
		static	char	c;
		return c;
	}
	return m_pBuffer [index];
}

//ת�������
CString::operator const char * () const
{
	return	m_pBuffer;
}

//�������������������
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
�ַ�����

��Ŀ����

ģ���׼���ַ�����ʵ�����Լ����ַ����ࡣ��������й��죬�ַ������ӡ�ȡ�Ӵ��͸��ơ���ֵ������ȹ��ܡ�Ҫ��ʹ�ö�̬����洢�ַ������ݡ�����ʹ��STL string��

��������

���Գ�����4���ַ�����ÿ������ǰ���к����Ȳ�����200�����ַ�������ֵ��ǰ2���ַ������󣬺�������ָ�ÿ��ָ��ռһ�У��ֱ���ָ��������������ɣ��ո�ָ���ÿ��ָ������в�ͬ����������; ָ������������ �� ָ��P  i��������ַ���i; ָ��A  i j�����ַ���i��ֵ���ַ���j;  ָ��C i j  k �����ַ���i���ַ���j���Ӻ�ֵ���ַ���k; ָ��F i s l k������ַ���iλ��s��ʼ�ĳ���Ϊl���Ӵ���ֵ���ַ���k;���в���ָ��Ͳ����϶�����У�ġ�

�������

ÿ���ַ������ռ1��

��������

Hello
HDU
P 1
P 2
C 1 2 3
P 3
F 3 5 3 4
P 4

�������

Hello
HDU
HelloHDU
HDU

*/
