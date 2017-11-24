#include <iostream>
#include <string>
using	namespace	std;
class	CQueue {
private :
	int	*m_pDatas; //存放队列元素缓冲区
	int	m_size;		//缓冲区大小
	int m_front, m_rear; //队首、队尾下标
public :
	CQueue ();     //构造函数
	CQueue (const	CQueue &rhs); //拷贝构造
	~CQueue (); //析构
	bool	push (int x);  //入队列
	void	pop ();		//出队列
	int		front ();	//队首元素
	bool	empty () const;  //判队空
	int		length () const;  //队列长度
};

CQueue::CQueue () : m_size (100)
{
	m_pDatas = new int [m_size];
	m_front  = m_rear = 0;
}

//拷贝构造
CQueue::CQueue (const	CQueue &rhs) : m_size (rhs.m_size), m_front (rhs.m_front)
{
	m_pDatas = new int [m_size];
	m_rear = m_front;
	while (m_rear != rhs.m_rear) { //复制元素
		m_pDatas [m_rear] = rhs.m_pDatas [m_rear];
		m_rear = (m_rear + 1) % m_size;
	}
}

CQueue::~CQueue ()
{
	delete [] m_pDatas;  //释放空间
}

//入队列
bool	CQueue::push (int x)
{
	if ((m_rear + 1) % m_size == m_front) {//原空间已满 （1单元区分队空、队满）
/*本例不采用
		return false;   //简单处理
*/
		int	*p = new int [m_size + 10]; //申请更大缓冲区
		int	len = m_size -1; //len =  = this->length (); //原队列长度
		//复制原队列元素到新缓冲区
		for (int i = 0; i < len; i++) {
			p [i] = this->front ();
			this->pop ();
		}
		//替换原缓冲区
		delete [] m_pDatas;
		m_pDatas = p;
		//缓冲区已变大，构建新队列状态
		m_size += 10;
		m_front = 0; //新队列元素位置从下标0开始
		m_rear = m_front + len;
	}
	//空间肯定足够
	m_pDatas [m_rear] = x;
	m_rear = (m_rear+1) % m_size;
	return true;
}

//队列非空
void	CQueue::pop ()
{
	m_front = (m_front +1) % m_size;
}
//队列非空
int	CQueue::front ()
{
	return m_pDatas [m_front];
}
//判队空
bool	CQueue::empty () const
{
	return (this->m_front == this->m_rear);
}
//队列长度
int		CQueue::length () const
{
	int	count = 0;
	int	front = m_front;//不可改变队列状态，即所有数据成员值
	while (front != m_rear) {
		front = (front +1) % m_size;
	}
	return count;
}


int	main ()
{
	CQueue	Queue [2];

	int	n;
	cin >> n;

	string	cmd;
	int		i,x;

	for (int j = 0; j < n; j++) {
		cin >> cmd;
		if (cmd == "E") {
			cin >> i >> x; i--;
			Queue [i].push (x);
		} else if (cmd == "D") {
			cin >> i;i--;
			x = Queue [i].front ();
			Queue [i].pop ();
			cout << x << ' ';
		} else if (cmd == "A") {
			cin >> i;i--;
			while (!Queue [i].empty ()) {
				x = Queue [i].front ();
				Queue [i].pop ();
				cout << x << ' ';
			}
		}
	}
	cout << endl;
	return 0;
}


/*
题目描述

模拟STL  queue类设计实现你的队列类，该类需具有入队列，出队列，判队空等功能，
并能拷贝构造和赋值；利用该类实现本题要求。要求使用循环队列实现。程序规范书写

 输入描述

输入描述

分别构造两个队列，再读入整数n, 后面n行代表n个操作指令，每个指令占一行，
分别由指令码和所需参数组成，空格分隔，指令码后第一个参数代表作用于哪个
队列，后一参数（如果有的话）代表操作元素; 指令有下述几种 ： E  入队列
D出队列并输出   A将队列中所有元素出队列并输出。所有操作指令肯定是有校的。

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

2 6 8 3 3 1 9 10 11 12

/*
