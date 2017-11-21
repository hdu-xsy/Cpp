#include <iostream>
using   namespace   std;
class   CJosephRing {
    struct Node {
        int     data;
        Node    *next;
    }  *m_pLast;
public :
    CJosephRing (); //构造空环
    void  Display(); //显示环
    ~CJosephRing () {
        _Clear ();//环清空
    }
    void  Append (int x); //环队列后添加x
    void  RunGame (int N, CJosephRing &result); //一次报数N游戏，结果环队列保存在result中
private :
    void    _Clear (); //环清空
};

CJosephRing::CJosephRing ()
{
   m_pLast = NULL;
}
void  CJosephRing::Display()
{
    if (m_pLast == NULL)
        return;
    for (Node *p = m_pLast->next; ;p = p->next) {
        cout.width (4);
        cout << p->data;
        if (p == m_pLast)
            break;
    }
    cout << endl;
}

void    CJosephRing::_Clear ()
{
    if (m_pLast == NULL)
        return;
    while (m_pLast->next != m_pLast) {
        Node *p = m_pLast->next;
        m_pLast ->next = p->next;
        delete p;
    }
    delete m_pLast;
}

void  CJosephRing::Append (int x)
{
    Node *p = new Node;
    p->data = x;
    if (m_pLast == NULL) {
        p->next = p;
        m_pLast = p;
        return;
    }
    p->next = m_pLast->next;
    m_pLast ->next = p;
    m_pLast = p;
}

void  CJosephRing::RunGame (int N, CJosephRing &result)
{
    if (m_pLast == NULL)
        return;
    while (m_pLast->next != m_pLast) {
        for (int i = 1; i < N; i++)
            m_pLast = m_pLast->next;
        Node *p = m_pLast->next;
        m_pLast ->next = p->next;
        result.Append(p->data);
        delete p;
    }
    result.Append(m_pLast->data);
    delete m_pLast;
    m_pLast = NULL;
}

int main()
{
    int M,N,K;

    cin>>M>>N>>K;
    CJosephRing     firstRing, secondRing, finalRing;

    for (int i = 1; i <= M; i++) {
        firstRing.Append(i);
    }
    firstRing.RunGame(N, secondRing);
//    secondRing.Display();  //中间结果显示
    secondRing.RunGame(K, finalRing);
    finalRing.Display();
}

/*
题目描述

有M个人围坐成一圈， 编号依次从1开始递增直到M，现从编号为1的人开始报数，报到N的人出列，然后再从下一人开始重新报数，报到N的人出列；重复这一过程，直至所有人出列。所有出列的人再次按出列顺序围坐成一圈，并从第1人开始报数，这次为报到K的人出队列，然后再从下一人开始重新报数，报到K的人出列；重复这一过程，直至所有人出列。求最后出列次序

输入描述

每行包括M、N、K三个正整数；N、K可能为1

输出描述

每个测试用例结果占一行，每个编号占4位。

输入样例

10   3   5

输出样例

7   4   1   6  10   5   3   2   8   9
*/
