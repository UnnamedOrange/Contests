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

const INT maxn = 1e5 + 5;
const INT maxm = 2 * maxn;
INT n, m;
INT weight[maxn];
struct Edge
{
	INT to;
	INT cost;
	INT next;
} edges[maxm];
INT head[maxn];
void addEdge(INT from, INT to, INT cost, INT Index)
{
	edges[Index].to = to;
	edges[Index].cost = cost;
	edges[Index].next = head[from];
	head[from] = Index;
}

INT size;
INT depth[maxn];
INT next[18][maxn];
INT sumCost[18][maxn];
void dfs(INT node = 1)
{
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (to == next[0][node]) continue;
		INT cost = edges[i].cost;
		depth[to] = depth[node] + 1;
		next[0][to] = node;
		sumCost[0][to] = cost;
		dfs(to);
	}
}
void goDouble()
{
	memset(depth, 0, sizeof(depth));
	memset(next, 0, sizeof(next));
	memset(sumCost, 0, sizeof(sumCost));
	depth[1] = 1;
	dfs();
	size = 0;
	while (1 << size < n) size++;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			next[i][j] = next[i - 1][next[i - 1][j]];
			sumCost[i][j] = sumCost[i - 1][j] + sumCost[i - 1][next[i - 1][j]];
		}
	}
}
INT query(INT x, INT y)
{
	if (depth[x] < depth[y]) std::swap(x, y);
	INT Sum = 0;
	for (int i = size; ~i; i--)
	{
		if (depth[next[i][x]] < depth[y]) continue;
		Sum += sumCost[i][x];
		x = next[i][x];
	}
	if (x != y)
	{
		for (int i = size; ~i; i--)
		{
			if (next[i][x] == next[i][y]) continue;
			Sum += sumCost[i][x] + sumCost[i][y];
			x = next[i][x];
			y = next[i][y];
		}
		Sum += sumCost[0][x] + sumCost[0][y];
	}
	return Sum;
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
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	void unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		parent[py] = px;
	}
};
struct Edge2
{
	INT minVal;
	INT v1;
	INT v2;

	bool operator< (const Edge2& b) const
	{
		return minVal > b.minVal;
	}
} edges2[maxn];
struct Block
{
	INT v1;
	INT v2;
	Block() {}
	Block(INT v1, INT v2) : v1(v1), v2(v2) {}

	bool operator< (const Block& b) const
	{
		return query(v1, v2) < query(b.v1, b.v2);
	}
	INT operator() () const
	{
		return query(v1, v2);
	}
} blocks[maxn];
void unite()
{
	DS ds(n);
	INT ans = 0;
	for (int i = 1; i <= n; i++)
	{
		blocks[i].v1 = blocks[i].v2 = i;
	}
	for (int i = 1; i <= m; i++)
	{
		INT v1 = ds.find(edges2[i].v1);
		INT v2 = ds.find(edges2[i].v2);
		Block temp = std::max(blocks[v1], blocks[v2]);
		temp = std::max(temp, Block(blocks[v1].v1, blocks[v2].v1));
		temp = std::max(temp, Block(blocks[v1].v1, blocks[v2].v2));
		temp = std::max(temp, Block(blocks[v1].v2, blocks[v2].v1));
		temp = std::max(temp, Block(blocks[v1].v2, blocks[v2].v2));
		ans = std::max(ans, temp() * edges2[i].minVal);

		ds.unite(v1, v2);
		blocks[v1] = temp;
	}
	cout << ans << endl;
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = n - 1;
		memset(head, 0, sizeof(INT) * (n + 1));
		for (int i = 1; i <= n; i++)
		{
			weight[i] = readIn();
		}
		for (int i = 1; i <= m; i++)
		{
			INT from = readIn();
			INT to = readIn();
			INT cost = readIn();
			addEdge(from, to, cost, (i << 1) - 1);
			addEdge(to, from, cost, i << 1);
			edges2[i].v1 = from;
			edges2[i].v2 = to;
			edges2[i].minVal = std::min(weight[from], weight[to]);
		}
		std::sort(edges2 + 1, edges2 + 1 + m);
		goDouble();
		unite();
	}
}

int main()
{
	run();
	return 0;
}