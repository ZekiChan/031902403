#include<iostream>
#include<fstream>
#include<sstream>
#include<locale>
using namespace std;

class mgc//敏感词类
{
public:
	string nam;//中文、英文
	string szm;//汉字首字母
	string py;//汉字拼音
	string tyz[100];//同音字（包括繁体字）
	int len_z, len_s, len_p;//敏感词长度（中文/英文、首字母、拼音）
	int fla;//判别汉字1、英文0
}m[1000];

class hang//待测文本的行类
{
public:
	string wor;//内容
	int len;//长度
}h[1000];

class sc//输出类
{
public:
	int m_num;//敏感词编号
	int h_num;//待测行编号
	int left, right;//过滤范围
}a[10000];
int snum;//输出的总数

void transformpy(mgc& M)//拼音映射函数（未实现）
{

}

void transformtyz(mgc& M)//同音字（繁体字）映射函数（未实现）
{
	
}

void search(mgc& M,int M_num, hang& H,int H_num)//在行中搜索敏感词存储到输出类
{
	int fst;//暂存搜索的第一位
	if (M.fla)//汉字搜索
	{
		for (int i = 0, j = 0 ; j < H.len; j++) //整字搜索
		if (H.wor[j] == M.nam[i] && H.wor[j + 1] == M.nam[i + 1] && H.wor[j + 2] == M.nam[i + 2])
		{
			if (i == 0) fst = j;
			i += 3;
			j += 2;
			if (j-fst>40)break;//过长抛弃
			if (i == M.len_z)
			{
				i = 0;
				a[snum].m_num = M_num;
				a[snum].h_num = H_num;
				a[snum].left = fst;
				a[snum++].right = j;
			}
		}
		for (int i = 0; i < H.len; i++)//首字母搜索
		{
			
		}
		for (int i = 0; i < H.len; i++)//全拼搜索
		{

		}
		for (int i = 0; i < H.len; i++)//同音字（包括繁体字）搜索
		{

		}
	}
	else//英文搜索
	{
		for (int i = 0, j = 0; j < H.len; j++)
		if ((H.wor[j] == M.nam[i]) || (H.wor[j] - M.nam[i] == 32 && M.nam[i] <= 'Z') || (M.nam[i] - H.wor[j] == 32 && M.nam[i] >= 'a'))
		{
			if (!i) fst = j;
			if (j-fst > 40)break;//间隔过长抛弃
			if (++i == M.len_z)
			{
				i = 0;
				a[snum].m_num = M_num;
				a[snum].h_num = H_num;
				a[snum].left = fst;
				a[snum++].right = j;
			}
		}
	}
}

int main()
{
	system("chcp 65001");//设为utf-8编码
	int i = 0, j = 0;
	string zc,str;//文件数据暂存
	int m_sum, h_sum;//敏感词、行总数暂存
	snum = 0;

	//读入敏感词
	cin >> zc;
	ifstream f1(zc);
	if (!f1)//读入异常
	{
		cout << "ERROR!" << endl;
		return 0;
	}
	while (f1 >> str)
	{
		m[i].nam = str;
		if (m[i].nam[0] > 0)m[i].fla = 0;
		else m[i].fla = 1;
		m[i++].len_z = str.length();
	}
	m_sum = i;

	//读入待测文本
	cin >> zc;
	ifstream f2(zc);
	if (!f2)//读入异常
	{
		cout << "ERROR!" << endl;
		return 0;
	}
	while (getline(f2, str))
	{
		h[j].wor = str;
		h[j++].len = str.length();
	}
	h_sum = j;

	//全拼首字母映射
	for (i = 0; i < m_sum; i++)
		transformpy(m[i]);

	//同音字繁体字映射
	for (i = 0; i < m_sum; i++)
		transformtyz(m[i]);

	//搜索并存储
	for (i = 0; i < h_sum; i++)
		for (j = 0; j < m_sum; j++)
			search(m[j],j, h[i],i);

	//输出结果
	cin >> zc;
	ofstream f3(zc);
	f3 << "Total: " << snum << endl;
	for (int i = 0; i < snum; i++)
	{
		f3 << "Line" << a[i].h_num + 1 << ": " << '<' << m[a[i].m_num].nam << "> ";
		for (int j = a[i].left; j <= a[i].right; j++) f3.put(h[a[i].h_num].wor[j]);
		f3 << endl;
	}

	//释放文件
	f1.close();
	f2.close();
	f3.close();

	return 0;
}
