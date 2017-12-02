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
	bool minus = false;
	INT a = 0;
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

struct DS
{
	std::vector<INT> parent;

	DS(INT size) : parent(size + 1)
	{
		for (int i = 1; i <= size; i++)
		{
			parent[i] = i;
		}
	}

	INT find(INT x)
	{
		if (parent[x] == x) return x;
		return parent[x] = find(parent[x]);
	}
	INT unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		parent[py] = px;
	}
	INT judge(INT x, INT y)
	{
		return find(x) == find(y);
	}
};

const INT maxn = 10005;
INT n, m;
struct E
{
	INT from;
	INT to;
	INT cost;
	E(INT from = 0, INT to = 0, INT cost = 0) : from(from), to(to), cost(cost)
	{
	}

	bool operator< (const E& b) const
	{
		return cost > b.cost;
	}
} e[50005];
INT k;

struct edge
{
	INT to;
	INT cost;
	edge(INT to = 0, INT cost = 0) : to(to), cost(cost)
	{

	}
};
std::vector<std::vector<edge> > edges;

void kruskal(DS &ds)
{
	edges.resize(n + 1);
	INT count_ = 0;
	for (int i = 0; i < m; i++)
	{
		if (!ds.judge(e[i].from, e[i].to))
		{
			ds.unite(e[i].from, e[i].to);
			edges[e[i].from].push_back(edge(e[i].to, e[i].cost));
			edges[e[i].to].push_back(edge(e[i].from, e[i].cost));
		}
	}
}

std::vector<INT> sequence(1);
std::vector<INT> vis;
std::vector<INT> depth;
std::vector<std::vector<INT> > stTable(1);
std::vector<std::vector<INT> > parent(1);
std::vector<std::vector<INT> > minLen(1);
void dfs(INT node = 1)
{
	vis[node] = sequence.size();
	sequence.push_back(node);
	for (int i = 0; i < edges[node].size(); i++)
	{
		INT to = edges[node][i].to;
		if (to == parent[0][node]) continue;
		INT cost = edges[node][i].cost;

		depth[to] = depth[node] + 1;
		parent[0][to] = node;
		minLen[0][to] = cost;
		dfs(to);
		sequence.push_back(node);
	}
}
void ST()
{
	INT N = sequence.size() - 1;
	INT size = 0;
	while (1 << (size + 1) <= N) size++;

	stTable[0].resize(N + 1);
	for (int i = 1; i <= N; i++)
	{
		stTable[0][i] = sequence[i];
	}

	for (int i = 1; i <= size; i++)
	{
		stTable.push_back(std::vector<INT>());
		stTable.back().resize(N + 1);
		for (int j = 1; j + (1 << i) - 1 <= N; j++)
		{
			INT x = stTable[i - 1][j];
			INT y = stTable[i - 1][j + (1 << (i - 1))];
			if (depth[stTable[i - 1][j]] < depth[stTable[i - 1][j + (1 << (i - 1))]])
			{
				stTable[i][j] = stTable[i - 1][j];
			}
			else
			{
				stTable[i][j] = stTable[i - 1][j + (1 << (i - 1))];
			}
		}
	}

	N = n;
	size = 0;
	while (1 << (size + 1) <= N) size++;
	for (int i = 1; i <= size; i++)
	{
		parent.push_back(std::vector<INT>());
		minLen.push_back(std::vector<INT>());
		parent.back().resize(N + 1);
		minLen.back().resize(N + 1);
		for (int j = 1; j <= N; j++)
		{
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
			if (parent[i][j]) minLen[i][j] = std::min(minLen[i - 1][j], minLen[i - 1][parent[i - 1][j]]);
		}
	}
}
INT getMin(int& x, int& y)
{
	INT l = vis[x];
	INT r = vis[y];
	if (l > r)
	{
		std::swap(l, r);
		std::swap(x, y);
	}
	INT length = r - l + 1;
	INT size = 0;
	while (1 << (size + 1) <= length) size++;

	if (depth[stTable[size][l]] < depth[stTable[size][r - (1 << size) + 1]])
		return stTable[size][l];
	else
		return stTable[size][r - (1 << size) + 1];
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 0; i < m; i++)
	{
		e[i].from = readIn();
		e[i].to = readIn();
		e[i].cost = readIn();
	}
	std::sort(e, e + m);
	DS ds(n);
	kruskal(ds);
	vis.resize(n + 1);
	depth.resize(n + 1);
	parent[0].resize(n + 1);
	minLen[0].resize(n + 1);

	for (int i = 1; i <= n; i++)
	{
		if (!vis[i]) dfs(i);
	}

	ST();

	k = readIn();
	while (k--)
	{
		INT from = readIn();
		INT to = readIn();
		if (ds.judge(from, to))
		{
			INT anc = getMin(from, to);
			INT depthFrom = depth[from];
			INT depthTo = depth[to];
			INT depthAnc = depth[anc];
			INT stepFrom = depthFrom - depthAnc;
			INT stepTo = depthTo - depthAnc;

			INT minVal = 0x7ffffff;

			for (int i = parent.size() - 1; ~i; i--)
			{
				if (stepFrom & (1 << i))
				{
					minVal = std::min(minVal, minLen[i][from]);
					from = parent[i][from];
				}
			}
			for (int i = parent.size() - 1; ~i; i--)
			{
				if (stepTo & (1 << i))
				{
					minVal = std::min(minVal, minLen[i][to]);
					to = parent[i][to];
				}
			}
			printf("%d\n", minVal);
		}
		else
		{
			printf("-1\n");
		}
	}
}

int main()
{
	run();
	return 0;
}