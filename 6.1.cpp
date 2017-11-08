#include <iostream>
#include <cstring>
using namespace std;

class CString {
private:
	typedef struct Chunk {
		char ch[3];
		struct Chunk *next;
	}Chunk;
	struct LString
	{
		Chunk *head, *tail;
		int curlen;
	}*L;
public:
	CString();
	void AddChars(char *chars);
	~CString();
	CString(const CString &);
	CString & operator = (const CString &rhs);

private:
	void _Clear();
};

CString::CString()
{
	L = new LString;
	(*L).head = NULL;
	(*L).tail = NULL;
	(*L).curlen = 0;
}

void CString::AddChars(char *chars)
{
	int i, j, k, len, count;
	Chunk *r;
	len = strlen(chars);
	
}

CString::~CString()
{

}

void CString::_Clear()
{
	
}

CString::CString(const CString &rhs)
{
	
}

CString & CString::operator = (const CString &rhs)
{
	

	return *this;
}

void main()
{

}