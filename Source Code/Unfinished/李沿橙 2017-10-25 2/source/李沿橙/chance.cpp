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
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + ch - '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[12];
		INT length = 0;
		bool minus = x < 0;
		if (minus) x = -x;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
			putchar(buffer[--length]);
		while (length);
	}
	putchar('\n');
}

const INT maxn = 2005;
INT n, k;
INT l[maxn], r[maxn], len[maxn], e[maxn];

INT calc(INT d)
{
	INT ret = 0;
	INT temp = 1;
	while (temp * 10 < d)
	{
		ret += temp;
		temp *= 10;
	}
	return ret + std::min(d - temp + 1, temp);
}
INT getF(INT idx)
{
	return calc(r[idx]) - calc(l[idx] - 1);
}

double f[maxn][maxn];
void run()
{
	n = readIn();
	k = readIn();
	for (int i = 1; i <= n; i++)
	{
		l[i] = readIn();
		r[i] = readIn();
		len[i] = r[i] - l[i] + 1;
		e[i] = getF(i);
	}

	f[1][1] = double(e[1]) / len[1];
	f[1][0] = double(len[1] - e[1]) / len[1];
	for (int i = 2; i <= n; i++)
	{
		f[i][0] = f[i - 1][0] * (double(len[i] - e[i]) / len[i]);
		for (int j = 1; j < i; j++)
		{
			f[i][j] = (f[i - 1][j - 1] * (double(e[i]) / len[i])) +
				(f[i - 1][j] * (double(len[i] - e[i]) / len[i]));
		}
		f[i][i] = f[i - 1][i - 1] * (double(e[i]) / len[i]);
	}
	INT m = std::ceil(double(n) * k / 100);
	double ans = 0;
	for (int i = m; i <= n; i++)
	{
		ans += f[n][i];
	}
	printf("%.8f", ans);
}

int main()
{
#ifndef JUDGE
	freopen("chance.in", "r", stdin);
	freopen("chance.out", "w", stdout);
#endif
	run();
	return 0;
}
