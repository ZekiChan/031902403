#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
class mgc//敏感词
{
public:
	string nam;//中文、英文
	string szm;//汉字首字母
	string py;//汉字拼音
	string tyz[100];//同音字（包括繁体字）
	int num;//标号
	int len_z, len_s, len_p;//中文(英文）长度，首字母长度，拼音长度
	int fla;//判别汉字1英文0
}m[1000];
int msum;//总数
class hang//文章的某一行
{
public:
	string wor;//内容
	int num;//标号
	int len;//长度
}h[1000];
int hsum;//总数
class sc//输出
{
public:
	int m_num;//敏感词标号
	int h_num;//某行标号
	int h, e;//过滤范围
}a[10000];
int snum;//输出的总数

void transformpy(mgc& M)//拼音转换函数（未实现）
{

}

void transformtyz(mgc& M)//同音字（繁体字）转换函数（未实现）
{
	
}

void search(mgc& M, hang& H)//在某一行中搜索一个敏感词并进行存储
{
	int i = 0, j = 0, fst;
	if (M.fla)//汉字搜索
	{
		for ( ; j < H.len; j++) //整字搜索
		if (H.wor[j] == M.nam[i] && H.wor[j + 1] == M.nam[i + 1] && H.wor[j + 2] == M.nam[i + 2])
		{
			if (i == 0) fst = j;
			i += 3;
			j += 2;
			if (i == M.len_z)
			{
				i = 0;
				a[snum].m_num = M.num;
				a[snum].h_num = H.num;
				a[snum].h = fst;
				a[snum++].e = j;
			}
		}
		for (i = 0; i < H.len; i++)//首字母搜索
		{
			
		}
		for (i = 0; i < H.len; i++)//全拼搜索
		{

		}
		for (i = 0; i < H.len; i++)//同音字（包括繁体字）搜索
		{

		}
	}
	else//英文搜索
	{
		for (; j < H.len; j++)
		if ((H.wor[j] == M.nam[i]) || (H.wor[j] - M.nam[i] == 32 && M.nam[i] <= 'Z') || (M.nam[i] - H.wor[j] == 32 && M.nam[i] >= 'a'))
		{
			if (!i) fst = j;
			if (++i == M.len_z)
			{
				i = 0;
				a[snum].m_num = M.num;
				a[snum].h_num = H.num;
				a[snum].h = fst;
				a[snum++].e = j;
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

	//读入敏感词
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

	//读入文章
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

	//全拼首字母转换
	for (i = 0; i < msum; i++)
		transformpy(m[i]);

	//同音字繁体字转换
	for (i = 0; i < msum; i++)
		transformtyz(m[i]);

	//搜索并存储
	for (i = 0; i < msum; i++)
		for (j = 0; j < hsum; j++)
			search(m[i], h[j]);

	//输出结果
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
