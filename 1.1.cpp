using namespace std;
int main()
{
    int n;
    cin >> n;
    int **A;
	A=new int*[n];
	for(int i=0;i<n;i++)
	{
		A[i]=new int[n];
		memset(A[i],0,n*sizeof(int));
	}


    int x=0,y,m =1;
	y=n/2;
	while (m<=n*n)
	{
		A[x][y] = m;
		int x0=x;
		int y0=y;
		x0--;
		y0++;
		if(x0 < 0)
			x0+=n;
		if(y0 == n)
			y0= n - y0;
		if(A[x0][y0] != 0)
		{
			x++;
			if(x == n)
			x = x-n;
		}
		else
		{
			x = x0;
			y = y0;
		}
		m ++;
	}
		for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<A[i][j]<<"\t";
		cout<<endl;
	}
    delete [] A;
}


/*题目描述

对于每一个正整数奇数n，输出一个n X n矩阵(奇数阶魔阵), 矩阵元素由1~n平方整数组成,
矩阵的每一行之和、每一列之和、主对角线之和均相等。要求使用动态存储分配.

输入描述

正整数奇数n

输出描述

每个阵列中整数占5位，每阵列输出阵列后输出一空行

输入样例

7

输出样例

30   39   48    1   10   19   28
38   47    7    9   18   27   29
46    6    8   17   26   35   37
5   14   16   25   34   36   45
13   15   24   33   42   44    4
21   23   32   41   43    3   12
22   31   40   49    2   11   20
