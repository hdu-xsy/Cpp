#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class   CFunctor {
public :
    //重载函数调用运算符（），用于判断x是否为完数的函数对象
    bool    operator () (int x) {
        int iSum = 0;
        for (int i = 1; i <=x /2 ;i ++)
            if ( x % i== 0)
                iSum += i;
        return iSum == x;
    }
};
int main()
{
    vector<int>     V;
    int x;
    while (cin >>x)
        V.push_back (x); //读入并保存数据
    //统计完数个数，CFunctor ()为匿名函数对象
    int iNumber = count_if (V.begin (), V.end (), CFunctor ());
    cout << iNumber << endl;
    //查找第一个完数
    vector<int>::iterator it = find_if (V.begin (), V.end (), CFunctor ());
    if (it != V.end ()) {//输出第一个万数位置和值
        cout << it - V.begin () + 1 << "\t" << *it << endl;
    } else {//向量中并无完数
        cout << "none" << endl;
    }
}


/*
STL算法和函数对象-找完数

题目描述

如果一个正整数的所有真因子（不含本身）之和等于自身，该正整数称为完数。本题要求利用STL容器保存输入的若干个正整数，并利用函数对象和STL算法统计其中完数个数，如果有完数，输出第1个完数的序号和第一个完数，如果没有，输出none

输入描述

若干个正整数

输出描述

第1行输出完数个数
如果有完数，第2行输出第1个完数的序号和第一个完数，如果没有，第2行输出none

输入样例

1 12  6 30 28  34 496

输出样例

3
3   6
*/
