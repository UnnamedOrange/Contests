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
#include <functional>
#include <cassert>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
LL readIn()
{
	LL a = 0;
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
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(LL x)
{
	int length = 0;
	char buffer[20];
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int n, m;
int nModify, maxx = 3;
int a[maxn];
struct Origin
{
	int type;
	int param1;
	int param2;
} origins[maxn];

#define RunInstance(x) delete new x
struct work
{
	static const int maxs = 320;
	int sqrtN;
	int N;
	int inBlocks[maxn];
	int lBegin[maxs];
	int rEnd[maxs];
	int buf[maxs][10005];
	int buf2[maxs][10005];
	void initBlocks()
	{
		sqrtN = std::sqrt(n);
		N = (n + sqrtN - 1) / sqrtN;
		for (int i = 1, v = 0; i <= n; i++, v++)
		{
			int t = inBlocks[i] = (i - 1) / sqrtN;
			if (!lBegin[t])
				lBegin[t] = i;
			rEnd[t] = i;
		}
		for (int i = 1; i <= n; i++)
			buf[inBlocks[i]][a[i]]++;
		for (int i = 1; i < N; i++)
			for (int j = 0; j <= int(1e4); j++)
				buf[i][j] += buf[i - 1][j];

		static int times[int(1e4) + 5];
		for (int i = 1; i <= n; i++)
			buf2[inBlocks[i]][++times[a[i]]]++;
	}
	work() : buf(), buf2(), lBegin(), rEnd(), inBlocks()
	{
		initBlocks();

		for (int o = 1; o <= m; o++)
		{
			const Origin& ins = origins[o];
			if (ins.type == 1)
			{
				int& num = a[ins.param2];
				if (num == ins.param1) continue;
				int ib = inBlocks[ins.param2];
				buf2[ib][buf[ib][num]]--;
				for (int i = ib + 1; i < N; i++)
				{
					buf2[i][buf[i - 1][num]]++;
					buf[i - 1][num]--;
					buf2[i][buf[i][num]]--;
				}
				buf[N - 1][num]--;
				num = ins.param1;

				buf[ib][num]++;
				buf2[ib][buf[ib][num]]++;
				for (int i = ib + 1; i < N; i++)
				{
					buf2[i][buf[i - 1][num]]--;
					buf[i][num]++;
					buf2[i][buf[i][num]]++;
				}
			}
			else if (ins.type == 2)
			{
				if (ins.param1 == 1)
					printOut(a[ins.param2]);
				else
				{
					int to = ins.param2;
					int ib = inBlocks[to];
					int num = a[to];
					int times;
					times = ib ? buf[ib - 1][num] : 0;

					for (int i = lBegin[ib]; i <= to; i++)
						if (a[i] == a[to]) times++;
					if (ins.param1 % 2 == 0)
						printOut(times);
					else
					{
						int ans = 0;
						for (int i = 0; i < ib; i++)
							ans += buf2[i][times];
						static int appear[maxs * 2];
						static int vis[int(1e4) + 5];
						static int ttimes[int(1e4) + 5];
						appear[0] = 0;
						for (int i = lBegin[ib]; i <= to; i++)
						{
							if (!vis[a[i]])
							{
								appear[++appear[0]] = a[i];
								vis[a[i]] = appear[0];
								ttimes[appear[0]] = (ib ? buf[ib - 1][a[i]] : 0);
							}
						}
						for (int i = lBegin[ib]; i <= to; i++)
						{
							if ((++ttimes[vis[a[i]]]) == times)
								ans++;
						}
						while (appear[0])
						{
							vis[appear[appear[0]--]] = 0;
						}
						printOut(ans);
					}
				}
			}
		}
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		Origin& o = origins[i];
		o.type = readIn();
		o.param1 = readIn();
		o.param2 = readIn();
		if (o.type == 1)
			nModify++;
		else
			maxx = std::max(maxx, o.param1);
	}

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("password.in", "r", stdin);
	freopen("password.out", "w", stdout);
#endif
	run();
	return 0;
}