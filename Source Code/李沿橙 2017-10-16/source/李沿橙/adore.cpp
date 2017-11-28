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
typedef int INT;
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
INT n, m;

#define RunInstance(x) delete new x
struct work
{
	static const INT maxn = INT(1e4) + 5;
	static const INT maxk = 15;
	static const INT maxs = 1030;

	INT init[maxk];
	INT finish[maxk];
	INT rect[maxn][maxk][maxk];

	INT f[maxn][maxs];
	bool odd1[maxs];

	work() : f(), odd1()
	{
		for (int i = 1; i <= m; i++)
		{
			init[i] = readIn();
		}
		for (int i = 3; i <= n - 1; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				for (int k = 1; k <= m; k++)
				{
					rect[i][j][k] = readIn();
				}
			}
		}
		for (int i = 1; i <= m; i++)
		{
			finish[i] = readIn();
		}

		INT s = 0;
		for (int i = 0; i < m; i++)
		{
			if (init[i + 1]) s |= 1 << i;
		}
		f[2][s] = 1;

		INT U = 1 << m;
		for (int i = 1; i < U; i++)
		{
			odd1[i] = !odd1[i ^ (i & -i)];
		}

		for (int i = 3; i <= n - 1; i++)
		{
			INT to[maxk] = { 0 };
			INT toT[maxk] = { 0 };
			for (int j = 1; j <= m; j++)
			{
				for (int k = 1; k <= m; k++)
				{
					to[k] |= rect[i][j][k] << (j - 1);
					toT[j] |= rect[i][j][k] << (k - 1);
				}
			}

			for (int j = 0; j < U; j++)
			{
				INT pre = j;
				if (!f[i - 1][pre]) continue;

				INT s1 = 0;
				INT s2 = 0;
				for (int k = 1; k <= m; k++)
				{
					if (odd1[j & to[k]]) s1 |= 1 << (k - 1);
					if (odd1[j & toT[k]]) s2 |= 1 << (k - 1);
				}

				INT& ans1 = f[i][s1];
				ans1 = (ans1 + f[i - 1][pre]) % mod;
				INT& ans2 = f[i][s2];
				ans2 = (ans2 + f[i - 1][pre]) % mod;
			}
		}
		INT iFinish = 0;
		for (int i = 1; i <= m; i++)
		{
			if (finish[i]) iFinish |= 1 << (i - 1);
		}
		INT ans = 0;
		for (int j = 0; j < U; j++)
		{
			if (!odd1[j & iFinish]) ans = (ans + f[n - 1][j]) % mod;
		}
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	m = readIn();
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("adore.in", "r", stdin);
	freopen("adore.out", "w", stdout);
#endif
	run();
	return 0;
}
