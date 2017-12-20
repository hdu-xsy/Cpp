#include<cassert>
#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;



int	main()
{
	vector<vector<int> > Array;
	int h, l;
	cin >> h >> l;
	Array.resize(h);
	int i, j;
	for (i = 0; i < h; ++i)
		Array[i].resize(l);
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < l; j++)
		{
			cin >> Array[i][j];
		}
	}
	int *sign = new int[h*l];
	int s = 0;
	sign[0] = ++s;
	for (j = 1;j < l; j++)
	{
		if (Array[0][j] == Array[0][j - 1])
			sign[j] = sign[j - 1];
		else sign[j] = ++s;
	}
	for (i = 1; i < h; i++)
	{
		if (Array[i][0] == Array[i - 1][0])
			sign[i*l] = sign[(i - 1)*l];
		else sign[i*l] = ++s;
		for (j = 1; j < l; j++)
		{
			if (Array[i][j] == Array[i][j - 1])
				sign[i*l + j] = sign[i*l + j - 1];
			else if (Array[i][j] == Array[i - 1][j])
				sign[i*l + j] = sign[(i-1)*l + j];
			else sign[i*l + j] = ++s;
		}
	}
	//
	for (j = l-2; j >=0; j--)
	{
		if (Array[h - 1][j] == Array[h - 1][j + 1])
			sign[l*(h - 1) + j] = sign[l*(h - 1) + j + 1];
	}
	for (i = h-2; i >= 0; i--)
	{
		if (Array[i][l-1] == Array[i+1][l-1])
			sign[i*l+l-1] = sign[(i+1)*l+l-1];
		for (j = l-2; j >= 0; j--)
		{
			if (Array[i][j] == Array[i][j + 1])
				sign[i*l + j] = sign[i*l + j + 1];
			else if (Array[i][j] == Array[i + 1][j])
				sign[i*l + j] = sign[(i + 1)*l + j];
		}
	}
	//
	for (i = 0; i < l*h; i++)
	{
		for (j = i + 1; j < l*h; j++)
		{
			if (sign[i] > sign[j])
			{
				int tmp;
				tmp = sign[i];
				sign[i] = sign[j];
				sign[j] = tmp;
			}
		}
	}
	int count = 1;
	for (i = 1; i < h*l; i++)
		if(sign[i]>sign[i-1])
			count ++;
	cout << count;
}
