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


/*������ħ������


��Ŀ����

����ÿһ������������n�����һ��n X n����(������ħ��), ����Ԫ����1~nƽ���������, �����ÿһ��֮�͡�ÿһ��֮�͡����Խ���֮�;���ȡ�Ҫ��ʹ�ö�̬�洢����.

��������

����������n

�������

ÿ������������ռ5λ��ÿ����������к����һ����

��������

7

�������

30   39   48    1   10   19   28
38   47    7    9   18   27   29
46    6    8   17   26   35   37
5   14   16   25   34   36   45
13   15   24   33   42   44    4
21   23   32   41   43    3   12
22   31   40   49    2   11   20
*/
