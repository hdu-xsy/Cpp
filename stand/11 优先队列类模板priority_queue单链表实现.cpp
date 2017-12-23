#include <iostream>
#include <string>
using	namespace	std;

template  <class T>
class	priority_queue {
	struct	Node {
		T	data;
		Node *next;
	};
private :
	Node  *m_pHead; //队首
	int	m_length;
public :
	priority_queue ();     //构造函数
	priority_queue (const	priority_queue &rhs); //拷贝构造
/*平台不支持C++11
	priority_queue (priority_queue &&rhs) { //移动构造
	    m_pHead = rhs.m_pHead;
	    m_length = rhs.m_length;
	    rhs.m_pHead = NULL;
	}
*/
	priority_queue& operator =  (const	priority_queue &rhs); //拷贝赋值
/*平台不支持C++11
	priority_queue& operator =  (priority_queue &&rhs) { // 移动赋值
	    Node *t = m_pHead;
	    m_pHead = rhs.m_pHead;
	    m_length = rhs.m_length;
	    rhs.m_pHead = t;
	}
*/
	~priority_queue (); //析构
	bool	push (T x);  //入队列
	void	pop ();		//出队列
	T		front ();	//队首元素
	bool	empty () const;  //判队空
	int		length () const;  //队列长度
};

template  <class T>
priority_queue<T>& priority_queue<T>::operator =  (const	priority_queue<T> &rhs) //拷贝赋值
{
    this->~priority_queue();
    m_length = rhs.m_length;
	m_pHead = new Node;
	Node *last = m_pHead;
	Node *p= rhs.m_pHead->next;
	while (p) {
		Node *q = new Node;
		q->data = p->data;
		last->next = q;
		last = q;
		p = p->next;
	}
	last->next = NULL;
    return  *this;
}

template  <class T>
priority_queue<T>::priority_queue () : m_length (0)
{
	m_pHead = new Node;
	m_pHead->next = NULL;

}

//拷贝构造
template  <class T>
priority_queue<T>::priority_queue (const	priority_queue &rhs) : m_length (rhs.m_length)
{
	m_pHead = new Node;
	Node *last = m_pHead;
	Node *p= rhs.m_pHead->next;
	while (p) {
		Node *q = new Node;
		q->data = p->data;
		last->next = q;
		last = q;
		p = p->next;
	}
	last->next = NULL;
}

template  <class T>
priority_queue<T>::~priority_queue ()
{
	while (m_pHead) {
		Node *q = m_pHead->next;
		delete m_pHead;
		m_pHead = q;
	}
}

//入队列
template  <class T>
bool	priority_queue<T>::push (T x)
{
	Node *q= new Node;
	q->data = x;
	Node *p = m_pHead;
	while (p->next && x > p->next ->data)
		p = p->next;
	q->next = p ->next ;
	p->next = q;
	m_length ++;
	return true;
}

//队列非空
template  <class T>
void	priority_queue<T>::pop ()
{
	Node *q = m_pHead->next;
	delete m_pHead;
	m_pHead = q;
	m_length --;
}
//队列非空
template  <class T>
T	priority_queue<T>::front ()
{
	return m_pHead->next ->data ;
}
//判队空
template  <class T>
bool	priority_queue<T>::empty () const
{
	return (m_pHead->next == NULL);
}
//队列长度
template  <class T>
int		priority_queue<T>::length () const
{
	return m_length;
}

template  <class T>
void    Parse ()
{
	priority_queue<T>	queue [2];

	int	n;
	cin >> n;

	string	cmd;
	int		i;
	T       x;

	for (int j = 0; j < n; j++) {
		cin >> cmd;
		if (cmd == "E") {
			cin >> i >> x; i--;
			queue [i].push (x);
		} else if (cmd == "D") {
			cin >> i;i--;
			x = queue [i].front ();
			queue [i].pop ();
			cout << x << ' ';
		} else if (cmd == "A") {
			cin >> i;i--;
			while (!queue [i].empty ()) {
				x = queue [i].front ();
				queue [i].pop ();
				cout << x << ' ';
			}
		}
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


题目描述

priority_queue是一个优先队列类模板，不过该类可以保证每次通过pop从它里面取得的元素都是剩下元素中优先级最高（最小）的。模拟STL priority_queue类模板设计实现你的优先队列类模板，该类模板需具有入队列，出队列，判队空等功能；利用该类模板实现本题要求,要求使用单链表实现,程序规范书写,支持拷贝构造、复制赋值、C++11移动构造、移动赋值（以注解形式）。




输入描述

先输入类型命令：int或string，代表后续处理对象类型为整形或字符串对象类型。据此分别构造两个队列，再读入整数n, 后面n行代表n个操作指令，每个指令占一行，分别由指令码和所需参数组成，空格分隔，指令码后第一个参数代表作用于哪个队列，后一参数（如果有的话）代表操作元素; 指令有下述几种 ： E 入队列 D出队列并输出 A将队列中所有元素出队列并输出。所有操作指令肯定是有校的。每个测试用例可能包含多个类型



/*
输出描述

每类型处理输出占一行，每个元素后加一个空格。

输入样例

int
12
E  1   2
E  1   3
E  2   6
E  1   3
E  2   9
D  1
D  2
E   2  7
A   1
A   2
E   1  12
A   1

string
15
E  1   some
E  1   one
E  2   two
E  2   tom
E  1   cat
E  2   hdu
D  1
D  2
E   2  same
A   1
D   2
A   2
E   1  again
E   1  yellow
A   1

输出样例

2 6 3 3 7 9 12
cat hdu one some same tom two again yellow
*/
