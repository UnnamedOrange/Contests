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
inline void printOut(INT x)
{
	if(!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[14];
		INT length = 0;
		while(x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		do
		{
			putchar(buffer[--length]);
		}
		while(length);
	}
	putchar('\n');
}

const INT mod = INT(1e9) + 7;
const INT maxn = 100005;
INT n;
INT weight[maxn];

INT Inv(INT x)
{
	INT y = mod - 2;
	INT ret = 1;
	while(y)
	{
		if(y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

struct E
{
	INT from;
	INT to;
	E() {}
	E(INT from, INT to) : from(from), to(to) {}
} e[maxn];
struct Edge
{
	INT to;

	INT next;
} edges[2 * maxn];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT nCount = 0;
	nCount++;
	edges[nCount].to = to;
	edges[nCount].next = head[from];
	head[from] = nCount;
}

INT maxD;
INT depth[maxn];
INT next[18][maxn];
INT cost[18][maxn];

void DFS(INT node)
{
	for(int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if(to == next[0][node]) continue;
		depth[to] = depth[node] + 1;
		next[0][to] = node;
		DFS(to);
	}
}
void goDouble()
{
	depth[1] = 1;
	DFS(1);
	while(1 << maxD < n) maxD++;
	for(int i = 1; i <= maxD; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			next[i][j] = next[i - 1][next[i - 1][j]];
			cost[i][j] = cost[i - 1][j] + cost[i - 1][next[i - 1][j]];
		}
	}
}
INT Dis(INT u, INT v)
{
	INT ret = 0;
	if(depth[u] < depth[v]) std::swap(u, v);
	for(int i = maxD; ~i; i--)
	{
		if(depth[next[i][u]] < depth[v]) continue;
		ret += cost[i][u];
		u = next[i][u];
	}
	if(u != v)
	{
		for(int i = maxD; ~i; i--)
		{
			if(next[i][u] == next[i][v]) continue;
			ret += cost[i][u];
			ret += cost[i][v];
			u = next[i][u];
			v = next[i][v];
		}
		ret += weight[u];
		ret += weight[v];
		u = next[0][u];
	}
	ret += weight[u];
	return ret;
}

struct DS
{
	std::vector<INT> parent;

	void init(INT size)
	{
		parent.clear();
		parent.resize(size + 1);
		for(int i = 1; i <= n; i++) parent[i] = i;
	}

	INT find(INT x)
	{
		if(x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	void unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		parent[py] = px;
	}
} ds;

INT querys[maxn];
INT anss[maxn];

struct Block
{
	INT u;
	INT v;
	INT dis;
	Block() {}
	Block(INT u) : u(u), v(u), dis(weight[u]) {}
	Block(INT u, INT v) : u(u), v(v), dis(Dis(u, v)) {}
	bool operator< (const Block& b) const
	{
		return dis > b.dis;
	}
} blocks[maxn];

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
		cost[0][i] = weight[i] = readIn();
	for(int i = 1; i < n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		e[i] = E(from, to);
		addEdge(from, to);
		addEdge(to, from);
	}

	goDouble();
	for(int i = 1; i < n; i++)
		querys[i] = readIn();

	for(int i = 1; i <= n; i++)
		new(&blocks[i]) Block(i);

	anss[n] = 1;
	for(int i = 1; i <= n; i++)
	{
		anss[n] = anss[n] * blocks[i].dis % mod;
	}

	ds.init(n);
	for(int i = n - 1; i >= 1; i--)
	{
		INT u = ds.find(e[querys[i]].from);
		INT v = ds.find(e[querys[i]].to);
		Block temp[] =
		{
			Block(blocks[u].u, blocks[u].v),
			Block(blocks[u].u, blocks[v].u),
			Block(blocks[u].u, blocks[v].v),
			Block(blocks[u].v, blocks[v].u),
			Block(blocks[u].v, blocks[v].v),
			Block(blocks[v].u, blocks[v].v),
		};
		std::sort(temp, temp + 6);
		anss[i] = anss[i + 1] * Inv(blocks[u].dis) % mod * Inv(blocks[v].dis) % mod * temp[0].dis % mod;
		ds.unite(u, v);
		blocks[ds.find(u)] = temp[0];
	}

	for(int i = 1; i <= n; i++)
	{
		printOut(anss[i]);
	}
}

int main()
{
#ifndef JUDGE
	freopen("forest.in", "r", stdin);
	freopen("forest.out", "w", stdout);
#endif
	run();
	return 0;
}
