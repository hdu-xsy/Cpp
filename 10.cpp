#include<cassert>
#include<iostream>
#include<string>
using namespace std;
template<typename T>
class CVector
{
public:
	enum { SPARE_CAPACITY = 5 };
	typedef T* iterator;
	typedef const T* const_iterator;

	explicit CVector(int initsize = 0);
	CVector(int initsize, T value);

	CVector(const CVector &rhs);
	CVector<T>& operator=(const CVector & rhs);
	~CVector() { delete[] elem; }


	bool empty()const { return Length == 0; }
	int size() const { return Length; }
	int capacity() const { return Vsize; }
	iterator begin() { return &elem[0]; }
	iterator end() { return &elem[Length]; }

	bool operator==(const CVector<T>& rhs);
	bool operator!=(const CVector<T>& rhs);


	void reserve(int newcapacity);
	void resize(int newsize, const T &thevalue);
	void resize(int newsize);
	void shrink_to_fit();

	T &operator[](int index);
	const T &operator[](int index) const;
	T &front();
	const T &front() const;
	T &back();
	const T &back() const;
	void push_back(const T &x);
	iterator insert(int n, iterator b, const T &value);
	iterator put(iterator b, const T &value);
	void pop_back() { Length--; }
	iterator erase(int n, iterator b);
	void clear();

private:
	T *elem;
	int Length;
	int Vsize;
};


template <typename T>
CVector<T>::CVector(int initsize = 0) :Length(initsize), Vsize(initsize + SPARE_CAPACITY)
{
	elem = new T[Vsize];
	assert(elem != NULL);
}

template <typename T>
CVector<T>::CVector(int initsize, T value) :Length(initsize), Vsize(initsize + SPARE_CAPACITY)
{
	elem = new T[Vsize];
	assert(elem != NULL);
	for (int i = 0; i != Length; ++i)
		elem[i] = value;
}


template <typename T>
CVector<T>::CVector(const CVector &rhs)
{
	used = rhs.used;
	Length = rhs.Length;
	Vsize = rhs.Vsize;
	elem = new T[Vsize];
	assert(elem != NULL);
	for (int i = 0; i != Length; ++i)
		elem[i] = rhs.elem[i];
}


template<typename T>
CVector<T>& CVector<T>::operator=(const CVector &rhs)
{
	if (this != &rhs)
	{
		delete[]elem;
		used = rhs.used;
		Length = rhs.Length;
		Vsize = rhs.Vsize;
		elem = new T[Vsize];
		assert(elem != NULL);
		for (int i = 0; i != Length; ++i)
			elem[i] = rhs.elem[i];
	}
	return *this;
}

template<typename T>
bool CVector<T>::operator==(const CVector<T>& rhs)
{
	if (this->Length == rhs.Length)
	{
		int cnt = 0;
		for (int i = 0; i != Length; i++)
			if (this->elem[i] == rhs.elem[i])
				++cnt;
		if (cnt == Length)
			return true;
	}
	return false;
}
template<typename T>
bool CVector<T>::operator!=(const CVector<T>& rhs)
{
	return !(*this == rhs);
}


template<typename T>
void CVector<T>::reserve(int newcapacity)
{
	if (newcapacity <= Vsize)
	{
		if (newcapacity < Vsize / 2)
		{
			T *newarray = new T[newcapacity];
			int newsize = newcapacity > Length ? Length : newcapacity;
			for (int i = 0; i != newsize; ++i)
				newarray[i] = elem[i];
			delete[] elem;
			elem = newarray;
			Vsize = newcapacity;
		}
		return;
	}
	T *newarray = new T[newcapacity];
	for (int i = 0; i != Length; ++i)
		newarray[i] = elem[i];
	delete[] elem;
	elem = newarray;
	Vsize = newcapacity;
}


template<typename T>
void CVector<T>::resize(int newsize, const T & thevalue)
{
	if (newsize > Length)
	{
		if (newsize > Vsize)
			reserve(newsize * 2 + 1);
		for (int i = Length; i != newsize; ++i)
			elem[i] = thevalue;
	}
	else if (newsize< Length)
	{
		if (newsize<Vsize / 2)
			reserve(newsize);
	}
	Length = newsize;
}
template<typename T>
void CVector<T>::resize(int newsize)
{
	resize(newsize, T());
}
template<typename T>
void CVector<T>::shrink_to_fit()
{
	reserve(Length + SPARE_CAPACITY);
}


template<typename T>
T & CVector<T>::operator[](int index)
{
	if (index < 0 || index >= Length)
	{
		throw "invalid index:";
	}
	return elem[index];
}
template<typename T>
const T &CVector<T>::operator[](int index) const
{
	if (index < 0 || index >= Length)
	{
		throw "invalid index:";
	}
	return elem[index];
}
template<typename T>
T& CVector<T>::front()
{
	if (!this->empty())
		return elem[0];
}
template<typename T>
const T& CVector<T>::front() const
{
	if (!this->empty())
		return elem[0];
}
template<typename T>
T& CVector<T>::back()
{
	if (!this->empty())
		return elem[Length - 1];
}
template<typename T>
const T& CVector<T>::back() const
{
	if (!this->empty())
		return elem[Length - 1];
}


template<typename T>
void CVector<T>::push_back(const T &x)
{
	if (Length == Vsize)
		reserve(2 * Vsize);
	elem[Length++] = x;
}
template<typename T>
T* CVector<T>::insert(int n,iterator b, const T &value)
{
	if (b < this->begin() || b> this->end())
	{
		throw "invalid index:";
	}
	int num = b - elem;
	if (Length == Vsize)
	{
		reserve(Length * 2);
		b = elem + num;
	}
	for (iterator p = this->end(); p > b; p--)
		*p = *(p - 1);
	*b = value;
	Length++;
	return b;
}
template<typename T>
T* CVector<T>::put(iterator b, const T &value)
{
	if (b < this->begin() || b> this->end())
	{
		throw "invalid index:";
	}
	int num = b - elem;
	if (Length == Vsize)
	{
		reserve(Length * 2);
		b = elem + num;
	}
	*b = value;
	return b;
}


template<typename T>
T* CVector<T>::erase(int n,iterator b)
{
	if (b < this->begin() || b >= this->end())
	{
		throw "invalid index:" ;
	}
	iterator q = b + 1;
	int num = q - elem;
	iterator p = this->end() - 1;
	for (; b < p; b++)
		*b = *(b + 1);
	Length--;
	if (Length <= Vsize / 4)
	{
		reserve(Length + SPARE_CAPACITY);
		iterator q1 = elem + num;
	}
	return q;
}
template<typename T>
void CVector<T>::clear()
{
	Length = 0;
}


void main()
{

	string n1,n2;
	int m = 0;
	while (cin >> n1)
	{
		if (n1 == "int")
		{
			cin >> m;
			CVector<int> v1(m);
			while (cin >> n2)
			{
				if (n2 == "quit") {
					cout << endl;
					break;
				}
				else if (n2 == "push")
				{
					int m2;
					cin >> m2;
					v1.push_back(m2);
				}
				else if (n2 == "put")
				{
					int k1=0, k2=0;
					try
					{
						cin >> k1 >> k2;
						v1.put(v1.begin() + k1, k2);
					}
					catch (const char* msg) {
						cerr << msg << k1 << " ";
					}

				}
				else if (n2 == "fetch")
				{
					int m2;
					try
					{
						cin >> m2;
						cout << v1[m2] << " ";
					}
					catch (const char* msg) {
						cerr << msg << m2 << " ";
					}
				}

			}
		}


		if (n1 == "string")
		{
			cin >> m;
			CVector<string> v2(m);
			while (cin >> n2)
			{
				if (n2 == "quit") {
					cout << endl;
					break;
				}
				else if (n2 == "push")
				{
					string m2;
					cin >> m2;
					v2.push_back(m2);
				}
				else if (n2 == "put")
				{
					int k1 = 0;string k2;
					try
					{
						cin >> k1 >> k2;
						v2.put(v2.begin() + k1, k2);
					}
					catch (const char* msg) {
						cerr << msg << k1 << " ";
					}

				}
				else if (n2 == "fetch")
				{
					int m2;
					try
					{
						cin >> m2;
						cout << v2[m2] << " ";
					}
					catch (const char* msg) {
						cerr << msg << m2 << " ";
					}
				}

			}
		}
	}

}
