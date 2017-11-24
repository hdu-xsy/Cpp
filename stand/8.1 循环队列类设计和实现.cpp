#include <iostream>
#include <string>
using	namespace	std;
class	CQueue {
private :
	int	*m_pDatas; //��Ŷ���Ԫ�ػ�����
	int	m_size;		//��������С
	int m_front, m_rear; //���ס���β�±�
public :
	CQueue ();     //���캯��
	CQueue (const	CQueue &rhs); //��������
	~CQueue (); //����
	bool	push (int x);  //�����
	void	pop ();		//������
	int		front ();	//����Ԫ��
	bool	empty () const;  //�жӿ�
	int		length () const;  //���г���
};

CQueue::CQueue () : m_size (100)
{
	m_pDatas = new int [m_size];
	m_front  = m_rear = 0;
}

//��������
CQueue::CQueue (const	CQueue &rhs) : m_size (rhs.m_size), m_front (rhs.m_front)
{
	m_pDatas = new int [m_size];
	m_rear = m_front;
	while (m_rear != rhs.m_rear) { //����Ԫ��
		m_pDatas [m_rear] = rhs.m_pDatas [m_rear];
		m_rear = (m_rear + 1) % m_size;
	}
}

CQueue::~CQueue ()
{
	delete [] m_pDatas;  //�ͷſռ�
}

//�����
bool	CQueue::push (int x)
{
	if ((m_rear + 1) % m_size == m_front) {//ԭ�ռ����� ��1��Ԫ���ֶӿա�������
/*����������
		return false;   //�򵥴���
*/
		int	*p = new int [m_size + 10]; //������󻺳���
		int	len = m_size -1; //len =  = this->length (); //ԭ���г���
		//����ԭ����Ԫ�ص��»�����
		for (int i = 0; i < len; i++) {
			p [i] = this->front ();
			this->pop ();
		}
		//�滻ԭ������
		delete [] m_pDatas;
		m_pDatas = p;
		//�������ѱ�󣬹����¶���״̬
		m_size += 10;
		m_front = 0; //�¶���Ԫ��λ�ô��±�0��ʼ
		m_rear = m_front + len;
	}
	//�ռ�϶��㹻
	m_pDatas [m_rear] = x;
	m_rear = (m_rear+1) % m_size;
	return true;
}

//���зǿ�
void	CQueue::pop ()
{
	m_front = (m_front +1) % m_size;
}
//���зǿ�
int	CQueue::front ()
{
	return m_pDatas [m_front];
}
//�жӿ�
bool	CQueue::empty () const
{
	return (this->m_front == this->m_rear);
}
//���г���
int		CQueue::length () const
{
	int	count = 0;
	int	front = m_front;//���ɸı����״̬�����������ݳ�Աֵ
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
��Ŀ����

ģ��STL  queue�����ʵ����Ķ����࣬�������������У������У��жӿյȹ��ܣ�
���ܿ�������͸�ֵ�����ø���ʵ�ֱ���Ҫ��Ҫ��ʹ��ѭ������ʵ�֡�����淶��д

 ��������

��������

�ֱ����������У��ٶ�������n, ����n�д���n������ָ�ÿ��ָ��ռһ�У�
�ֱ���ָ��������������ɣ��ո�ָ���ָ������һ�����������������ĸ�
���У���һ����������еĻ����������Ԫ��; ָ������������ �� E  �����
D�����в����   A������������Ԫ�س����в���������в���ָ��϶�����У�ġ�

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

2 6 8 3 3 1 9 10 11 12

/*
