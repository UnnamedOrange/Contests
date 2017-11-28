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
typedef int INT;
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

const INT maxn = 8005;
INT n, q;
INT a[maxn];
INT t;
INT disc[maxn];

#define RunInstance(x) delete new x
struct cheat
{
	INT sub[maxn * 2];

	cheat() : sub()
	{
		while (q--)
		{
			INT x = readIn();
			INT y = readIn();
			INT pos;
			pos = std::lower_bound(disc + 1, disc + 1 + t, x) - disc;
			if (1 <= pos && pos <= t && x == disc[pos]) x = pos;
			else x = 0;
			pos = std::lower_bound(disc + 1, disc + 1 + t, y) - disc;
			if (1 <= pos && pos <= t && y == disc[pos]) y = pos;
			else y = 0;

			const INT delta = n;
			sub[0 + delta] = 1;
			INT tx = 0;
			INT ty = 0;
			for (int i = 1; i <= n; i++)
			{
				if (a[i] == x) tx++;
				if (a[i] == y) ty++;
				sub[tx - ty + delta]++;
			}

			INT ans = 0;
			for (int i = 0; i <= 2 * n; i++)
			{
				ans += sub[i] * (sub[i] - 1) / 2;
				sub[i] = 0;
			}
			printOut(ans);
		}
	}
};
struct work
{
	INT ans[maxn][maxn];
	struct Edge
	{
		INT pos;
		INT next;
	} e[maxn];
	INT head[maxn];
	void addEdge(INT node, INT pos)
	{
		static INT i;
		i++;
		e[i].pos = pos;
		e[i].next = head[node];
		head[node] = i;
	}

	INT times[maxn * 2];

	work() : head()
	{
		memset(ans, -1, sizeof(ans));
		for (int i = n; i >= 1; i--)
			addEdge(a[i], i);

		const INT delta = n;
		while (q--)
		{
			INT x = readIn();
			INT y = readIn();
			INT pos;
			pos = std::lower_bound(disc + 1, disc + 1 + t, x) - disc;
			if (1 <= pos && pos <= t && x == disc[pos]) x = pos;
			else x = 0;
			pos = std::lower_bound(disc + 1, disc + 1 + t, y) - disc;
			if (1 <= pos && pos <= t && y == disc[pos]) y = pos;
			else y = 0;

			if (!~ans[y][x]) ans[x][y] = ans[y][x];
			if (!~ans[x][y])
			{
				ans[x][y] = 0;

				INT minVal = 0;
				INT maxVal = 0;
				times[delta] = 0;

				INT cntCount = 0;
				INT cntPos = 0;
				INT k1 = head[x];
				INT k2 = head[y];

				while (k1 || k2)
				{
					if (!k2 || k1 && e[k1].pos < e[k2].pos)
					{
						times[cntCount + delta] += e[k1].pos - cntPos;
						cntCount++;
						if (cntCount > maxVal)
							times[(maxVal = cntCount) + delta] = 0;
						cntPos = e[k1].pos;
						k1 = e[k1].next;
					}
					else
					{
						times[cntCount + delta] += e[k2].pos - cntPos;
						cntCount--;
						if (cntCount < minVal)
							times[(minVal = cntCount) + delta] = 0;
						cntPos = e[k2].pos;
						k2 = e[k2].next;
					}
				}
				times[cntCount + delta] += n - cntPos + 1;

				for (int k = minVal; k <= maxVal; k++)
				{
					ans[x][y] += times[k + delta] * (times[k + delta] - 1) / 2;
				}
			}
			printOut(ans[x][y]);
		}
	}
};

void discretize()
{
	for (int i = 1; i <= n; i++) disc[i] = a[i];
	std::sort(disc + 1, disc + 1 + n);
	t = std::unique(disc + 1, disc + 1 + n) - (disc + 1);
	for (int i = 1; i <= n; i++)
		a[i] = std::lower_bound(disc + 1, disc + 1 + t, a[i]) - disc;
}
void run()
{
	n = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++) a[i] = readIn();

	discretize();
	if (n <= 100 && q <= 1000)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("query.in", "r", stdin);
	freopen("query.out", "w", stdout);
#endif
	run();
	return 0;
}
