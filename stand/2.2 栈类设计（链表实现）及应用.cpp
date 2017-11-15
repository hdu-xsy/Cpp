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
	CStack	()  :m_sp(NULL)   { //���캯��
	}
	CStack	(const CStack &rhs);//�������캯��
	CStack & operator =	(const CStack &rhs);//��ֵ���������

	~CStack	();				 //��������
	void	push (int x);	 //��ջ
	bool	empty () const;  //��ջ��
	int		top () const;    //ȡջ��Ԫ��
	void	pop ();			 //��ջ
};

CStack::CStack	(const CStack &rhs) //�������캯��
{
	m_sp = NULL;
	if (rhs.empty ()) //��ջ��
		return;

	//���������׽��
	m_sp  = new Node;
	Node *q = rhs.m_sp;
	m_sp->data = q->data;

	//��������������
	Node	*last = m_sp; //��¼��������δ���
	q = q->next;
	while (q != NULL) {
		Node *p = new Node;
		p->data = q->data;//��������
		last->next = p; //�½��������������
		last = p;		//�½��������
		q = q->next;	//׼��������һ���
	}
	last->next = NULL;	//�����ָ���ÿ�
}

CStack & CStack::operator =	(const CStack &rhs)//��ֵ���������
{
	if (this == &rhs)
		return *this;
	this->~CStack ();  //��������

	m_sp = NULL;
	if (rhs.empty ()) //��ջ��
		return *this; //��������

	//���������׽��
	m_sp  = new Node;
	Node *q = rhs.m_sp;
	m_sp->data = q->data;

	//��������������
	Node	*last = m_sp; //��¼��������δ���
	q = q->next;
	while (q != NULL) {
		Node *p = new Node;
		p->data = q->data;//��������
		last->next = p; //�½��������������
		last = p;		//�½��������
		q = q->next;	//׼��������һ���
	}
	last->next = NULL;	//�����ָ���ÿ�

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
��Ŀ����

ģ��STL  stack�����ʵ�����stack�࣬�����������ջ����ջ����ջ�գ�ȡջ��Ԫ�صȹ��ܣ����ø���ʵ�ֱ���Ҫ�󡣱���Ҫ��ʹ�õ�����ʵ�֡�����ʹ��STL  stack��

��������

�ֱ���������ջ���ٶ������ɶ�����v��x; 1<=v<=2; ��Ԫ��x���v��ջ ��

�������

�������ջ��Ԫ�س�ջ���������ÿ��ջ��Ԫ��ռһ�У�Ԫ�ؼ��Կո�ָ���

��������

1 100
2 200
1 300
2 400
1 50
1 60
2 80

�������

60 50 300 100
80 400 200

��Ŀ����

ģ��STL  stack�����ʵ�����stack�࣬�����������ջ����ջ����ջ�գ�ȡջ��Ԫ�صȹ��ܣ����ø���ʵ�ֱ���Ҫ�󡣱���Ҫ��ʹ�õ�����ʵ�֡�����ʹ��STL  stack��

��������

�ֱ���������ջ���ٶ������ɶ�����v��x; 1<=v<=2; ��Ԫ��x���v��ջ ��
*/



�������

�������ջ��Ԫ�س�ջ���������ÿ��ջ��Ԫ��ռһ�У�Ԫ�ؼ��Կո�ָ���




��������

1 100
2 200
1 300
2 400
1 50
1 60
2 80




�������

60 50 300 100
80 400 200
