#include <iostream>
#include <string>
using	namespace	std;
class	priority_queue {
	struct	Node {
		int	data;
		Node *next;
	};
private :
	Node  *m_pHead; //����
	int	m_length;
public :
	priority_queue ();     //���캯��
	priority_queue (const	priority_queue &rhs); //��������
	~priority_queue (); //����
	bool	push (int x);  //�����
	void	pop ();		//������
	int		front ();	//����Ԫ��
	bool	empty () const;  //�жӿ�
	int		length () const;  //���г���
};

priority_queue::priority_queue () : m_length (0)

{
	m_pHead = new Node;
	m_pHead->next = NULL;

}

//��������
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

//�����
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

//���зǿ�
void	priority_queue::pop ()
{
	Node *q = m_pHead->next;
	delete m_pHead;
	m_pHead = q;
	m_length --;
}
//���зǿ�
int	priority_queue::front ()
{
	return m_pHead->next ->data ;
}
//�жӿ�
bool	priority_queue::empty () const
{
	return (m_pHead->next == NULL);
}
//���г���
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
��Ŀ����

priority_queue��һ�����ȶ����࣬����������Ա�֤ÿ��ͨ��pop��������ȡ�õ�Ԫ�ض���ʣ��
Ԫ�������ȼ���ߣ���С���ġ�ģ��STL  priority_queue�����ʵ��������ȶ����࣬�������
������У������У��жӿյȹ��ܣ����ܿ������죻���ø���ʵ�ֱ���Ҫ��Ҫ��ʹ�õ�����ʵ�֡�
����淶��д��

��������

�ֱ����������У��ٶ�������n, ����n�д���n������ָ�ÿ��ָ��ռһ�У��ֱ���ָ�������
�������ɣ��ո�ָ���ָ������һ�����������������ĸ����У���һ����������еĻ�������
����Ԫ��; ָ������������ �� E  ����� D�����в����   A������������Ԫ�س����в������
���в���ָ��϶�����У�ġ�

�������

�������ռһ�У�ÿ��Ԫ�غ��һ���ո�

��������

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

�������

2 1 3 3 8 6 9 10 11 12

*/
