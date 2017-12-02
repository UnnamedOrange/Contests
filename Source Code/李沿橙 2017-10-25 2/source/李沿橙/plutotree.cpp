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
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 100005;
INT n, q;
struct Edge
{
	INT to;
	INT next;
} edges[maxn];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

INT w[maxn];
INT parent[18][maxn];
INT sum[18][maxn];
INT max[18][maxn];

INT depth[maxn];
void dfs(INT node)
{
	depth[node] = depth[parent[0][node]] + 1;
	for(int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		sum[0][to] = w[to];
		max[0][to] = w[to];
		dfs(to);
	}
}

INT upSum[maxn], upMax[maxn];
INT downSum[maxn], downMax[maxn];
void dp(INT node)
{
	upSum[node] = upSum[parent[0][node]] + w[node];
	upMax[node] = std::max(upMax[parent[0][node]], w[node]);
	downSum[node] = INF;
	for(int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		dp(to);
		if(downSum[to] < downSum[node])
		{
			downSum[node] = downSum[to];
			downMax[node] = downMax[to];
		}
		else if(downSum[node] == downSum[to])
		{
			downMax[node] = std::max(downMax[node], downMax[to]);
		}
	}
	if(downSum[node] == INF) downSum[node] = 0;
	downSum[node] += w[node];
	downMax[node] = std::max(downMax[node], w[node]);
}
void dp2(INT node)
{
	for(int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if(downSum[node] + w[to] < downSum[to])
		{
			downSum[to] = downSum[node] + w[to];
			downMax[to] = std::max(downMax[node], w[to]);
		}
		dp2(to);
	}
}

INT size;
void goDouble()
{
	while(1 << size < n) size++;
	for(int i = 1; i <= size; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
			sum[i][j] = sum[i - 1][j] + sum[i - 1][parent[i - 1][j]];
			max[i][j] = std::max(max[i - 1][j], max[i - 1][parent[i - 1][j]]);
		}
	}
}

INT LCA(INT u, INT v, INT& c, INT& m)
{
	if(depth[u] < depth[v]) std::swap(u, v);
	c = 0;
	m = 0;
	for(int i = size; ~i; i--)
	{
		if(depth[parent[i][u]] < depth[v]) continue;
		c += sum[i][u];
		m = std::max(m, max[i][u]);
		u = parent[i][u];
	}
	if(u != v)
	{
		for(int i = size; ~i; i--)
		{
			if(parent[i][u] == parent[i][v]) continue;
			c += sum[i][u] + sum[i][v];
			m = std::max(m, std::max(max[i][u], max[i][v]));
			u = parent[i][u];
			v = parent[i][v];
		}
		u = parent[0][u];
	}
	c += w[u];
	m = std::max(m, w[u]);
	return u;
}

void run()
{
	n = readIn();
	q = readIn();
	for(int i = 2; i <= n; i++)
		addEdge(parent[0][i] = readIn(), i);
	for(int i = 1; i <= n; i++)
		w[i] = readIn();

	dfs(1);
	dp(1);
	goDouble();

	while(q--)
	{
		INT u = readIn();
		INT v = readIn();
		INT c, m;
		LCA(u, v, c, m);
		if(downSum[u] + upSum[v] < c)
		{
			c = downSum[u] + upSum[v];
			m = std::max(downMax[u], upMax[v]);
		}
		if(downSum[v] + upSum[u] < c)
		{
			c = downSum[v] + upSum[u];
			m = std::max(downMax[v], upMax[u]);
		}
		if(downSum[v] + downSum[u] + w[1] < c)
		{
			c = downSum[v] + downSum[u] + w[1];
			m = std::max(w[1], std::max(downMax[u], downMax[v]));
		}
		printOut(c);
		putchar(' ');
		printOut(m);
		putchar('\n');
	}
}

int main()
{
#ifndef JUDGE
	freopen("plutotree.in", "r", stdin);
	freopen("plutotree.out", "w", stdout);
#endif
	run();
	return 0;
}
