#include <iostream>
#include <string>
using	namespace	std;
class	CQueue {
	struct Node {
		int	data;
		Node *next;
	};//链表结点结构
private:
	Node *m_pFront, *m_pRear;//链表首结点和尾结点指针
public:
	CQueue();   //队列构造
	CQueue(const	CQueue &rhs);//队列拷贝构造
	~CQueue();   //队列析构，
	bool	push(int x); //X入队列
	void	pop();  //出队列
	int		front();  //取队首元素
	bool	empty() const;   //判队空
	int		GetLength() const; //取队列长度
};

CQueue::CQueue()
{
	this->m_pFront = this->m_pRear = new Node; //链表加头结点简化出队列、入队列操作
	m_pFront->next = NULL;
}
CQueue::CQueue(const	CQueue &rhs)  //复制队列
{
	this->m_pFront = this->m_pRear = new Node;
	this->m_pFront->next = NULL;
	Node *p = rhs.m_pFront->next;
	while (p) { //将原队列元素依次入队列
		this->push(p->data);
		p = p->next;
	}
}

CQueue::~CQueue()
{
	while (m_pFront != NULL) {
		m_pRear = m_pFront;
		m_pFront = m_pFront->next;
		delete m_pRear;
	}
}

bool	CQueue::push(int x)//X入队列
{
	Node *p = new Node;//申请结点
	p->data = x;
	p->next = NULL;
	//挂在队尾
	this->m_pRear->next = p;
	this->m_pRear = p;
	return true;
}

//队列非空
void	CQueue::pop()//出队列
{
	Node *min = this->m_pFront->next;
	Node *p = min->next;
	while (p != NULL)
	{
		if (min->data > p->data)
		{
			min = p;
		}			
		p = p->next;
	}
	Node *minpre = m_pFront;
	while (minpre->next != min)
		minpre = minpre->next;
	if (min->next != NULL)
		minpre->next = min->next;
	else
		minpre->next=NULL;
	if (min == m_pFront)
	{
		m_pFront = m_pFront->next;
	}
	if (min == m_pRear)
	{
		m_pRear = minpre;
	}
	delete min;
}


//队列非空
int	CQueue::front()
{
	Node *min = this->m_pFront->next;
	Node *p = min->next;
	while (p != NULL)
	{
		if (min->data > p->data)
		{
			min = p;
		}			
		p = p->next;
	}
	return min->data; 
}


bool	CQueue::empty() const
{
	return (this->m_pFront == this->m_pRear); //是否只有头结点
}

int		CQueue::GetLength() const
{
	int	count = 0;
	Node *p = this->m_pFront->next;//头结点不算
	while (p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}


int	main()
{
	CQueue	Queue[2];

	int	x;

	cin >> x;
	for (int i = 0; i < x; i++)
	{
		char c;
		cin >> c;
		switch (c)
		{
			case 'E':
			{
				int x1, x2;
				cin >> x1 >> x2;
				Queue[x1 - 1].push(x2);
				break;
			}
			case'D':
			{
				int x1;
				int y;
				cin >> x1;
				y = Queue[x1 - 1].front();
				Queue[x1 - 1].pop();
				cout << y << ' ';
				break;
			}
			case'A':
			{
				int x1;
				cin >> x1;
				while (!Queue[x1 - 1].empty()) 
				{
					int y = Queue[x1 - 1].front();
					Queue[x1 - 1].pop();
					cout << y << ' ';
				}
				break;
			}
		}
	}
	return 0;
}