#include <iostream>
using namespace std;

class CSet{
private:
	struct Node{
		int data;
		Node *next;
	} *m_pHead; // ���ϲ��õ������������ʾ
public:
	//���캯��
	CSet();
	//�����������ͷ�����
	~CSet();
	//����Ԫ��
	bool Add(int x);
	//��ʾ����
	void Display();
	//���ΪA��B����
	CSet UnionBy(const CSet &rhs) const;
	//���ΪA��B����
	CSet IntersectionBy(const CSet &rhs) const;
	//���ΪA��B�
	CSet DifferentBy(const CSet &rhs) const;

	//���г�Ա��������δ�ã��������Կ���
	//�������캯��
	CSet(const CSet &);
	//�ƶ����캯��
	//CSet(CSet &&);
	//ɾ��Ԫ��x
	bool Remove(int x);
	//�Ƿ����Ԫ��x
	bool In(int x);
	//���Ƹ�ֵ
	CSet & operator = (const CSet &rhs);
	//�ƶ���ֵ
	//CSet & operator = (CSet &&rhs);

private:
	//�������
	void	_Clear();
};


//���캯��
CSet::CSet()
{
	m_pHead = new Node;;
	m_pHead->next = NULL;
}
//�����������ͷ�����
CSet::~CSet()
{
	while (m_pHead) {
		Node *p = m_pHead;
		m_pHead = p->next;
		delete p;
	}
}

//�������
void	CSet::_Clear()
{
	while (m_pHead->next) {
		Node *p = m_pHead;
		m_pHead = p->next;
		delete p;
	}
}

//����Ԫ��
bool CSet::Add(int x)
{
	Node *p = m_pHead;
	while (p->next && (p->next->data < x)) {
		p = p->next;
	}
	if (p->next && p->next->data == x)
		return false; //Ԫ�����ڼ�����
	Node *q = new Node;
	q->data = x;
	q->next = p->next;
	p->next = q;
	return true;

}

//��ʾ����
void CSet::Display()
{
	Node *p = m_pHead->next;
	cout << "{";
	while (p)
	{
		cout << p->data;
		p = p->next;
		if (p) cout << ",";
	}
	cout << "}" << endl;
}

//���ΪA��B������ΪЧ�ʱ��⿽������
//����Ϊ���߼�ֱ�ӵ���Add��Ա������Ч��ΪO��M*N����ʵ��Ӧ�ο�IntersectionByչ����Ч�ʿ�ΪO��M+N��
CSet CSet::UnionBy(const CSet &rhs) const
{
	CSet  result;

	Node *p = m_pHead->next;
	Node *q = rhs.m_pHead->next;
	while (p && q) {
		if (p->data == q->data) {
			result.Add(p->data);
			p = p->next;
			q = q->next;
		}
		else if (p->data < q->data) {
			result.Add(p->data);
			p = p->next;
		}
		else {
			result.Add(q->data);
			q = q->next;
		}
	}
	while (p) {
		result.Add(p->data);
		p = p->next;
	}
	while (q) {
		result.Add(q->data);
		q = q->next;
	}
	return result;
}

//���ΪA��B������ΪЧ�ʱ��⿽������
CSet CSet::IntersectionBy(const CSet &rhs) const
{
	CSet  result;

	Node *last = result.m_pHead;

	Node *p = m_pHead->next;
	Node *q = rhs.m_pHead->next;
	while (p && q)	{
		if (p->data == q->data) {
			//			Add(p->data);
			Node * s = new Node;
			s->data = p->data;
			last->next = s;
			last = s;

			p = p->next;
			q = q->next;
		}
		else if (p->data  < q->data)
			p = p->next;
		else
			q = q->next;
	}
	last->next = NULL;
	return result;
}

//���ΪA��B���ΪЧ�ʱ��⿽������
//����Ϊ���߼�ֱ�ӵ���Add��Ա������Ч��ΪO��M*N����ʵ��Ӧ�ο�IntersectionByչ����Ч�ʿ�ΪO��M+N��
CSet CSet::DifferentBy(const CSet &rhs) const
{
	CSet  result;

	Node *p = m_pHead->next;
	Node *q = rhs.m_pHead->next;
	while (p && q) {
		if (p->data == q->data) {
			p = p->next;
			q = q->next;
		}
		else if (p->data  < q->data) {
			result.Add(p->data);
			p = p->next;
		}
		else
			q = q->next;
	}
	while (p) {
		result.Add(p->data);
		p = p->next;
	}
	return result;
}

//ɾ��Ԫ��
bool CSet::Remove(int x)
{
	Node *p = m_pHead;
	while (p->next && (p->next->data < x)) {
		p = p->next;
	}
	if (p->next == NULL || p->next->data != x)
		return false; //Ԫ��δ�ڼ�����
	Node *q = p->next;
	p->next = q->next;
	delete q;
	return true;
}

//�Ƿ����Ԫ��x
bool CSet::In(int x)
{
	Node *p = m_pHead;
	while (p->next && (p->next->data < x)) {
		p = p->next;
	}
	if (p->next && p->next->data == x)
		return true;
	return false;
}

//�������캯��
CSet::CSet(const CSet &rhs)
{
	//����ͷ���
	m_pHead = new Node;
	Node *last = m_pHead; //�����

	Node *p = rhs.m_pHead->next;//�����޸�rhs.m_pHead�� ��������ʱ����p
	while (p) {
		Node *q = new Node;//����һ���
		q->data = p->data; //����Ԫ��
		//�������
		last->next = q;
		last = q;
		//����һ���
		p = p->next;
	}
	last->next = NULL;
}
//�ƶ����캯��
/*
CSet::CSet(CSet &&rhs)
{
	//����ͷ���
	m_pHead = rhs.m_pHead;
	rhs.m_pHead = NULL;
}
*/
//���Ƹ�ֵ
CSet & CSet::operator = (const CSet &rhs)
{
	this->_Clear();

	Node *last = m_pHead; //�����

	Node *p = rhs.m_pHead->next;//�����޸�rhs.m_pHead�� ��������ʱ����p
	while (p) {
		Node *q = new Node;//����һ���
		q->data = p->data; //����Ԫ��
		//�������
		last->next = q;
		last = q;
		//����һ���
		p = p->next;
	}
	last->next = NULL;

	return *this;
}
//�ƶ���ֵ
/*
CSet & CSet::operator = (CSet &&rhs)
{
	Node *p = this->m_pHead;
	this->m_pHead = rhs.m_pHead;
	rhs.m_pHead = p;

	return *this;
}
*/
int main()
{
	CSet A, B, S;
	int i, m, n, x;
	cin >> m >> n;
	while ((m + n) >= 100) exit(-1);
	for (i = 0; i < m; i++)
	{
		cin >> x;
		A.Add(x);
	}
	for (i = m; i < n + m; i++)
	{
		cin >> x;
		B.Add(x);
	}
	A.Display();
	B.Display();


	S = A.UnionBy(B);
	S.Display();

	S = A.IntersectionBy(B);
	S.Display();

	S= A.DifferentBy(B);
	S.Display();

	return 0;
}