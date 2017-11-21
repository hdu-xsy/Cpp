#include <iostream>
using   namespace   std;
class   CJosephRing {
    struct Node {
        int     data;
        Node    *next;
    }  *m_pLast;
public :
    CJosephRing (); //����ջ�
    void  Display(); //��ʾ��
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
//    secondRing.Display();  //�м�����ʾ
    secondRing.RunGame(K, finalRing);
    finalRing.Display();
}

/*
��Ŀ����

��M����Χ����һȦ�� ������δ�1��ʼ����ֱ��M���ִӱ��Ϊ1���˿�ʼ����������N���˳��У�Ȼ���ٴ���һ�˿�ʼ���±���������N���˳��У��ظ���һ���̣�ֱ�������˳��С����г��е����ٴΰ�����˳��Χ����һȦ�����ӵ�1�˿�ʼ���������Ϊ����K���˳����У�Ȼ���ٴ���һ�˿�ʼ���±���������K���˳��У��ظ���һ���̣�ֱ�������˳��С��������д���

��������

ÿ�а���M��N��K������������N��K����Ϊ1

�������

ÿ�������������ռһ�У�ÿ�����ռ4λ��

��������

10   3   5

�������

7   4   1   6  10   5   3   2   8   9
*/
