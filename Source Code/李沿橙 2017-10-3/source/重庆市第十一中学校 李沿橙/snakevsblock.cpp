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

const INT maxn = 205;
const INT maxk = 10010;
INT n, m;
INT rect[maxn][6];
INT block[maxn][6];

#define RunInstance(x) delete new x
struct work
{
	INT f[maxn][maxk][6];
	INT g[maxk][6][6];

	work()
	{
		memset(f, 0x80, sizeof(f));
		f[0][4][3] = 0;
		const INT maxHP = n * 50;
		INT ans = 0;
		for (int i = 1; i <= n; i++)
		{
			memset(g, 0x80, sizeof(g));
			for (int j = 0; j <= maxHP; j++)
			{
				for (int k = 1; k <= 5; k++)
				{
					if (j - rect[i][k] >= 0 && j - rect[i][k] <= maxHP)
					{
						f[i][j][k] = g[j][k][k] = f[i - 1][j - rect[i][k]][k] + (rect[i][k] < 0 ? -rect[i][k] : 0);
					}
				}
			}

			for (int length = 1; length <= 5; length++)
			{
				for (int j = 1, k = j + length; k <= 5; j++, k++)
				{
					for (int s = 0; s <= maxHP; s++)
					{
						INT t;
						if (!block[i][j] && (t = s - rect[i][j]) >= 0 && t <= maxHP)
						{
							g[s][j][k] = g[t][j + 1][k] + (rect[i][j] < 0 ? -rect[i][j] : 0);
						}
						if (!block[i][k - 1] && (t = s - rect[i][k]) >= 0 && t <= maxHP)
						{
							g[s][j][k] = std::max(g[s][j][k], g[t][j][k - 1] + (rect[i][k] < 0 ? -rect[i][k] : 0));
						}
						for (int to = j; to <= k; to++)
						{
							f[i][s][to] = std::max(f[i][s][to], g[s][j][k]);
						}
					}
				}
			}
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j <= maxHP; j++)
			{
				for (int k = 1; k <= 5; k++)
				{
					ans = std::max(ans, f[i][j][k]);
				}
			}
		}
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			rect[i][j] = readIn();
		}
	}
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT x = readIn();
		INT y = readIn();
		block[x][y] = true;
	}
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("snakevsblock.in", "r", stdin);
	freopen("snakevsblock.out", "w", stdout);
#endif
	run();
	return 0;
}
