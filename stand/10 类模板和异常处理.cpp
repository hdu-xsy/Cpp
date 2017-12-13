#include <iostream>
#include <string>
#include <sstream>
using	namespace	std;

class	CException {
	string	m_errMsg;
public :
	CException (string	errMsg, int i) : m_errMsg (errMsg) {
		stringstream	stream;
		stream << i;
		string	str;
		stream >> str;
		m_errMsg += str;
	}
	string	GetErrorMsg () {
		return m_errMsg;
	}
};
template <class	T>
class	CMyVector {
private :
	T	*m_pBuffer;
	int	m_size,m_bufferSize;
public:

	CMyVector () : m_size (0), m_bufferSize (0),m_pBuffer (NULL) {}
	CMyVector (int n) : m_size (n), m_bufferSize (n) {
		if  (m_bufferSize > 0)
			m_pBuffer = new T [m_bufferSize];
		else
			m_pBuffer = NULL;
	}

	~CMyVector () {
		delete [] m_pBuffer;
	}

	void	push_back (const T &rhs);

	T  & operator [] (int i) {
		if (i < 0 || i >= m_size) {
			string	errMsg ("invalid index:");

			throw	CException (errMsg, i);
		}
		return m_pBuffer [i];
	}
	int	size () const {
		return m_size;
	}
};

template <class T>
void	CMyVector<T>::push_back (const T &rhs)
{
	if  (m_bufferSize <= m_size) {
		T	*p = new T [m_bufferSize  + 10];
		for (int i= 0; i < m_size; i++)
			p [i] = m_pBuffer [i];

		delete [] m_pBuffer;
		m_pBuffer = p;
		m_bufferSize += 10;
	}
	m_pBuffer [m_size++] = rhs;
}

template	<class T>
void Parse (int size)
{
	CMyVector<T>	V (size);
	string	cmd;
	T		x;
	int		index;
	while (cin >> cmd) {
		try {
			if (cmd == "quit")
				break;
			else if (cmd == "push") {
				cin >> x;
				V.push_back (x);
			} else if (cmd == "fetch") {
				cin >> index;
				x = V [index];
				cout << ' '<< x;

			} else if (cmd == "put") {
				cin >> index >> x;
				V [index] = x;
			}
		} catch (CException ex) {
			cout << ' ' << ex.GetErrorMsg ();
		}
	}
	cout << endl;
}

int	main ()
{
	string	typeStr;
	while (cin >> typeStr) {
		int	size;
		cin >> size;
		if (typeStr == "int")
			Parse<int> (size);
		else
			Parse<string> (size);
	}
}


/*
��ģ����쳣����

��Ŀ����

�ο�C++ vector��ģ�壬���ʵ���Լ���CVector������ģ�壬������л������ܣ� ���졢������
size��push_back���±���ʣ���ͨ���±����Խ��ʱ�׳��쳣����д���Գ������ø���ģ����
��һ�������������������ִ����Ӧ������

��������

����������5�� ��int ����  ����ʼ������������ (����Ϊ������ʼ��С)��string ����
����ʼ����string������push���� ����������β׷�Ӷ��� put  �±�  ����  �����轫����
���������±괦��fetch  �±�   ����ȡ����ӡ�����±괦���󣻵��±�Խ��ʱ�׳��쳣����ʾin
valid index:�±ꣻquit�������д��������ÿ��������int��string��ʼ����quit����������
�����Сд��

�������

ÿ�������ӽ������������ռһ�У�
���������ǰ��һ���ո�

��������

int 10  push 100 push 200 push 50 push 300 put 0 5  put 1 20  push 400 fetch 1
fetch 12 fetch -1 fetch 20 fetch 11 quit
string 10 push hello push some push apple push box put 1 zhang   push hdu fetch
1 fetch 20 fetch 12 quit

�������

20 50 invalid index:-1 invalid index:20 200
  zhang invalid index:20 apple
*/
