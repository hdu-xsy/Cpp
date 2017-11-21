#include <iostream>
using   namespace   std;
class   CJosephRing {
    struct Node {
        int     data;
        Node    *next;
    }  *m_pLast;
public :
    CJosephRing (); //构造空环
    void  Display() const ; //显示环
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
void  CJosephRing::Display() const
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
    int     M,N;
    int     times =  0;

    cin>>M;
    CJosephRing     firstRing, secondRing;

    for (int i = 1; i <= M; i++) {
        firstRing.Append(i);
    }
    while  (cin >>N) {
        if (times % 2 == 0)
            firstRing.RunGame(N, secondRing);
        else
            secondRing.RunGame(N, firstRing);
        ++times;
    }
    if (times % 2 == 0)
        firstRing.Display();
    else
        secondRing.Display();
}

/*
题目描述

有M个人，编号分别为1到M，玩约瑟夫环游戏，最初时按编号顺序排成队列；每遍游戏开始时，有一个正整数报数密码N，队列中人依次围坐成一圈，从队首的人开始报数，报到N的人出列，然后再从出列的下一人开始重新报数，报到N的人出列；重复这一过程，直至所有人出列，完成一遍游戏，所有出列的人形成新队列；游戏可能玩很多遍，每遍有新报数密码。求若干遍游戏完成后队列次序。

输入描述

每个测试用例包含若干个正整数（至少1个），第一个正整数为玩游戏人数M，后续每个正整数为每遍游戏报数密码；报数密码可能为1

输出描述

每个测试用例结果占一行，每个编号占4位。

输入样例

10   3   5    2

输出样例

4   6   5   2   9   1   3   7   8  10
*/
