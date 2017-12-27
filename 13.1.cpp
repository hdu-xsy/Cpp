#include<cassert>
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

class PN
{
public:
	bool operator() (int n)
	{
		int sum = 0;
		for (int i = 1; i < n; i++) {
			if ((n % i) == 0)
				sum += i;
		}
		if (sum == n)
			return true;
		else
			return false;
	}
};
int main()
{
	vector<int> v;
	int x;
	while (cin >> x)
		v.push_back(x);
	int count = count_if(v.begin(), v.end(), PN());
	cout << count << endl;
	if (count == 0)
		cout << "none";
	else
	{
		vector<int>::iterator identifier;
		for (vector<int>::const_iterator iter = v.begin(); iter != v.end(); iter++)
			identifier = find_if(v.begin(), v.end(), PN());
		cout << identifier - v.begin() + 1 << " " << *identifier << endl;
	}
	return 0;
}
