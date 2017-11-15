#include <iostream>
using namespace std;

class CSet{
private:
	enum	{MaxSIZE = 100};
	int	m_datas [MaxSIZE]; //����Ԫ���ڵ��������ʾ
	int m_count; // ��Ԫ�ظ���
public:
	//���캯��
	CSet();
	//����Ԫ��
	bool Add(int x);
	//��ʾ����
	void Display() const;
	//����
	CSet UnionWith (const CSet &rhs) const;
	//����
	CSet IntersectionWith (const CSet &rhs) const;
	//�
	CSet DifferentWith (const CSet &rhs) const;
	//�Ƿ����Ԫ��x
	bool In (int x) const;
	//ɾ��Ԫ��x
	bool Remove(int x);
	//�������
	void Clear ();
};


//���캯��
CSet::CSet()
{
	m_count = 0;
}

//�������
void	CSet::Clear ()
{
	m_count = 0;
}

//����Ԫ��
bool CSet::Add(int x)
{
	if (In (x))
		return false; //Ԫ�����ڼ�����
	if (m_count >= MaxSIZE)
		throw "OverFlow";  //��������, �׳��쳣������
	int	i = m_count-1;
	while (i >= 0 && x < m_datas [i]) {
		m_datas [i+1] = m_datas [i];
		i --;  //�Ӻ���ǰ,Ԫ�غ���
	}
	m_datas [i+1] = x; //����Ԫ��
	m_count ++;        //����Ԫ�ظ���
	return true;
}

//��ʾ����
void CSet::Display() const
{
	cout << "{";
	int		i;
	for (i = 0; i < m_count-1; i++) {
		cout << m_datas [i] << ",";
	}
	if (i < m_count)
		cout << m_datas [i];
	cout << "}" << endl;
}

//���ΪA��B������Ч��ΪO��M+N)
//����
CSet CSet::UnionWith (const CSet &rhs) const
{
	CSet	result;
	int	i,j;
	i=j=0;
	while (i < m_count && j < rhs.m_count) {
		if  (result.m_count >= MaxSIZE)
			throw "OverFlow";  //��������, �׳��쳣������
		//Ԫ��С�ȴ���
		if (m_datas [i] < rhs.m_datas [j]) {
			result.m_datas [result.m_count++] = m_datas [i];
			i++;
		} else if  (m_datas [i] == rhs.m_datas [j]) {
			result.m_datas [result.m_count++] = m_datas [i];
			i++;
			j++;
		} else {
			result.m_datas [result.m_count++] = rhs.m_datas [j];
			j++;
		}
	}
	while (i < m_count ) {//��������Ԫ��
		if  (result.m_count >= MaxSIZE)
			throw "OverFlow";  //��������, �׳��쳣������
		result.m_datas [result.m_count++] = m_datas [i];
		i++;
	}
	while ( j < rhs.m_count) {//����rhs����Ԫ��
		if  (result.m_count >= MaxSIZE)
			throw "OverFlow";  //��������, �׳��쳣������
		result.m_datas [result.m_count++] = rhs.m_datas [j];
		j++;
	}
	return result;
}

//����
//����Ϊ���߼�ֱ�ӵ��ó�Ա������Ч��ΪO��M*N����ʵ��Ӧ�ο�UnionWithhչ����Ч�ʿ�ΪO��M+N��
CSet CSet::IntersectionWith (const CSet &rhs) const
{
	CSet	result;

    for (int i = 0; i < m_count; i++) {
		if (rhs.In (m_datas [i]))
			result.Add (m_datas [i]);
	}
	return result;
}

//����Ϊ���߼�ֱ�ӵ��ó�Ա������Ч��ΪO��M*N����ʵ��Ӧ�ο�UnionWithչ����Ч�ʿ�ΪO��M+N��
//�
CSet CSet::DifferentWith (const CSet &rhs) const
{
	CSet	result;

    for (int i = 0; i < m_count; i++) {
		if (!rhs.In (m_datas [i]))
			result.Add (m_datas [i]);
	}
	return result;
}

//ɾ��Ԫ��
bool CSet::Remove(int x)
{
	int	i = 0;
	while (i < m_count && x < m_datas [i])
		i++;
	if (i >= m_count || x != m_datas [i]) {
		return false;//Ԫ��δ�ڼ�����
	}
	while (i+1 < m_count) {
		m_datas [i] = m_datas [i+1];
		i++; //����Ԫ��ǰ��
	}
	m_count --; //����Ԫ�ظ���
	return true;
}

//�Ƿ����Ԫ��x
bool CSet::In(int x) const
{
	int	i = 0;
	while (i < m_count && x > m_datas [i])
		i++;
	if (i < m_count && x == m_datas [i])
		return true;
	return false;
}


int main()
{
	CSet A,B,S;
	int i,m,n,x;

	cin >> m >> n;
	//����A ��
	for(i = 0; i < m; i++)
	{
		cin >> x;
		A.Add(x);
	}

	//����B ��
	for(i = 0; i < n ; i++)
	{
		cin >> x;
		B.Add(x);
	}

	A.Display();
	B.Display();


	S = A.UnionWith (B);
	S.Display();

	S = A.IntersectionWith (B);
	S.Display();

	S = A.DifferentWith (B);
	S.Display();

	return 0;
}


/*
��Ŀ����

�����ʵ�ּ����࣬Ԫ������Ϊ���Ρ��ü�����֧�ּ���Ԫ�����ӡ�ɾ������ѯ����֧�ּ��ϲ������������㣨��Ϊ���Ա������������������Ƶļ����࣬ʵ�ֱ���Ҫ�󡣳���Ӧ�����������������˼�룬�ṹ����Ϊ��֤���Ψһ������Ԫ�ص������С����輯��Ԫ�ظ�������100����Ҫ�󲢡��������������ȱ����ڼ��϶����ڣ�����Ҫ�ɼ����μӼ������㣩�������ü�����ʾ������ʾ������Ԫ�ر����������С�

��������

��ʼΪ����������m,n������m���������ɼ���A,�ٺ���n���������ɼ���B

�������

����A��B�����ǵĲ����������ÿ������Ԫ�ؼ���,�ָ�����ͬ������ʾ�ڲ�ͬ��

��������

3 5
1 2 3
3 5 8 2 1

�������

{1,2,3}
{1,2,3,5,8}
{1,2,3,5,8}
{1,2,3}
{}
*/
