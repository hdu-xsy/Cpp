#include <iostream>
using   namespace   std;
class   CJosephRing {
    struct Node {
        int     data;
        Node    *next;
    }  *m_pLast;
public :
    CJosephRing (); //����ջ�
    void  Display() const ; //��ʾ��
    ~CJosephRing () {
        _Clear ();//�����
    }
    void  Append (int x); //�����к����x
    void  RunGame (int N, CJosephRing &result); //һ�α���N��Ϸ����������б�����result��
private :
    void    _Clear (); //�����
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
��Ŀ����

��M���ˣ���ŷֱ�Ϊ1��M����Լɪ����Ϸ�����ʱ�����˳���ųɶ��У�ÿ����Ϸ��ʼʱ����һ����������������N��������������Χ����һȦ���Ӷ��׵��˿�ʼ����������N���˳��У�Ȼ���ٴӳ��е���һ�˿�ʼ���±���������N���˳��У��ظ���һ���̣�ֱ�������˳��У����һ����Ϸ�����г��е����γ��¶��У���Ϸ������ܶ�飬ÿ�����±������롣�����ɱ���Ϸ��ɺ���д���

��������

ÿ�����������������ɸ�������������1��������һ��������Ϊ����Ϸ����M������ÿ��������Ϊÿ����Ϸ�������룻�����������Ϊ1

�������

ÿ�������������ռһ�У�ÿ�����ռ4λ��

��������

10   3   5    2

�������

4   6   5   2   9   1   3   7   8  10
*/
