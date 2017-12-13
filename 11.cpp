#include<cassert>
#include<iostream>
#include<string>
using namespace std;

template<typename T>
class priority_queue
{
	struct	Node {
		T data;
		Node *next;
	};

private:
	Node  *m_pHead;
	int	m_length;
public:
	priority_queue() : m_length(0)
	{
		m_pHead = new Node;
		m_pHead->next = NULL;
	}

	priority_queue(const priority_queue &rhs) : m_length(rhs.m_length)
	{
		m_pHead = new Node;
		m_pHead->next = NULL;
		Node *last = m_pHead;
		Node *p = rhs.m_pHead->next;
		while (p) {
			Node *q = new Node;
			q->data = p->data;
			last->next = q;
			last = q;
			p = p->next;
		}
		last->next = NULL;
	}

	/*
	priority_queue(priority_queue &&rhs) : m_length(rhs.m_length)
	{
		m_pHead = new Node;
		m_pHead->next = NULL;
		Node *last = m_pHead;
		Node *p = rhs.m_pHead->next;
		while (p) {
			Node *q = new Node;
			q->data = p->data;
			last->next = q;
			last = q;
			p = p->next;
		}
		last->next = NULL;
		rhs.m_length = 0;
		while (rhs.m_pHead) {
		Node *q = rhs.m_pHead->next;
		delete rhs.m_pHead;
		rhs.m_pHead = q;
		}
	}
	*/

	~priority_queue()
	{
		while (m_pHead) {
			Node *q = m_pHead->next;
			delete m_pHead;
			m_pHead = q;
		}
	}

	bool	push(T x)
	{
		Node *q = new Node;
		q->data = x;
		Node *p = m_pHead;
		while (p->next && x > p->next->data)
			p = p->next;
		q->next = p->next;
		p->next = q;
		m_length++;
		return true;
	}
	void pop()
	{
		Node *q = m_pHead->next;
		delete m_pHead;
		m_pHead = q;
		m_length--;
	}

	T	front() { return m_pHead->next->data; }
	bool	empty() const { return (m_pHead->next == NULL); }
	int		length() const { return m_length; }
};


int	main()
{
	string type;
	while (cin >> type)
	{
		if (type == "string")
		{
			priority_queue<string> queue[2];

			int	n;
			cin >> n;

			string	cmd;
			int	i;
			string x;

			for (int j = 0; j < n; j++) {
				cin >> cmd;
				if (cmd == "E") {
					cin >> i >> x; i--;
					queue[i].push(x);
				}
				else if (cmd == "D") {
					cin >> i; i--;
					x = queue[i].front();
					queue[i].pop();
					cout << x << ' ';
				}
				else if (cmd == "A") {
					cin >> i; i--;
					while (!queue[i].empty()) {
						x = queue[i].front();
						queue[i].pop();
						cout << x << ' ';
					}
				}
			}
			cout << endl;
		}
		else if (type == "int")
		{
			priority_queue<int> queue[2];

			int	n;
			cin >> n;

			string	cmd;
			int	i;
			int x;

			for (int j = 0; j < n; j++) {
				cin >> cmd;
				if (cmd == "E") {
					cin >> i >> x; i--;
					queue[i].push(x);
				}
				else if (cmd == "D") {
					cin >> i; i--;
					x = queue[i].front();
					queue[i].pop();
					cout << x << ' ';
				}
				else if (cmd == "A") {
					cin >> i; i--;
					while (!queue[i].empty()) {
						x = queue[i].front();
						queue[i].pop();
						cout << x << ' ';
					}
				}
			}
			cout << endl;
		}
	}

	return 0;
}
