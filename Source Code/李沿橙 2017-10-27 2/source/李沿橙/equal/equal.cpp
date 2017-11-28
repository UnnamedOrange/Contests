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

const INT maxn = 100005;
INT n, m;
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
INT K;
INT size[maxn];
INT depth[maxn];
INT next[18][maxn];
void dfs(INT node)
{
	depth[node] = depth[next[0][node]] + 1;
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (to == next[0][node]) continue;
		next[0][to] = node;
		dfs(to);
		size[node] += size[to];
	}
	size[node]++;
}
void goDouble()
{
	while (1 << K < n) K++;
	for (int i = 1; i <= K; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			next[i][j] = next[i - 1][next[i - 1][j]];
		}
	}
}
INT LCA(INT u, INT v, INT& cu, INT& cv)
{
	if (depth[u] < depth[v])
		std::swap(u, v);
	for (int i = K; i >= 0; i--)
	{
		if (depth[next[i][u]] < depth[v]) continue;
		u = next[i][u];
	}
	if (u != v)
	{
		for (int i = K; i >= 0; i--)
		{
			if (next[i][u] == next[i][v]) continue;
			u = next[i][u];
			v = next[i][v];
		}
		cu = u;
		cv = v;
		u = next[0][u];
	}
	return u;
}
INT jump(INT u, INT step)
{
	INT i = 0;
	while (step)
	{
		if (step & 1) u = next[i][u];
		i++;
		step >>= 1;
	}
	return u;
}

void run()
{
	n = readIn();
	for (int i = 1; i < n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to);
		addEdge(to, from);
	}

	dfs(1);
	goDouble();

	m = readIn();
	while (m--)
	{
		INT u = readIn();
		INT v = readIn();
		if (depth[u] < depth[v]) std::swap(u, v);
		if (u == v) printOut(n);
		else
		{
			INT cu, cv;
			INT lca = LCA(u, v, cu, cv);
			if (depth[u] == depth[v])
			{
				printOut(n - size[cu] - size[cv]);
			}
			else if ((depth[u] + depth[v] - depth[lca] * 2) % 2)
			{
				printOut(0);
			}
			else
			{
				INT dis = depth[u] + depth[v] - depth[lca] * 2;
				dis >>= 1;
				cu = jump(u, dis - 1);
				printOut(size[next[0][cu]] - size[cu]);
			}
		}
	}
}

int main()
{
#ifndef JUDGE
	freopen("equal.in", "r", stdin);
	freopen("equal.out", "w", stdout);
#endif
	run();
	return 0;
}
