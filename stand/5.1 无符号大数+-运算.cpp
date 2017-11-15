#include <iostream>
using	namespace	std;

class	CBigNumber;	//向前声明
ostream &  operator << (ostream &os, const CBigNumber &rhs); //VC要求

class	CUBigNumber; //向前声明
ostream &  operator << (ostream &os, const CUBigNumber &rhs);  //VC要求
//无符号大整数类，超过256位废弃
class	CUBigNumber {
friend class	CBigNumber;
private :
	char	m_digitsA [256];//各位数字，为便于运算，从低位开始存放，有效0~m_len-1
	int		m_len;//有效位数
public :
	CUBigNumber () {}				//无参构造,值不确定
	CUBigNumber (unsigned int	x);	//用常规小整数构造
	CUBigNumber (char *digitsA);	//用字符串构造
	CUBigNumber operator + (const CUBigNumber &rhs) const;//
	CUBigNumber operator - (const CUBigNumber &rhs) const;//
	CUBigNumber operator * (const CUBigNumber &rhs) const;//
	CUBigNumber operator / (const CUBigNumber &rhs) const;//
	CUBigNumber operator % (const CUBigNumber &rhs) const;//
	operator unsigned int () const;	//转换为常规小整数，高位废弃
	bool	operator > (const CUBigNumber &rhs) const;		//
	bool	operator < (const CUBigNumber &rhs) const;		//
	bool	operator == (const CUBigNumber &rhs) const;		//
	bool	operator != (const CUBigNumber &rhs) const;
	bool	operator >= (const CUBigNumber &rhs) const;		//
	bool	operator <= (const CUBigNumber &rhs) const;		//
	friend ostream &  operator << (ostream &os, const CUBigNumber &rhs);//
private :
	void _Multi10 ();//10倍
	CUBigNumber _Divide (const CUBigNumber &rhs, CUBigNumber &remainder) const;//相除，结果分整数和余数部分
	_Normalize (); //规整化表示, 去除多余0, 0用m_len为0表示(不用m_len为1,数据0表示, 有利于比较处理)
};

//规整化表示, 去除多余0, 0用m_len为0表示(不用m_len为1,数据0表示, 有利于比较处理)
CUBigNumber::_Normalize ()
{
	while (m_len > 0 && m_digitsA [m_len-1] == 0)
		m_len--;
}

CUBigNumber::CUBigNumber (unsigned int	x) : m_len (0)
{
	while (x) {
		m_digitsA [m_len ++] = x % 10;
		x /= 10;
	}
}

//转换为常规小整数，高位废弃
CUBigNumber::operator unsigned int () const
{
	unsigned int x = 0;
	unsigned mul = 1;
	for (int i = 0; i < 9 && i < m_len; i++) {
		x = x  + this->m_digitsA [i] * mul;
		mul = mul * 10;
	}
	return x;
}

CUBigNumber::CUBigNumber (char *digitsA)
{
	m_len = strlen (digitsA);
	for (int i = 0; i<m_len; i++) {
		m_digitsA [i] = digitsA [m_len-1-i] - '0';
	}
	this->_Normalize ();
}
void CUBigNumber::_Multi10 ()
{
	if (m_len == 0)
		return;
	for (int i = m_len; i> 0; i--) {
		m_digitsA [i] = m_digitsA [i-1];
	}
	m_digitsA [0] = 0;
	m_len ++;
}

CUBigNumber CUBigNumber::operator + (const CUBigNumber &rhs) const
{
	CUBigNumber	bigNumber;
	int	carry = 0;//进位
	int	i = 0;
	while (i < m_len && i < rhs.m_len) {
		bigNumber.m_digitsA [i] = this->m_digitsA [i] + rhs.m_digitsA [i] + carry;
		carry = bigNumber.m_digitsA [i] / 10;
		bigNumber.m_digitsA [i] = bigNumber.m_digitsA [i] % 10;
		i++;
	}
	while (i < m_len) {
		bigNumber.m_digitsA [i] = this->m_digitsA [i] + carry;
		carry = bigNumber.m_digitsA [i] / 10;
		bigNumber.m_digitsA [i] = bigNumber.m_digitsA [i] % 10;
		i++;
	}
	while (i < rhs.m_len) {
		bigNumber.m_digitsA [i] = rhs.m_digitsA [i] + carry;
		carry = bigNumber.m_digitsA [i] / 10;
		bigNumber.m_digitsA [i] = bigNumber.m_digitsA [i] % 10;
		i++;
	}
	if (carry && i < 256) {
		bigNumber.m_digitsA [i] = carry;
		i++;
	}
	bigNumber.m_len = i;
	bigNumber._Normalize ();
	return bigNumber;
}

CUBigNumber CUBigNumber::operator - (const CUBigNumber &rhs) const
{
	if (*this <= rhs)
		return CUBigNumber ((unsigned int) 0);

	CUBigNumber	bigNumber;
	int	carry = 0;//借位
	int	i = 0;
	while (i < rhs.m_len) {
		bigNumber.m_digitsA [i] = this->m_digitsA [i] - rhs.m_digitsA [i] + carry;
		if (bigNumber.m_digitsA [i] < 0) {
			bigNumber.m_digitsA [i] += 10;
			carry = -1;
		} else
			carry = 0;
		i++;
	}
	while (i < m_len) {
		bigNumber.m_digitsA [i] = this->m_digitsA [i] + carry;
		if (bigNumber.m_digitsA [i] < 0)
			carry = -1;
		else
			carry = 0;
		i++;
	}
	bigNumber.m_len = i;
	bigNumber._Normalize ();
	return bigNumber;
}

CUBigNumber CUBigNumber::operator * (const CUBigNumber &rhs) const
{
	CUBigNumber	bigResult ((unsigned int) 0);//结果
	CUBigNumber	bigSecond (rhs);//被乘数
	for (int digit = 0; digit < m_len; digit++) {
		int	x = m_digitsA [digit];
		if (x == 0) {
			bigSecond._Multi10 ();
			continue;
		}
		CUBigNumber	partResult;//部分结果
		int	carry = 0;
		int	i = 0;
		while (i < bigSecond.m_len) {
			partResult.m_digitsA [i] = x * bigSecond.m_digitsA [i] + carry;
			carry = partResult.m_digitsA [i] / 10;
			partResult.m_digitsA [i] = partResult.m_digitsA [i] % 10;
			i++;
		}
		if (carry && i < 256) {
			partResult.m_digitsA [i] = carry;
			i++;
		}
		partResult.m_len = i;
		bigResult = bigResult + partResult;
		bigSecond._Multi10 ();
	}
	bigResult._Normalize ();
	return bigResult;
}

//相除，结果分整数和余数部分
CUBigNumber CUBigNumber::_Divide (const CUBigNumber &rhs, CUBigNumber &remainder) const
{
	if (*this < rhs) {
		remainder = *this;
		return 	CUBigNumber	((unsigned int) 0);
	}

	//取高rhs.m_len -1位
	remainder.m_len = rhs.m_len -1;
	int	i;
	for (i =0; i< remainder.m_len; i++) {
		remainder.m_digitsA [remainder.m_len-1-i] = this->m_digitsA [this->m_len - 1 - i];
	}

	CUBigNumber	bigResult ((unsigned int) 0);
	for (i = remainder.m_len; i < m_len; i++) {
		//再取1位
		remainder._Multi10 ();
		remainder.m_digitsA [0] = this->m_digitsA [this->m_len - 1 - i];
		if (remainder.m_len == 0 && 	remainder.m_digitsA [0] != 0)
			remainder.m_len = 1;
		//计算得1位结果
		int	x = 0;
		while (remainder >= rhs) {
			remainder = remainder - rhs;
			x ++;
		}
		//添加到低位
		bigResult._Multi10 ();
		bigResult.m_digitsA [0] = x;
		if (bigResult.m_len == 0 && 	bigResult.m_digitsA [0] != 0)
			bigResult.m_len = 1;
	}
	remainder._Normalize ();
	bigResult._Normalize ();
	return bigResult;
}


CUBigNumber CUBigNumber::operator / (const CUBigNumber &rhs) const
{
	CUBigNumber remainder;

	return this->_Divide (rhs, remainder);
}

CUBigNumber CUBigNumber::operator % (const CUBigNumber &rhs) const
{
	CUBigNumber remainder;

	this->_Divide (rhs, remainder);
	return remainder;
}

bool	CUBigNumber::operator < (const CUBigNumber &rhs) const
{
	//比较位数
	if (this->m_len > rhs.m_len) {
		return false;
	} else if (this->m_len < rhs.m_len) {
		return true;
	}
	//从高位开始比较
	for (int i = m_len-1; i >= 0; i--) {
		if (m_digitsA [i] > rhs.m_digitsA [i])
			return false;
		else if (m_digitsA [i] < rhs.m_digitsA [i])
			return true;
	}
	return false;//相等
}

bool	CUBigNumber::operator > (const CUBigNumber &rhs) const
{
	//比较位数
	if (this->m_len > rhs.m_len) {
		return true;
	} else if (this->m_len < rhs.m_len) {
		return false;
	}
	//从高位开始比较
	for (int i = m_len-1; i >= 0; i--) {
		if (m_digitsA [i] > rhs.m_digitsA [i])
			return true;
		else if (m_digitsA [i] < rhs.m_digitsA [i])
			return false;
	}
	return false;//相等
}

bool	CUBigNumber::operator == (const CUBigNumber &rhs) const
{
	//比较位数
	if (this->m_len != rhs.m_len ) {
		return false;
	}
	for (int i = m_len-1; i >= 0; i--) {
		if (m_digitsA [i] != rhs.m_digitsA [i])
			return false;
	}
	return true;
}
bool	CUBigNumber::operator != (const CUBigNumber &rhs) const
{
	return !(*this == rhs);
}


bool	CUBigNumber::operator >= (const CUBigNumber &rhs) const
{
	return ! (*this < rhs);
}

bool	CUBigNumber::operator <= (const CUBigNumber &rhs) const
{
	return ! (*this > rhs);
}

ostream &  operator << (ostream &os, const CUBigNumber &rhs)
{
	if (rhs.m_len == 0)
		cout << 0;
	for (int i = 0; i< rhs.m_len; i++) {
		cout << (char) (rhs.m_digitsA [rhs.m_len-1-i] + '0');
	}
	return os;
}


//测试演示程序
int	main ()
{
	char	str [257];
	cin >> str;
	CUBigNumber	bigNumber1 (str);
	cin >> str;
	CUBigNumber	bigNumber2 (str);

	CUBigNumber	bigNumber3;
	bigNumber3 = bigNumber1 + bigNumber2;
	cout <<  bigNumber3 << endl;
	bigNumber3 = bigNumber1 - bigNumber2;
	cout <<  bigNumber3 << endl;
	bigNumber3 = bigNumber1 * bigNumber2;
	cout <<  bigNumber3 << endl;

}


/*
题目描述

应用中需要解决大数运算问题。请设计无符号大数类，能支持大数+,-,*,比较运算和输出。假定本题大数在200位以内,输入数据均合法。

输入描述

输入两行分别为两个无符号大数

（第一个大数不小于第二个大数）

输出描述

它们的和  差  积

输入样例

1245623652134651416536434754367564657876876876987
1234689879657845768756

输出样例

1245623652134651416536434755602254537534722645743
1245623652134651416536434753132874778219031108231
1537958917153099098209725307498978420829044109097527114510873460018172

*/
