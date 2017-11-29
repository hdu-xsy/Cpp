#include <iostream>
#include <string>
using	namespace	std;
class	CQueue {
	struct Node {
		int	data;
		Node *next;
	};//������ṹ
private:
	Node *m_pFront, *m_pRear;//�����׽���β���ָ��
public:
	CQueue();   //���й���
	CQueue(const	CQueue &rhs);//���п�������
	~CQueue();   //����������
	bool	push(int x); //X�����
	void	pop();  //������
	int		front();  //ȡ����Ԫ��
	bool	empty() const;   //�жӿ�
	int		GetLength() const; //ȡ���г���
};

CQueue::CQueue()
{
	this->m_pFront = this->m_pRear = new Node; //�����ͷ���򻯳����С�����в���
	m_pFront->next = NULL;
}
CQueue::CQueue(const	CQueue &rhs)  //���ƶ���
{
	this->m_pFront = this->m_pRear = new Node;
	this->m_pFront->next = NULL;
	Node *p = rhs.m_pFront->next;
	while (p) { //��ԭ����Ԫ�����������
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

bool	CQueue::push(int x)//X�����
{
	Node *p = new Node;//������
	p->data = x;
	p->next = NULL;
	//���ڶ�β
	this->m_pRear->next = p;
	this->m_pRear = p;
	return true;
}

//���зǿ�
void	CQueue::pop()//������
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


//���зǿ�
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
	return (this->m_pFront == this->m_pRear); //�Ƿ�ֻ��ͷ���
}

int		CQueue::GetLength() const
{
	int	count = 0;
	Node *p = this->m_pFront->next;//ͷ��㲻��
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