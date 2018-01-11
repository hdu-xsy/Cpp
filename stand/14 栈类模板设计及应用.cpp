#include <iostream>
#include <string>
using	namespace std;

template <class T>
class	CStack {
	struct Node {
		T	data;
		Node *next;
	};
private :
	Node	*m_sp;

public :
	CStack	()  :m_sp(NULL)   { //构造函数
	}
	CStack	(const CStack &rhs);//拷贝构造函数
	CStack & operator =	(const CStack &rhs);//赋值运算符重载

	~CStack	();				 //析构函数
	void	push (const T & x);	 //入栈
	bool	empty () const;  //判栈空
	T&		top () const;    //取栈顶元素
	void	pop ();			 //出栈
};

template <class T>
CStack<T>::CStack	(const CStack &rhs) //拷贝构造函数
{
	m_sp = NULL;
	if (rhs.empty ()) //空栈？
		return;

	//复制链表首结点
	m_sp  = new Node;
	Node *q = rhs.m_sp;
	m_sp->data = q->data;

	//复制链表其余结点
	Node	*last = m_sp; //记录新链表最未结点
	q = q->next;
	while (q != NULL) {
		Node *p = new Node;
		p->data = q->data;//复制数据
		last->next = p; //新结点挂在新链表最后
		last = p;		//新结点成最后结点
		q = q->next;	//准备复制下一结点
	}
	last->next = NULL;	//最后结点指针置空
}

template <class T>
CStack<T> & CStack<T>::operator =	(const CStack<T> &rhs)//赋值运算符重载
{
	if (this == &rhs)
		return *this;
	this->~CStack ();  //析构自身

	m_sp = NULL;
	if (rhs.empty ()) //空栈？
		return *this; //返回自身

	//复制链表首结点
	m_sp  = new Node;
	Node *q = rhs.m_sp;
	m_sp->data = q->data;

	//复制链表其余结点
	Node	*last = m_sp; //记录新链表最未结点
	q = q->next;
	while (q != NULL) {
		Node *p = new Node;
		p->data = q->data;//复制数据
		last->next = p; //新结点挂在新链表最后
		last = p;		//新结点成最后结点
		q = q->next;	//准备复制下一结点
	}
	last->next = NULL;	//最后结点指针置空

	return *this;
}

template <class T>
CStack<T>::~CStack	()
{
	while (m_sp != NULL) {
		Node *p = m_sp;
		m_sp = m_sp->next;
		delete p;
	}
}

template <class T>
void	CStack<T>::push (const T& x)
{
	Node *p = new Node;
	p->data = x;
	p->next = m_sp;
	m_sp = p;
}

template <class T>
bool	CStack<T>::empty () const
{
	return (m_sp == NULL);
}

template <class T>
T&		CStack<T>::top () const
{
	return m_sp->data;
}

template <class T>
void	CStack<T>::pop ()
{
	Node *p = m_sp;
	m_sp = p->next;
	delete p;
}

template  <class T>
void    Parse ()
{
	int	n;
	cin >> n;

	CStack<T>	S1, S2;
	int	   v, i;
	T    x;

    for (i = 0; i < n; i++) {
        cin >> v >> x;
		if (v == 1)
			S1.push (x);
		else
			S2.push (x);
	}


	while (!S1.empty ()) {
		x = S1.top ();
		cout << x << " ";
		S1.pop ();
	}
	cout << endl;

	while (!S2.empty ()) {
		x = S2.top ();
		cout << x << " ";
		S2.pop ();
	}
	cout << endl;
}


int	main ()
{
    string  strType;

    while (cin >> strType) {
        if (strType == "int")
            Parse<int> ();
        else if (strType == "string")
            Parse<string> ();
    }
}



/*
栈类模板设计及应用

题目描述

模拟STL stack类模板设计实现你的stack类模板，该类需具有入栈，出栈，判栈空，取栈顶元素等功能，并能拷贝构造和赋值；利用该类实现本题要求。不可使用STL  stack类，可使用STL string类。

输入描述

开始int或string代表需要处理的对象类型。对于每种类型，先构造两个目标类型的空栈，读入整数n,再读入n对整数v、x; 1<=v<=2; 将元素x入第v个栈,n对整数处理完成后， 将两个栈中元素出栈，并输出。

输出描述

每个栈中元素占一行，元素间以空格分隔。

输入样例

int
7
1 100
2 200
1 300
2 400
1 50
1 60
2 80

string
6
1   some
1   one
2   two
2   tom
1   cat
2   hdu

输出样例

60 50 300 100
80 400 200
cat one some
hdu tom two
*/
