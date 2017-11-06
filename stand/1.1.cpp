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
