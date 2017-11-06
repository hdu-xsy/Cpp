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
