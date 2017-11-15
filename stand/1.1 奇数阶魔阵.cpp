#include <iostream>
#include <fstream>
using	namespace	std;

int main()
{
	int		n, k;
	while (cin >> n) {
		int	*p = new int [n*n];
		for (k = 0; k < n *n; k++)
			p [k] = 0;

		int	row = 0, col = n / 2;

		for (k = 1; k <= n*n; k++) {
			p [ row *n+col] = k;
			int	newRow, newCol;
			newRow = (row - 1 + n) % n;
			newCol = (col + 1) % n;
			if (p [ newRow *n + newCol] == 0) {
				row = newRow; col = newCol;
			} else {
				row = (row +1) % n;
			}
		}
		for (row = 0; row < n; row ++) {
			for (col = 0; col < n; col ++) {
				cout.width (5);
				cout << p [row *n+col];
			}
			cout << endl;
		}
		cout << endl;
		delete [] p;
	}
	return 0;
}


/*奇数阶魔阵问题


题目描述

对于每一个正整数奇数n，输出一个n X n矩阵(奇数阶魔阵), 矩阵元素由1~n平方整数组成, 矩阵的每一行之和、每一列之和、主对角线之和均相等。要求使用动态存储分配.

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
*/
