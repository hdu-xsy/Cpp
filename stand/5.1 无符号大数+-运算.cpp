#include <iostream>
using	namespace	std;

class	CBigNumber;	//��ǰ����
ostream &  operator << (ostream &os, const CBigNumber &rhs); //VCҪ��

class	CUBigNumber; //��ǰ����
ostream &  operator << (ostream &os, const CUBigNumber &rhs);  //VCҪ��
//�޷��Ŵ������࣬����256λ����
class	CUBigNumber {
friend class	CBigNumber;
private :
	char	m_digitsA [256];//��λ���֣�Ϊ�������㣬�ӵ�λ��ʼ��ţ���Ч0~m_len-1
	int		m_len;//��Чλ��
public :
	CUBigNumber () {}				//�޲ι���,ֵ��ȷ��
	CUBigNumber (unsigned int	x);	//�ó���С��������
	CUBigNumber (char *digitsA);	//���ַ�������
	CUBigNumber operator + (const CUBigNumber &rhs) const;//
	CUBigNumber operator - (const CUBigNumber &rhs) const;//
	CUBigNumber operator * (const CUBigNumber &rhs) const;//
	CUBigNumber operator / (const CUBigNumber &rhs) const;//
	CUBigNumber operator % (const CUBigNumber &rhs) const;//
	operator unsigned int () const;	//ת��Ϊ����С��������λ����
	bool	operator > (const CUBigNumber &rhs) const;		//
	bool	operator < (const CUBigNumber &rhs) const;		//
	bool	operator == (const CUBigNumber &rhs) const;		//
	bool	operator != (const CUBigNumber &rhs) const;
	bool	operator >= (const CUBigNumber &rhs) const;		//
	bool	operator <= (const CUBigNumber &rhs) const;		//
	friend ostream &  operator << (ostream &os, const CUBigNumber &rhs);//
private :
	void _Multi10 ();//10��
	CUBigNumber _Divide (const CUBigNumber &rhs, CUBigNumber &remainder) const;//������������������������
	_Normalize (); //��������ʾ, ȥ������0, 0��m_lenΪ0��ʾ(����m_lenΪ1,����0��ʾ, �����ڱȽϴ���)
};

//��������ʾ, ȥ������0, 0��m_lenΪ0��ʾ(����m_lenΪ1,����0��ʾ, �����ڱȽϴ���)
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

//ת��Ϊ����С��������λ����
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
	int	carry = 0;//��λ
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
	int	carry = 0;//��λ
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
	CUBigNumber	bigResult ((unsigned int) 0);//���
	CUBigNumber	bigSecond (rhs);//������
	for (int digit = 0; digit < m_len; digit++) {
		int	x = m_digitsA [digit];
		if (x == 0) {
			bigSecond._Multi10 ();
			continue;
		}
		CUBigNumber	partResult;//���ֽ��
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

//������������������������
CUBigNumber CUBigNumber::_Divide (const CUBigNumber &rhs, CUBigNumber &remainder) const
{
	if (*this < rhs) {
		remainder = *this;
		return 	CUBigNumber	((unsigned int) 0);
	}

	//ȡ��rhs.m_len -1λ
	remainder.m_len = rhs.m_len -1;
	int	i;
	for (i =0; i< remainder.m_len; i++) {
		remainder.m_digitsA [remainder.m_len-1-i] = this->m_digitsA [this->m_len - 1 - i];
	}

	CUBigNumber	bigResult ((unsigned int) 0);
	for (i = remainder.m_len; i < m_len; i++) {
		//��ȡ1λ
		remainder._Multi10 ();
		remainder.m_digitsA [0] = this->m_digitsA [this->m_len - 1 - i];
		if (remainder.m_len == 0 && 	remainder.m_digitsA [0] != 0)
			remainder.m_len = 1;
		//�����1λ���
		int	x = 0;
		while (remainder >= rhs) {
			remainder = remainder - rhs;
			x ++;
		}
		//��ӵ���λ
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
	//�Ƚ�λ��
	if (this->m_len > rhs.m_len) {
		return false;
	} else if (this->m_len < rhs.m_len) {
		return true;
	}
	//�Ӹ�λ��ʼ�Ƚ�
	for (int i = m_len-1; i >= 0; i--) {
		if (m_digitsA [i] > rhs.m_digitsA [i])
			return false;
		else if (m_digitsA [i] < rhs.m_digitsA [i])
			return true;
	}
	return false;//���
}

bool	CUBigNumber::operator > (const CUBigNumber &rhs) const
{
	//�Ƚ�λ��
	if (this->m_len > rhs.m_len) {
		return true;
	} else if (this->m_len < rhs.m_len) {
		return false;
	}
	//�Ӹ�λ��ʼ�Ƚ�
	for (int i = m_len-1; i >= 0; i--) {
		if (m_digitsA [i] > rhs.m_digitsA [i])
			return true;
		else if (m_digitsA [i] < rhs.m_digitsA [i])
			return false;
	}
	return false;//���
}

bool	CUBigNumber::operator == (const CUBigNumber &rhs) const
{
	//�Ƚ�λ��
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


//������ʾ����
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
��Ŀ����

Ӧ������Ҫ��������������⡣������޷��Ŵ����࣬��֧�ִ���+,-,*,�Ƚ������������ٶ����������200λ����,�������ݾ��Ϸ���

��������

�������зֱ�Ϊ�����޷��Ŵ���

����һ��������С�ڵڶ���������

�������

���ǵĺ�  ��  ��

��������

1245623652134651416536434754367564657876876876987
1234689879657845768756

�������

1245623652134651416536434755602254537534722645743
1245623652134651416536434753132874778219031108231
1537958917153099098209725307498978420829044109097527114510873460018172

*/
