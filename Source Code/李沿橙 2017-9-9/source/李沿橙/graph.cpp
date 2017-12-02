#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT mod = 998244353;
const INT maxn = 3005;
INT n;
INT n1, n2;

inline INT C2(INT down)
{
	return down * (down - 1) / 2 % mod;
}
inline void add(INT& a, INT b)
{
	a = (a + b) % mod;
}
INT f[maxn][maxn];

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		INT degree = readIn();
		if(degree == 1) n1++;
		else n2++;
	}

	f[0][0] = 1;
	for(int k2 = 0; k2 <= n; k2++)
	{
		for(int k1 = 0; k1 <= n; k1++)
		{
			INT& cnt = f[k1][k2];
			if(!cnt) continue; //��ǰ����û���κη������޷�ת��

			if(!k2) //�����ǰû���κζ�Ϊ2�ĵ�
				add(f[k1 + 2][k2], cnt * (k1 + 1) % mod); //����������Ϊ0�ĵ�
			add(f[k1 + 2][k2 + 1], cnt * C2(k1 + 2) % mod); //��һ��0��ȥ��������0��
			add(f[k1][k2 + 2], cnt * k1 % mod * (k2 + 1) % mod); //����������Ϊ1�ĵ�
			if(k1 >= 2)
				add(f[k1 - 2][k2 + 3], cnt * C2(k2 + 2) % mod); //��һ��0��ȥ��������1��
		}
	}

	cout << f[n1][n2] << endl;
}

int main()
{
#ifndef JUDGE
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#endif
	run();
	return 0;
}
