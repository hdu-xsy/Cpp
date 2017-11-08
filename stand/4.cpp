#include <iostream>
using namespace std;

class CSet{
private:
	struct Node{
		int data;
		Node *next;
	} *m_pHead; // 集合采用递增排序单链表表示
public:
	//构造函数
	CSet();
	//析构函数，释放链表
	~CSet();
	//增加元素
	bool Add(int x);
	//显示集合
	void Display();
	//结果为A、B并集
	CSet UnionBy(const CSet &rhs) const;
	//结果为A、B交集
	CSet IntersectionBy(const CSet &rhs) const;
	//结果为A、B差集
	CSet DifferentBy(const CSet &rhs) const;

	//下列成员函数本例未用，纯完整性考虑
	//拷贝构造函数
	CSet(const CSet &);
	//移动构造函数
	//CSet(CSet &&);
	//删除元素x
	bool Remove(int x);
	//是否包含元素x
	bool In(int x);
	//复制赋值
	CSet & operator = (const CSet &rhs);
	//移动赋值
	//CSet & operator = (CSet &&rhs);

private:
	//集合清空
	void	_Clear();
};


//构造函数
CSet::CSet()
{
	m_pHead = new Node;;
	m_pHead->next = NULL;
}
//析构函数，释放链表
CSet::~CSet()
{
	while (m_pHead) {
		Node *p = m_pHead;
		m_pHead = p->next;
		delete p;
	}
}

//集合清空
void	CSet::_Clear()
{
	while (m_pHead->next) {
		Node *p = m_pHead;
		m_pHead = p->next;
		delete p;
	}
}

//增加元素
bool CSet::Add(int x)
{
	Node *p = m_pHead;
	while (p->next && (p->next->data < x)) {
		p = p->next;
	}
	if (p->next && p->next->data == x)
		return false; //元素已在集合中
	Node *q = new Node;
	q->data = x;
	q->next = p->next;
	p->next = q;
	return true;

}

//显示集合
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

//结果为A、B并集，为效率避免拷贝构造
//本例为简化逻辑直接调用Add成员函数，效率为O（M*N）；实际应参考IntersectionBy展开，效率可为O（M+N）
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

//结果为A、B交集，为效率避免拷贝构造
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

//结果为A、B差集，为效率避免拷贝构造
//本例为简化逻辑直接调用Add成员函数，效率为O（M*N）；实际应参考IntersectionBy展开，效率可为O（M+N）
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

//删除元素
bool CSet::Remove(int x)
{
	Node *p = m_pHead;
	while (p->next && (p->next->data < x)) {
		p = p->next;
	}
	if (p->next == NULL || p->next->data != x)
		return false; //元素未在集合中
	Node *q = p->next;
	p->next = q->next;
	delete q;
	return true;
}

//是否包含元素x
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

//拷贝构造函数
CSet::CSet(const CSet &rhs)
{
	//复制头结点
	m_pHead = new Node;
	Node *last = m_pHead; //最后结点

	Node *p = rhs.m_pHead->next;//不可修改rhs.m_pHead， 故引入临时变量p
	while (p) {
		Node *q = new Node;//申请一结点
		q->data = p->data; //复制元素
		//挂在最后
		last->next = q;
		last = q;
		//后移一结点
		p = p->next;
	}
	last->next = NULL;
}
//移动构造函数
/*
CSet::CSet(CSet &&rhs)
{
	//复制头结点
	m_pHead = rhs.m_pHead;
	rhs.m_pHead = NULL;
}
*/
//复制赋值
CSet & CSet::operator = (const CSet &rhs)
{
	this->_Clear();

	Node *last = m_pHead; //最后结点

	Node *p = rhs.m_pHead->next;//不可修改rhs.m_pHead， 故引入临时变量p
	while (p) {
		Node *q = new Node;//申请一结点
		q->data = p->data; //复制元素
		//挂在最后
		last->next = q;
		last = q;
		//后移一结点
		p = p->next;
	}
	last->next = NULL;

	return *this;
}
//移动赋值
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