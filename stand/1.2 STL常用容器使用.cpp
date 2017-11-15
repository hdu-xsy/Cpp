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
题目描述

编写一个C++程序, 建立整数向量V、整数队列Q、整数栈S1、S2；输入若干整数, 0作为输入结束;
将负整数依次保存在向量V中;将正整数中的素数保存在队列Q中; 将正整数中的偶数保存在栈S1中;
将正整数中的奇数保存在栈S2中;最后依次分别将保存在V、Q、S1、S2容器中的整数输出，
以’\t’作为分隔; 每个容器中整数输出后换行。

输入描述

输入若干整数, 0作为输入结束;

输出描述

每个容器中整数输出后换行。向量容器按顺序输出,队列按出队列次序输出,栈按出栈次序输出

输入样例

2 5 8 -2 -4 10 -6 9 11 0

输出样例

-2	-4	-6
2	5	11
10	8	2
11	9	5
*/
