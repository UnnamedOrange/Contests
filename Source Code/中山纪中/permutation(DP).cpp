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

const INT mod = 1e9 + 7;
const INT maxn = 3000;
const INT maxSize = 3005;
INT f[maxSize][maxSize];
INT q;
INT n, k;

void run()
{
	q = readIn();
	f[1][1] = 1;
	for (int i = 1; i <= maxn; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			f[i + 1][j] += f[i][j] * 2 * j;
			if (f[i + 1][j] >= mod) f[i + 1][j] %= mod;
			f[i + 1][j + 1] += f[i][j] * (i + 1 - 2 * j);
			if (f[i + 1][j + 1] >= mod) f[i + 1][j + 1] %= mod;
		}
	}

	while (q--)
	{
		n = readIn();
		k = readIn();
		INT to = n - k;
		INT ans = 0;
		for (int i = 1; i <= to; i++)
		{
			ans += f[n][i];
			if (ans >= mod) ans -= mod;
		}
		printf("%lld\n", ans);
	}
}

int main()
{
#ifndef JUDGE
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
#endif
	run();
	return 0;
}
