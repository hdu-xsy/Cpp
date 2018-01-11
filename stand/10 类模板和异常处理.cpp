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
类模板和异常处理

题目描述

参考C++ vector类模板，设计实现自己的CVector向量类模板，完成下列基本功能： 构造、析构、
size、push_back和下标访问，在通过下标访问越界时抛出异常。编写测试程序，利用该类模板完
成一个解释器，它接受命令，执行相应操作。

输入描述

输入命令有5种 ：int 整数  代表开始建立整数向量 (整数为向量初始大小)；string 整数
代表开始建立string向量；push对象 代表在向量尾追加对象； put  下标  对象  代表需将对象
放入向量下标处；fetch  下标   代表取并打印向量下标处对象；当下标越界时抛出异常并显示in
valid index:下标；quit代表本队列处理结束。每个队列以int或string开始，以quit结束；所有
命令均小写。

输出描述

每个向量从建立到结束输出占一行；
各输出对象前含一个空格。

输入样例

int 10  push 100 push 200 push 50 push 300 put 0 5  put 1 20  push 400 fetch 1
fetch 12 fetch -1 fetch 20 fetch 11 quit
string 10 push hello push some push apple push box put 1 zhang   push hdu fetch
1 fetch 20 fetch 12 quit

输出样例

20 50 invalid index:-1 invalid index:20 200
  zhang invalid index:20 apple
*/
