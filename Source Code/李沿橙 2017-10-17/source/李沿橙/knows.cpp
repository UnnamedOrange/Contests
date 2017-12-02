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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = INT(2e5) + 5;
INT n;
INT y[maxn];
INT c[maxn];

#define RunInstance(x) delete new x
struct work
{
	work()
	{

	}
};
//Oriented to 20% data
struct cheat2
{
	INT f[maxn];

	cheat2()
	{
		memset(f, 0x3f, sizeof(f));
		f[0] = 0;
		f[1] = c[1];
		y[n + 1] = n + 1;
		for (int i = 2; i <= n + 1; i++)
		{
			for (int j = std::max(0, i - 15); j < i; j++)
			{
				if (y[j] > y[i]) continue;
				bool bOk = true;
				for (int k = j + 1; k < i; k++)
				{
					if (y[k] > y[j] && y[k] < y[i])
					{
						bOk = false;
						break;
					}
				}
				if (bOk)
				{
					f[i] = std::min(f[i], f[j] + c[i]);
				}
			}
		}
		cout << std::min(f[n], f[n + 1]) << endl;
	}
};
//Brute: normal DP, O(n ^ 2)
struct cheat
{
	static const INT maxN = 1005;
	INT f[maxN];

	cheat()
	{
		memset(f, 0x3f, sizeof(f));
		f[0] = 0;
		f[1] = c[1];
		y[n + 1] = n + 1;
		for (int i = 2; i <= n + 1; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (y[j] > y[i]) continue;
				bool bOk = true;
				for (int k = j + 1; k < i; k++)
				{
					if (y[k] > y[j] && y[k] < y[i])
					{
						bOk = false;
						break;
					}
				}
				if (bOk)
				{
					f[i] = std::min(f[i], f[j] + c[i]);
				}
			}
		}
		cout << std::min(f[n], f[n + 1]) << endl;
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		y[i] = readIn();
	}
	for (int i = 1; i <= n; i++)
	{
		c[i] = readIn();
	}

	if (n <= 1000) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("knows.in", "r", stdin);
	freopen("knows.out", "w", stdout);
#endif
	run();
	return 0;
}
