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
typedef long long INT;
typedef long double REAL;
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
	putchar('\n');
}

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
INT degree[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const INT maxN = 5000;
	REAL f[maxN];

	void dfs(INT node, INT parent)
	{
		INT nEdge = degree[node] - bool(parent);
		f[node] = a[node];
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent)
				continue;

			dfs(to, node);
			f[node] += REAL(f[to]) / nEdge;
		}
	}

	brute()
	{
		INT minIdx = 0;
		REAL minVal = 1e100;
		for (int i = 1; i <= n; i++)
		{
			dfs(i, 0);
			if (f[i] < minVal)
			{
				minIdx = i;
				minVal = f[i];
			}
		}
		printOut(minIdx);
	}
};
struct work
{
	REAL f[maxn];

	void dfs1(INT node, INT parent)
	{
		INT nEdge = degree[node] - bool(parent);
		f[node] = a[node];
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent)
				continue;

			dfs1(to, node);
			f[node] += REAL(f[to]) / nEdge;
		}
	}

	REAL g[maxn];
	void dfs2(INT node, INT parent)
	{
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent)
				continue;

			if (degree[node] != 1 && degree[to] != 1)
				g[to] = a[to] + ((((g[node] - a[node]) * degree[node] - f[to]) / (degree[node] - 1) + a[node]) + (f[to] - a[to]) * (degree[to] - 1)) / degree[to];
			else if (degree[node] == 1 && degree[to] != 1)
				g[to] = ((f[to] - a[to]) * (degree[to] - 1) + a[node]) / degree[to];
			else if (degree[node] != 1 && degree[to] == 1)
				g[to] = (((g[node] - a[node]) * degree[node] - f[to]) / (degree[node] - 1) + a[node]) / degree[to] + a[to];
			dfs2(to, node);
		}
	}

	work()
	{
		dfs1(1, 0);
		g[1] = f[1];
		dfs2(1, 0);
		INT minIdx = 0;
		REAL minVal = 1e100;
		for (int i = 1; i <= n; i++)
		{
			if (g[i] < minVal)
			{
				minIdx = i;
				minVal = g[i];
			}
		}
		printOut(minIdx);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i < n; i++)
	{
		INT u = readIn();
		INT v = readIn();
		degree[u]++;
		degree[v]++;
		addEdge(u, v);
		addEdge(v, u);
	}

	if (n <= 500)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("walking.in", "r", stdin);
	freopen("walking.out", "w", stdout);
#endif
	run();
	return 0;
}
