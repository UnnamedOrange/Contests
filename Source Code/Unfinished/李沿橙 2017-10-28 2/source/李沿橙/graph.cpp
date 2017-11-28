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
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	char buffer[15];
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

const INT maxn = 100005;
const INT maxm = 200005;
INT n, m;
struct Edge
{
	INT to;
	bool isBri;

	INT next;
} edges[maxm * 2];
INT head[maxn];
void addEdge(INT u, INT v)
{
	static INT i;
	edges[i].to = v;
	edges[i].next = head[u];
	head[u] = i;
	i++;
}

INT dfn[maxn];
INT dfs1(INT u, INT parent)
{
	static INT clock;
	INT lowu = dfn[u] = ++clock;
	for (int i = head[u]; ~i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (to == parent) continue;
		if (!dfn[to])
		{
			INT lowv = dfs1(to, u);
			lowu = std::min(lowu, lowv);
			if (lowv > dfn[u])
				edges[i].isBri = edges[i ^ 1].isBri = true;
		}
		else if (dfn[to] < dfn[u])
		{
			lowu = std::min(lowu, dfn[to]);
		}
	}
	return lowu;
}

INT cnt;
INT vis[maxn];
void dfs2(INT u)
{
	vis[u] = cnt;
	for (int i = head[u]; ~i; i = edges[i].next)
	{
		if (edges[i].isBri) continue;
		INT to = edges[i].to;
		if (!vis[to]) dfs2(to);
	}
}

INT degree[maxn];
void run()
{
	n = readIn();
	m = readIn();
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= m; i++)
	{
		INT u = readIn();
		INT v = readIn();
		addEdge(u, v);
		addEdge(v, u);
	}

	dfs1(1, 0);

	for (int i = 1; i <= n; i++)
	{
		if (!vis[i])
		{
			cnt++;
			dfs2(i);
		}
	}

	for (int i = 0; i < m * 2; i++)
	{
		if (edges[i].isBri)
		{
			degree[vis[edges[i].to]]++;
		}
	}

	INT leaf = 0;
	for (int i = 1; i <= cnt; i++)
		if (degree[i] == 1)
			leaf++;

	printOut((leaf + 1) / 2);
}

int main()
{
#ifndef JUDGE
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#endif
	run();
	return 0;
}
