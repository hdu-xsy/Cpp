#include <iostream>
using	namespace std;

class	CStack {
	struct Node {
		int	data;
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
	void	push (int x);	 //入栈
	bool	empty () const;  //判栈空
	int		top () const;    //取栈顶元素
	void	pop ();			 //出栈
};

CStack::CStack	(const CStack &rhs) //拷贝构造函数
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

CStack & CStack::operator =	(const CStack &rhs)//赋值运算符重载
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
CStack::~CStack	()
{
	while (m_sp != NULL) {
		Node *p = m_sp;
		m_sp = m_sp->next;
		delete p;
	}
}

void	CStack::push (int x)
{
	Node *p = new Node;
	p->data = x;
	p->next = m_sp;
	m_sp = p;
}

bool	CStack::empty () const
{
	return (m_sp == NULL);
}
int		CStack::top () const
{
	return m_sp->data;
}

void	CStack::pop ()
{
	Node *p = m_sp;
	m_sp = p->next;
	delete p;
}

int main()
{
	CStack	S1, S2;
	int	v, x;

	while (cin >> v >> x) {
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

	return 0;
}

/*
题目描述

模拟STL  stack类设计实现你的stack类，该类需具有入栈，出栈，判栈空，取栈顶元素等功能；利用该类实现本题要求。本题要求使用单链表实现。不可使用STL  stack类

输入描述

分别构造两个空栈，再读入若干对整数v、x; 1<=v<=2; 将元素x入第v个栈 。

输出描述

最后将两个栈中元素出栈，并输出；每个栈中元素占一行，元素间以空格分隔。

输入样例

1 100
2 200
1 300
2 400
1 50
1 60
2 80

输出样例

60 50 300 100
80 400 200

题目描述

模拟STL  stack类设计实现你的stack类，该类需具有入栈，出栈，判栈空，取栈顶元素等功能；利用该类实现本题要求。本题要求使用单链表实现。不可使用STL  stack类

输入描述

分别构造两个空栈，再读入若干对整数v、x; 1<=v<=2; 将元素x入第v个栈 。
*/



输出描述

最后将两个栈中元素出栈，并输出；每个栈中元素占一行，元素间以空格分隔。




输入样例

1 100
2 200
1 300
2 400
1 50
1 60
2 80




输出样例

60 50 300 100
80 400 200
