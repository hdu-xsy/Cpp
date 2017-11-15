#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
using namespace std;

class Joseph {
private:
	struct node {
		int data;
		node *next;
	}*p, *pre, *head;
	int M;

public:
	Joseph(int n);
	void out(Joseph &j, int k);
	void print();
};

Joseph::Joseph(int n)
{
	p = NULL, pre = NULL, head = NULL;
	M = n;
	for (int i = 1; i <= n; i++)
	{
		p = new node;
		p->data = i;
		if (head == NULL)
			head = p;
		else
			pre->next = p;
		pre = p;
	}
	p->next = head;
}

void Joseph::out(Joseph &j, int k) {
	if (k != 1)
	{
		node *q;
		p = head;
		q = p;
		j.p = j.head;
		while (p->next != p)
		{
			for (int i = 1; i < k; i++)
			{
				q = p;
				p = p->next;
			}
			j.p->data = p->data;
			j.p = j.p->next;
			q->next = p->next;
			delete p;
			p = q->next;
		}
		j.p->data = p->data;
		delete p;
	}
	else
	{
		p = head;
		j.p = j.head;
		for (int i = 0; i < M; i++)
		{
			j.p->data = p->data;
			j.p = j.p->next;
			p = p->next;
		}
	}
}

void Joseph::print() {
	p = head;
	for (int i = 0; i < M; i++)
	{
		cout << p->data << setw(4);
		p = p->next;
	}
}
void main() {
	int m, k;
	cin >> m;
	int Chk = 1;
	Joseph j1 = Joseph(m);
	Joseph j2 = Joseph(m);
	while (cin >> k)
	{
		if (Chk == 1)
		{
			j2 = Joseph(m);
			j1.out(j2, k);
			Chk = 0;
		}
		else
		{
			j1 = Joseph(m);
			j2.out(j1, k);
			Chk = 1;
		}
	}
	if (Chk == 0)
		j2.print();
	else
		j1.print();
}
