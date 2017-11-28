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
INT readIn()
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
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = INT(1e6) + 5;
INT n;
INT a[maxn];
struct Edge
{
	INT to;
	INT next;
} edges[maxn * 2];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

#define RunInstance(x) delete new x
struct brute
{
	bool isOk;
	void dfs(INT node, bool who)
	{
		if (!a[node])
		{
			if (who) isOk = true;
			return;
		}
		a[node]--;
		INT mini = INF;
		INT minn = 0;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (a[to] < mini)
			{
				mini = a[to];
				minn = to;
			}
		}
		dfs(minn, !who);
		a[node]++;
	}
	brute()
	{
		for (int i = 1; i <= n; i++)
		{
			isOk = false;
			dfs(i, 0);
			if (isOk)
			{
				static bool printed;
				if (printed) putchar(' ');
				printOut(i);
				printed = true;
			}
		}
	}
};
struct cheat
{
	static const INT maxN = 2005;
	bool f[maxN];

	void dfs(INT node, INT parent = 0)
	{
		f[node] = false;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			dfs(to, node);
			if (a[to] < a[node] && !f[to])
				f[node] = true;
		}
	}
	cheat()
	{
		for (int i = 1; i <= n; i++)
		{
			dfs(i);
			if (f[i])
			{
				static bool printed;
				if (printed) putchar(' ');
				printOut(i);
				printed = true;
			}
		}
		putchar('\n');
	}
};
struct work
{
	INT f[maxn];
	INT g[maxn];
	void dfs1(INT node, INT parent = 0)
	{
		g[node] = 0;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			dfs1(to, node);
			if (a[to] < a[node] && !g[to])
			{
				if (!g[node])
					g[node] = to;
				else
					g[node] = -1;
			}
		}
	}
	void dfs2(INT node, INT parent = 0)
	{
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;

			if (a[node] < a[to] && (!f[node] || f[node] == to))
				f[to] = g[to] ? -1 : node;
			else
				f[to] = g[to];
			dfs2(to, node);
		}
	}

	work()
	{
		dfs1(1);
		f[1] = g[1];
		dfs2(1);
		for (int i = 1; i <= n; i++)
		{
			if (f[i])
			{
				static bool printed;
				if (printed) putchar(' ');
				printOut(i);
				printed = true;
			}
		}
		putchar('\n');
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++) a[i] = readIn();
	for (int i = 1; i < n; i++)
	{
		INT u = readIn();
		INT v = readIn();
		addEdge(u, v);
		addEdge(v, u);
	}

	if (n <= 7)
		RunInstance(brute);
	else if (n <= 2000)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	run();
	return 0;
}
