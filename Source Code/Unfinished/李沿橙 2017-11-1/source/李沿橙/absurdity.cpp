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
	static char buffer[20];
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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = INT(2e4) + 5;
const INT maxm = INT(2.5e4) + 5;
INT n, m;
INT c[maxn];
struct Edge
{
	INT to;
	INT next;
} edges[maxm * 2];
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
	brute()
	{
		INT U = 1 << n;
		INT ans = INF;
		for (INT S = 1; S < U; S++)
		{
			INT cost = 0;
			for (int i = 0; i < n; i++)
				if (S & (1 << i))cost += c[i + 1];

			if (cost >= ans) continue;

			bool bAval = true;
			for (int i = 0; i < n; i++)
			{
				if (S & (1 << i)) continue;
				bool bOk = false;
				for (int j = head[i + 1]; j; j = edges[j].next)
				{
					INT to = edges[j].to - 1;
					if (S & (1 << to))
					{
						bOk = true;
						break;
					}
				}
				if (!bOk)
				{
					bAval = false;
					break;
				}
			}
			if (bAval) ans = std::min(ans, cost);
		}
		printOut(ans);
	}
};
struct cheat
{
	INT f[3][maxn];
	bool vis[maxn];

	void dfs(INT node, INT parent)
	{
		vis[node] = true;
		f[0][node] = c[node];
		INT sum = 0;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			dfs(to, node);

			f[0][node] += std::min(f[0][to], std::min(f[1][to], f[2][to]));
			if (f[2][node] < INF)
				if (f[1][to] < INF) f[2][node] += f[1][to];
				else f[2][node] = INF;
				sum += std::min(f[0][to], f[1][to]);
		}
		f[1][node] = INF;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;

			f[1][node] = std::min(f[1][node], sum - std::min(f[0][to], f[1][to]) + f[0][to]);
		}
	}

	cheat() : f(), vis()
	{
		INT ans = 0;
		for (int i = 1; i <= n; i++)
		{
			if (!vis[i])
			{
				dfs(i, 0);
				ans += std::min(f[0][i], f[1][i]);
			}
		}
		printOut(ans);
	}
};

struct DS
{
	INT parent[maxn];
	INT block;
	void clear(INT size)
	{
		block = size;
		for (int i = 1; i <= size; i++)
			parent[i] = i;
	}
	INT find(INT x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	void unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		if (px == py) return;
		parent[py] = px;
		block--;
	}
} ds;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		c[i] = readIn();

	for (int i = 1; i <= m; i++)
	{
		INT u = readIn();
		INT v = readIn();
		addEdge(u, v);
		addEdge(v, u);
		ds.unite(u, v);
	}

	if (n <= 20 && m <= 50)
		RunInstance(brute);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef JUDGE
	freopen("absurdity.in", "r", stdin);
	freopen("absurdity.out", "w", stdout);
#endif
	run();
	return 0;
}
