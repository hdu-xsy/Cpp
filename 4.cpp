#include <iostream>
using namespace std;

class Set
{
private:
	int listsize;
	int length;
	int *elem;
public:
	Set(int initsize = 10);
	Set(const Set& s);
	Set operator=(const Set& s);
	~Set();
	//Set(const Set&& s);
	//Set& operator=(const Set&& s);
	int Add(int a[], int len);
	int Add(int e);
	void Del(int i);
	bool Contains(int e) const;
	Set Intersect(const Set& s) const;
	Set Union(const Set& s) const;
	Set Difference(const Set& s);
	void sequence();
	void Print() const;
};
void main()
{
	int n1, n2;
	Set s1 = Set();
	Set s2 = Set();
	Set s = Set();
	cin >> n1 >> n2;
	int *c1 = new int[n1];
	int *c2 = new int[n2];
	for (int i = 0; i < n1; i++)
	{
		cin >> c1[i];
	}
	for (int i = 0; i < n2; i++)
	{
		cin >> c2[i];
	}
	s1.Add(c1, n1);
	s2.Add(c2, n2);
	s1.sequence();
	s2.sequence();
	s1.Print();
	s2.Print();
	s = s1.Union(s2);
	s.sequence();
	s.Print();
	s = s1.Intersect(s2);
	s.sequence();
	s.Print();
	s = s1.Difference(s2);
	s.sequence();
	s.Print();
	delete[] c1;
	delete[] c2;
	system("pause");


}
Set::Set(int initsize)
	:listsize(initsize), length(0)
{
	elem = new int[listsize];
}

Set::Set(const Set& s)
{
	listsize = s.listsize;
	length = s.length;
	elem = new int[listsize];
	memcpy(elem, s.elem, sizeof(int)*length);
}
Set Set::operator=(const Set& s)
{
	if (this != &s)
	{
		delete[] elem;
		listsize = s.listsize;
		length = s.length;
		elem = new int[listsize];
		memcpy(elem, s.elem, sizeof(int)*length);
	}
	return *this;
}
Set::~Set()
{
	delete[] elem;
}

void Set::Print() const
{
	if (length == 0)
	{
		cout << "{}" << endl;
	}
	else {
		cout << "{";
		for (int i = 0; i < length - 1; i++) {
			cout << elem[i] << ",";
		}
		cout << elem[length - 1] << "}" << endl;
	}
}

int Set::Add(int a[], int len)
{
	int c = 0;
	for (int i = 0; i < len; i++) c += Add(a[i]);
	return c;
}

int Set::Add(int e)
{
	if (Contains(e)) return 0;
	if (length == listsize)
	{
		int *tmp = new int[listsize + 10];
		if (!tmp) return 0;
		memcpy(tmp, elem, length * sizeof(int));
		listsize += 10;
		delete[] elem;
		elem = tmp;
	}
	elem[length++] = e;
	return 1;
}

void Set::Del(int i)
{
	for (int j = i; j < length-1; j++)
	{
		elem[j] = elem[j + 1];
	}
	length--;
}

bool Set::Contains(int e) const
{
	for (int i = 0; i < length; i++)
		if (elem[i] == e) return true;
	return false;
}

void Set::sequence()
{
	int temp;
	for (int j = 0; j < length - 1; j++)
	{
		for (int i = 0; i < length - 1 - j; i++)
		{
			if (elem[i] > elem[i + 1])
			{
				temp = elem[i];
				elem[i] = elem[i + 1];
				elem[i + 1] = temp;
			}
		}
	}
}

Set Set::Union(const Set& s) const
{
	Set r(s);
	r.Add(elem, length);
	return r;
}

Set Set::Intersect(const Set& s) const
{
	Set r(s.length + this->length);
	for (int i = 0; i < s.length; i++)
	{
		if (Contains(s.elem[i])) r.Add(s.elem[i]);
	}
	return r;
}

Set Set::Difference(const Set& s)
{
	Set r = Intersect(s);
	for (int i = 0; i < r.length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (elem[j] == r.elem[i])
			{
				Del(j);
			}
		}
	}
	return *this;
}

/*Set::Set(const Set&& s)
	: elem(nullptr)
	, length(0)
{
	listsize = s.listsize;
	length = s.length;
	elem = new int[listsize];
	memcpy(elem, s.elem, sizeof(int)*length);
}

Set& Set::operator=(const Set&& s)
{
	if (this != &s)
	{
		delete[] elem;
		listsize = s.listsize;
		length = s.length;
		elem = new int[listsize];
		memcpy(elem, s.elem, sizeof(int)*length);
	}
	return *this;
}
*/
