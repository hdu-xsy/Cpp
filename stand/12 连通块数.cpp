#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct POSITION {
int	row, col, dir; //行，列，下步搜索方向
};

class	CGame {
	vector<vector<int> > m_matrix;	//存放矩阵mat，四周放0，起监视哨作用
	int	m_row, m_col;
public :
	void BuildMatrix (); //建立游戏矩阵
	void Run (); //开始搜索游戏
public :
	void _BFS (int row, int col);  //搜索单一连通块
};

//建立游戏矩阵
void CGame::BuildMatrix ()
{
	int row, col;				//行和列的大小
	cin >> row >> col;			//输入

	m_matrix.clear ();
	m_row = row; m_col = col;

	vector<int> vecRowEmpty (col + 2, 0);		//向量0
	vector<int> vecRow;							//行向量
	m_matrix.push_back (vecRowEmpty);
	for (row = 0; row < m_row; row ++) {
		vecRow.clear ();
		vecRow.push_back (0);
		for (col = 0; col < m_col; col++) {
			int	x;
			cin >> x;
			vecRow.push_back (x);
		}
		vecRow.push_back (0);
		m_matrix.push_back (vecRow);
	}
	m_matrix.push_back (vecRowEmpty);
}

//搜索单一连通块
void CGame::_BFS (int row, int col)
{
	stack<POSITION>	S;  ////记录轨迹

	int	x = m_matrix [row][col];
	//保存搜索轨迹
	POSITION	pos;
	pos.row = row; pos.col = col; pos.dir = 0;
	S.push (pos);
	m_matrix [row][col] = -m_matrix [row][col];//负数表示已访问，避免重入

	int adjust [4][2] = {{1,0}, {-1,0}, {0, 1}, {0, -1}};	//方向数组
	while (!S.empty ()) {
		//取出轨迹， 回溯
		pos = S.top ();
		S.pop ();

		row = pos.row;
		col = pos.col;
		//沿当前方向前进
		row += adjust [pos.dir][0];
		col += adjust [pos.dir][1];
		if (++pos.dir < 4) {//调整方向，等待回溯
			S.push (pos);
		}
		if (m_matrix [row][col] == x) {
			//保存前进搜索轨迹
			pos.row = row; pos.col = col; pos.dir = 0;
			S.push (pos);
			m_matrix [row][col] = -m_matrix [row][col];
		}
	}
}

//开始搜索游戏
void CGame::Run ()
{
	int cnt = 0;					//记录连通块数
	for (int row = 1; row <= m_row; row++)
		for (int col = 1; col <= m_col; col ++)
			if (m_matrix [row][col] > 0) {
				//搜索单一连通块
				cnt ++;
				_BFS (row, col);
			}
	cout << cnt;
}

int main()
{
	CGame	game;

	game.BuildMatrix ();
	game.Run ();
}

/*
题目描述

读入矩阵行和列及元素数据，计算并打印出矩阵中的连通块数。注：此处，连通块定义为上、下、左、右编号（元素）相同。要求使用STL中vector保存矩阵，要求采用非递归算法。因编译器老旧，vector<<vector<int> >中> >间需空格分开。

输入描述

矩阵行和列数及元素数据。所有元素均为正整数。

输出描述

连通块数

输入样例

7 6
4   4  4   4   4    4
4   1   3   2   1    4
4   1   2   2   1    4
4   1   1   1   1    4
4   1   2   2   3    4
4   3   3   3   3    4
4   4   4   4   4    4

输出样例

6
*/
