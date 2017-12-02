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

const INT maxn = 21;
const INT mod = 1e9 + 7;
int n, m, k;
int rMap[maxn];
int count1[1050000];
int g[1050000][maxn];
INT f[1050000][maxn];

inline int lowbit(int x)
{
	return x & -x;
}

inline void add(INT& x, INT& y)
{
	INT ans = x + y;
	x = ans >= mod ? ans - mod : ans;
}

void work()
{
	INT U = 1 << n;
	for (int i = 1; i <= m; i++)
	{
		INT front = readIn() - 1;
		INT back = readIn() - 1;
		rMap[front] |= 1 << back;
	}
	for (int i = 1; i < U; i++)
	{
		count1[i] = count1[i ^ lowbit(i)] + 1;
	}
	for (int i = 0; i < n; i++)
	{
		for (int S = 1; S < U; S++)
		{
			if (!(S & (1 << i)))
			{
				g[S][i] = count1[S & rMap[i]];
			}
		}
	}

	f[0][0] = 1;
	for (int S = 0; S < U; S++)
		for (int i = 0; i <= k; i++)
			if (f[S][i])
				for (int j = 0; j < n; j++)
					if (!(S & (1 << j)) && i + g[S][j] <= k)
						add(f[S | (1 << j)][i + g[S][j]], f[S][i]);

	INT ans = 0;
	for (int i = 0; i <= k; i++)
	{
		add(ans, f[U - 1][i]);
	}
	cout << ans << endl;
}

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	work();
}

int main()
{
#ifndef JUDGE
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
#endif
	run();
	return 0;
}
