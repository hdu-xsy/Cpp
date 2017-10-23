using namespace std;

class SqStack
{
private:
    struct Node
    {
        int data;
        Node *next;
    };
    Node *head;
    Node *p;
    int length;

public:
    SqStack()
    {
        head = NULL;
        length = 0;
    }
    void Push(int n)	//入栈
    {
        Node *q = new Node;
        q->data = n;
        if (head == NULL)
        {
            q->next = head;
            head = q;
            p = q;
        }
        else
        {
            q->next = p;
            p = q;
        }
        length ++;
    }

    void Pop()	//出栈
    {
        Node *q;
        q = p;
        p = p->next;
        delete(q);
        length --;
    }

    int Top()	//取栈顶元素
    {
        return p->data;
    }

    bool isEmpty()	//判栈空
    {
        if (length == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

void main()
{
	int n1,n2;
    SqStack s1;
	SqStack s2;
	while(scanf("%d%d",&n1,&n2) != EOF)
	{
		switch(n1)
		{
			case 1:
				s1.Push(n2);
				break;
			case 2:
				s2.Push(n2);
				break;
		}
	}
	while(!s1.isEmpty())
	{
		cout << s1.Top() << " ";
		s1.Pop();
	}
		cout<<endl;
	while(!s2.isEmpty())
	{
		cout << s2.Top() << " ";
		s2.Pop();
	}

}


/*
题目描述

模拟STL  stack类设计实现你的stack类，该类需具有入栈，出栈，判栈空，取栈顶元素等功能；利用该类实现本题要求。本题要求使用单链表实现。不可使用STL  stack类

输入描述

分别构造两个空栈，再读入若干对整数v、x; 1<=v<=2; 将元素x入第v个栈 。

输出描述

最后将两个栈中元素出栈，并输出；每个栈中元素占一行，元素间以空格分隔。

输入样例

1 100
2 200
1 300
2 400
1 50
1 60
2 80

输出样例

60 50 300 100
80 400 200
*/
