#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
class mgc//���д�
{
public:
	string nam;//���ġ�Ӣ��
	string szm;//��������ĸ
	string py;//����ƴ��
	string tyz[100];//ͬ���֣����������֣�
	int num;//���
	int len_z, len_s, len_p;//����(Ӣ�ģ����ȣ�����ĸ���ȣ�ƴ������
	int fla;//�б���1Ӣ��0
}m[1000];
int msum;//����
class hang//���µ�ĳһ��
{
public:
	string wor;//����
	int num;//���
	int len;//����
}h[1000];
int hsum;//����
class sc//���
{
public:
	int m_num;//���дʱ��
	int h_num;//ĳ�б��
	int h, e;//���˷�Χ
}a[10000];
int snum;//���������

void transformpy(mgc& M)//ƴ��ת��������δʵ�֣�
{

}

void transformtyz(mgc& M)//ͬ���֣������֣�ת��������δʵ�֣�
{
	
}

void search(mgc& M, hang& H)//��ĳһ��������һ�����дʲ����д洢
{
	int i = 0, j = 0, fst;
	if (M.fla)//��������
	{
		for ( ; j < H.len; j++) //��������
		if (H.wor[j] == M.nam[i] && H.wor[j + 1] == M.nam[i + 1] && H.wor[j + 2] == M.nam[i + 2])
		{
			if (i == 0) fst = j;
			i += 3;
			j += 2;
			if (i == M.len_z)
			{
				a[snum].m_num = M.num;
				a[snum].h_num = H.num;
				a[snum].h = fst;
				a[snum++].e = j;
				i = 0;
			}
		}
		for (i = 0; i < H.len; i++)//����ĸ����
		{
			
		}
		for (i = 0; i < H.len; i++)//ȫƴ����
		{

		}
		for (i = 0; i < H.len; i++)//ͬ���֣����������֣�����
		{

		}
	}
	else//Ӣ������
	{
		for (; j < H.len; j++)
		if ((H.wor[j] == M.nam[i]) || (H.wor[j] - M.nam[i] == 32 && M.nam[i] <= 'Z') || (M.nam[i] - H.wor[j] == 32 && M.nam[i] >= 'a'))
		{
			if (!i) fst = j;
			if (++i == M.len_z)
			{
				a[snum].m_num = M.num;
				a[snum].h_num = H.num;
				a[snum].h = fst;
				a[snum++].e = j;
				i = 0;
			}
		}
	}
}

int main()
{
	system("chcp 65001");
	int i = 0, j = 0;
	string dz,str;
	snum = 0;

	//�������д�
	cin >> dz;
	ifstream f1(dz);
	while (f1 >> str)
	{
		m[i].nam = str;
		if (m[i].nam[0] > 0)m[i].fla = 0;
		else m[i].fla = 1;
		m[i].num = i;
		m[i++].len_z = str.length();
	}
	msum = i;
	f1.close();

	//��������
	cin >> dz;
	ifstream f2(dz);
	while (getline(f2, str))
	{
		h[j].wor = str;
		h[j].num = j;
		h[j++].len = str.length();
	}
	hsum = j;
	f2.close();

	//ȫƴ����ĸת��
	for (i = 0; i < msum; i++)
		transformpy(m[i]);

	//ͬ���ַ�����ת��
	for (i = 0; i < msum; i++)
		transformtyz(m[i]);

	//�������洢
	for (j = 0; j < hsum; j++)
		for (i = 0; i < msum; i++)
			search(m[i], h[j]);

	//�����
	cin >> dz;
	ofstream f3(dz);
	f3 << "Total: " << snum << endl;
	for (int i = 0; i < snum; i++)
	{
		f3 << "Line" << a[i].h_num + 1 << ": " << '<' << m[a[i].m_num].nam << "> ";
		for (int j = a[i].h; j <= a[i].e; j++) f3.put(h[a[i].h_num].wor[j]);
		f3 << endl;
	}
	f3.close();

	return 0;
}