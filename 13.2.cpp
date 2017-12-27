#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

class Picture
{
public:
	Picture();
	~Picture();
	Picture(int x, int y);
	Picture(const Picture &rhs);
	Picture & operator = (const Picture &rhs);
	void match(const Picture &rhs);
	void print();
	void scan();
private:
	int x;
	int y;
	vector<vector<int> >pixel;
};

Picture::Picture()
{
	x = 0;
	y = 0;
}

Picture::Picture(int x, int y)
{
	this->x = x;
	this->y = y;
	pixel.resize(y);
	for (int h = 0; h < y; h++)
		pixel[h].resize(x);
}

Picture::~Picture()
{

}

void Picture::print()
{
	for (int h = 0; h < y; h++)
	{
		for (int l = 0; l < x; l++)
		{
			cout << pixel[h][l] << " ";
		}
		cout << endl;
	}
}

void Picture::scan()
{
	for (int h = 0; h < y; h++)
	{
		for (int l = 0; l < x; l++)
		{
			cin >> pixel[h][l];
		}
	}
}

Picture::Picture(const Picture &rhs)
{
	x = rhs.x;
	y = rhs.y;
	pixel.resize(y);
	for (int h = 0; h < y; h++)
		pixel[h].resize(x);
	for (int h = 0; h < y; h++)
	{
		for (int l = 0; l < x; l++)
		{
			pixel[h][l] = rhs.pixel[h][l];
		}
	}
}

Picture& Picture::operator = (const Picture &rhs)
{
	x = rhs.x;
	y = rhs.y;
	pixel.resize(y);
	for (int h = 0; h < y; h++)
		pixel[h].resize(x);
	for (int h = 0; h < y; h++)
	{
		for (int l = 0; l < x; l++)
		{
			pixel[h][l] = rhs.pixel[h][l];
		}
	}
	return *this;
}

void Picture::match(const Picture &rhs)
{
	vector<vector<int> >mabs;
	mabs.resize(y - rhs.y + 1);
	int min = INT_MAX;
	for (int h = 0; h < y - rhs.y + 1; h++)
		mabs[h].resize(x - rhs.x + 1);
	for (int j = 0; j < y - rhs.y+1 ; j++)
	{
		for (int i = 0; i < x - rhs.x+1 ; i++)
		{
			mabs[j][i] = 0;
			for (int h = 0; h < rhs.y; h++)
			{
				for (int l = 0; l < rhs.x; l++)
				{
					mabs[j][i] += abs(pixel[j + h][l + i] - rhs.pixel[h][l]);
				}
			}
			if (min > mabs[j][i])
			{
				min = mabs[j][i];
			}
		}
	}
	cout << min << endl;
	for (int j = 0; j < y - rhs.y + 1; j++)
	{
		for (int i = 0; i < x - rhs.x + 1; i++)
		{
			if (mabs[j][i] == min)
				cout << "<" << j + 1 << "," << i + 1 << ">" << endl;
		}
	}
}

int main()
{
	int x1, y1;
	cin >> y1 >> x1;
	Picture p1 = Picture(x1, y1);
	p1.scan();
	int x2, y2;
	cin >> y2 >> x2;
	Picture p2 = Picture(x2, y2);
	p2.scan();
	p1.match(p2);
	return 0;

}
