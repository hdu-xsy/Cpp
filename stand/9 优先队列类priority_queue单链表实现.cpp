#include <iostream>
#include <string>
using	namespace	std;
class	priority_queue {
	struct	Node {
		int	data;
		Node *next;
	};
private :
	Node  *m_pHead; //队首
	int	m_length;
public :
	priority_queue ();     //构造函数
	priority_queue (const	priority_queue &rhs); //拷贝构造
	~priority_queue (); //析构
	bool	push (int x);  //入队列
	void	pop ();		//出队列
	int		front ();	//队首元素
	bool	empty () const;  //判队空
	int		length () const;  //队列长度
};

priority_queue::priority_queue () : m_length (0)

{
	m_pHead = new Node;
	m_pHead->next = NULL;

}

//拷贝构造
priority_queue::priority_queue (const	priority_queue &rhs) : m_length (rhs.m_length)
{
	m_pHead = new Node;
	m_pHead->next = NULL;
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

priority_queue::~priority_queue ()
{
	while (m_pHead) {
		Node *q = m_pHead->next;
		delete m_pHead;
		m_pHead = q;
	}
}

//入队列
bool	priority_queue::push (int x)
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
void	priority_queue::pop ()
{
	Node *q = m_pHead->next;
	delete m_pHead;
	m_pHead = q;
	m_length --;
}
//队列非空
int	priority_queue::front ()
{
	return m_pHead->next ->data ;
}
//判队空
bool	priority_queue::empty () const
{
	return (m_pHead->next == NULL);
}
//队列长度
int		priority_queue::length () const
{
	return m_length;
}


int	main ()
{
	priority_queue	queue [2];

	int	n;
	cin >> n;

	string	cmd;
	int		i,x;

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
	return 0;
}


/*
题目描述

priority_queue是一个优先队列类，不过该类可以保证每次通过pop从它里面取得的元素都是剩下
元素中优先级最高（最小）的。模拟STL  priority_queue类设计实现你的优先队列类，该类需具
有入队列，出队列，判队空等功能，并能拷贝构造；利用该类实现本题要求。要求使用单链表实现。
程序规范书写。

输入描述

分别构造两个队列，再读入整数n, 后面n行代表n个操作指令，每个指令占一行，分别由指令码和所
需参数组成，空格分隔，指令码后第一个参数代表作用于哪个队列，后一参数（如果有的话）代表
操作元素; 指令有下述几种 ： E  入队列 D出队列并输出   A将队列中所有元素出队列并输出。
所有操作指令肯定是有校的。

输出描述

整个输出占一行，每个元素后加一个空格。

输入样例

16
E  1   2
E  1   8
E  1   3
E  2   6
E  2   1
E  1   3
E  2   9
D  1
D  2
E   2  10
A   1
D   2
A   2
E   1  11
E   1  12
A   1

输出样例

2 1 3 3 8 6 9 10 11 12

*/
