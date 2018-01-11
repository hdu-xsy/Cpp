#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
using namespace std;

//灰度图像类
class   CImage {
private :
    vector<vector<int> > m_matrixDatas;
public :
    int     GetRowCount () const {
        return  m_matrixDatas.size();
    }
    int     GetColCount () const {
        return  m_matrixDatas[0].size ();
    }
    void    Input ();
    int     Match (int iStartRow, int iStartCol, const CImage &imagePattern);
};

//输入图像
void CImage::Input(){
    int m,n,x;
    cin >> m >> n;
    m_matrixDatas.clear();
    for (int row = 0; row < m; row ++) {
        vector<int> vecRow;
        for (int col = 0; col < n; col ++) {
            cin >>x;
            vecRow.push_back(x);
        }
        m_matrixDatas.push_back( (vecRow)); //m_matrixDatas.push_back(std::move (vecRow));
    }
}

//子图像与模板图像匹配差异度
int     CImage::Match (int iStartRow, int iStartCol, const CImage &imagePattern)
{
    int     iResult = 0;
    for (int iRow = 0; iRow < imagePattern.GetRowCount (); iRow++) {
        for (int iCol = 0; iCol < imagePattern.GetColCount (); iCol ++) {
            iResult += abs(this->m_matrixDatas [iStartRow + iRow][iStartCol + iCol] - imagePattern.m_matrixDatas [iRow][iCol]);
        }
    }
    return  iResult;
}

int main()
{
    CImage  imageA, imageB;

    imageA.Input();
    imageB.Input();
    if (imageA.GetRowCount() < imageB.GetRowCount() || imageA.GetColCount() < imageB.GetColCount()) {
        cout <<"Error";
        return 0;
    }

    //初定<0,0>子图像最佳匹配
    int iBestResult = imageA.Match (0, 0, imageB);
    vector<int> vecResultRows, vecResultCols;

    //迭代
    for (int iStartRow = 0; iStartRow <= imageA.GetRowCount() - imageB.GetRowCount(); iStartRow++) {
        for (int    iStartCol = 0; iStartCol <= imageA.GetColCount() - imageB.GetColCount(); iStartCol++) {
            int   iResult = imageA.Match (iStartRow, iStartCol, imageB);
            if (iBestResult < iResult) //匹配差
                continue;
            else if (iBestResult > iResult) {//更好匹配
                vecResultRows.clear();
                vecResultCols.clear();
                iBestResult = iResult;
                vecResultRows.push_back(iStartRow);
                vecResultCols.push_back(iStartCol);
            } else {//同等匹配
                vecResultRows.push_back(iStartRow);
                vecResultCols.push_back(iStartCol);
            }
        }
    }
    //输出匹配结果
    cout <<iBestResult << endl;
    for (unsigned int i = 0; i < vecResultRows.size(); i++) {
        cout << "<" << vecResultRows [i]+1<<"," << vecResultCols [i] +1<<">"<< endl;
    }
 	return 0;
}

/*
图像最佳匹配

题目描述

在某应用中, m × n 个像素灰度图像由 m × n 个正整数组成的矩阵表示，矩阵中每个整数元素表示一个像素。我们将两幅相同大小图像的差异度定义为各相同位置像素差的绝对值之和，将图像中某位置开始的m1 × n1矩形区域图像称为图像的子图像。给定m × n 个像素图像A和m1 × n1 个像素图像B,m〉=m1 且n 〉=n1, 现需要在图像A中查找与图像B具有最佳匹配(差异度最小)的大小为m1 × n1的子图像。
设计程序，分别读入图像A和图像B数据，输出主图像A的子图像与图像B的最小差异度和相应子图像在主图象中位置(左上角行列号)。 如果满足要求的子图像有多个,请分别输出各子图像的位置。本题要求设计一个图像类。

输入样例

6	15
213   66   28  226  131  243   24  250   77  159   62   77   72   17  250
36  234  254  255  241   39  149  142  136  218   87  245  139  103   41
86   38  158  167  169  253  227  188    4   99  140  111   26  205  139
0    3  134   77   52   59  164  226  237  236   58   93  253  112  207
126   60   17   15  142  217   20  193  139  237  247  249  133   86  246
143   72  194  212  207   59   10  215  114  136  194   21  206  125   14

3	4
78   53   59  165
16  119  209  20
225  217  50   11

输出样例

68
<4,4>
*/
