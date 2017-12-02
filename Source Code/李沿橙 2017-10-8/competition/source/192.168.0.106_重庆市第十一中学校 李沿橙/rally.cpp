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

const INT maxn = 405;
INT n, m, mod;
INT rect[maxn][maxn];

#define RunInstance(x) delete new x
struct cheat
{
	cheat()
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				rect[i][j] += rect[i - 1][j] + rect[i][j - 1] - rect[i - 1][j - 1];
			}
		}

		INT ans = 0;
		for(int x1 = 1; x1 <= n; x1++)
		{
			for(int y1 = 1; y1 <= m; y1++)
			{
				for(int x2 = x1; x2 <= n; x2++)
				{
					for(int y2 = y1; y2 <= m; y2++)
					{
						INT val = rect[x2][y2] - rect[x1 - 1][y2] - rect[x2][y1 - 1] + rect[x1 - 1][y1 - 1];
						ans += (val % mod == 0);
					}
				}
			}
		}
		cout << ans << endl;
	}
};
struct work
{
	work()
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				
			}
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	mod = readIn();
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			rect[i][j] = readIn();
		}
	}

	if(n * m <= 6400) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("rally.in", "r", stdin);
	freopen("rally.out", "w", stdout);
#endif
	run();
	return 0;
}
