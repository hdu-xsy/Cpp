#include <stack>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

bool    IsPrime (int    x);

int main()
{
    queue<int>  Q;
    vector<int> V;
    stack<int>  S1,S2;
    int     x;

    cin >> x;
    while (x != 0) {
        if (x < 0) {
            V.push_back(x);
        } else {
            if (IsPrime (x))
                Q.push(x);
            if (x % 2 == 0)
                S1.push (x);
            else
                S2.push (x);
        }
        cin >> x;
    }

    for (unsigned int i = 0; i < V.size(); i++)
        cout << V [i] << '\t';
    cout << endl;

    while (!Q.empty ()) {
        x = Q.front () ;
        cout << x << '\t';
        Q.pop ();
    }
    cout << endl;

    while (!S1.empty ()) {
        x = S1.top ();
        cout << x << '\t';
        S1.pop ();
    }
    cout << endl;
    while (!S2.empty ()) {
        x = S2.top ();
        cout << x << '\t';
        S2.pop ();
    }
    cout << endl;

	return 0;
}

bool    IsPrime (int    x)
{
    if  (x == 1)
        return false;
    for (int  i = 2; i <= (int)(sqrt ((double)x)+0.5); i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}


/*
��Ŀ����

��дһ��C++����, ������������V����������Q������ջS1��S2��������������, 0��Ϊ�������;
�����������α���������V��;���������е����������ڶ���Q��; ���������е�ż��������ջS1��;
���������е�����������ջS2��;������ηֱ𽫱�����V��Q��S1��S2�����е����������
�ԡ�\t����Ϊ�ָ�; ÿ������������������С�

��������

������������, 0��Ϊ�������;

�������

ÿ������������������С�����������˳�����,���а������д������,ջ����ջ�������

��������

2 5 8 -2 -4 10 -6 9 11 0

�������

-2	-4	-6
2	5	11
10	8	2
11	9	5
*/
