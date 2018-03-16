#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int mod = int(1e9) + 7;
const int maxn = int(1e5) + 5;
int n, m;
int param[65][3];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 25;
	int rect[maxN][maxN];
	int a[maxN];
	brute()
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				rect[i][j] = 1;
		for (int i = 1; i <= m; i++)
			rect[param[i][0]][param[i][1]] = param[i][2];

		for (int i = 1; i <= n; i++)
			a[i] = i;
		int ans = 0;
		do
		{
			LL mul = 1;
			for (int i = 1; i <= n; i++)
				mul = mul * rect[i][a[i]] % mod;
			ans = ans + mul >= mod ? ans + mul - mod : ans + mul;
		} while (std::next_permutation(a + 1, a + 1 + n));
		printOut(ans);
	}
};
struct cheat
{
	static const int maxN = 20;
	int rect[maxN][maxN];
	int F[2][1 << maxN];
	int count1[1 << maxN];

	cheat() : F()
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				rect[i][j] = 1;
		for (int i = 1; i <= m; i++)
			rect[param[i][0] - 1][param[i][1] - 1] = param[i][2];

		int U = 1 << n;

		count1[0] = 0;
		for (int i = 1; i < U; i++)
			count1[i] = count1[i ^ (i & -i)] + 1;

		for (int i = 0; i < n; i++)
			F[0][1 << i] = rect[0][i];
		for (int i = 1; i < n; i++)
		{
			int cnt = i & 1;
			int pre = !cnt;
			int *f = F[cnt], *g = F[pre];
			memset(F[cnt], 0, sizeof(F[cnt]));
			int *r = rect[i];
			for (int S = 0; S < U; S++)
			{
				if (count1[S] != i + 1) continue;
				for (int j = 0, k = 1; j < n; j++, k <<= 1)
				{
					if (!(S & k)) continue;
					f[S] = (f[S] + (LL)g[S ^ k] * r[j]) % mod;
				}
			}
		}
		printOut(F[(n - 1) & 1][U - 1]);
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		param[i][0] = readIn();
		param[i][1] = readIn();
		param[i][2] = readIn();
	}
	if (n <= 10)
		RunInstance(brute);
	else if (n <= 20)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("wudongchao.in", "r", stdin);
	freopen("wudongchao.out", "w", stdout);
#endif
	run();
	return 0;
}