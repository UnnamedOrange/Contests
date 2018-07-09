#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef LL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(2e5) + 5;
LL lastans;
int n, m, type;
struct Edge
{
	int from;
	int to;
	LL cost;
	Edge() {}
	Edge(int from, int to, LL cost) : from(from), to(to), cost(cost) {}
};
std::vector<Edge> edges;
std::vector<std::vector<int> > G;
void addEdge(int from, int to, LL cost)
{
	edges.push_back(Edge(from, to, cost));
	edges.push_back(Edge(to, from, cost));
	int i = edges.size();
	G[from].push_back(i - 2);
	G[to].push_back(i - 1);
}

#define RunInstance(x) delete new x
struct brute
{
	LL depth[maxn];
	void DFS(int node, int parent)
	{
		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = edges[G[node][i]];
			if (e.to == parent) continue;
			depth[e.to] = depth[node] + e.cost;
			DFS(e.to, node);
		}
	}
	brute()
	{
		while (m--)
		{
			char ins[10];
			scanf("%s", ins);
			if (ins[0] == 'm')
			{
				LL x = readIn();
				LL y = readIn();
				if (type)
				{
					x ^= lastans;
					y ^= lastans;
				}
				edges[((x - 1) << 1)].cost = y;
				edges[((x - 1) << 1) | 1].cost = y;
			}
			else if (ins[0] == 'q')
			{
				LL l = readIn();
				LL r = readIn();
				LL x = readIn();
				if (type)
				{
					l ^= lastans;
					r ^= lastans;
					x ^= lastans;
				}
				depth[x] = 0;
				DFS(x, 0);
				lastans = 0;
				for (int i = l; i <= r; i++)
					lastans += depth[i];
				printOut(lastans);
			}
		}
	}
};
class FuncSegTree
{
	struct Node
	{
		int sum;
		int lc, rc;
		Node() : sum(), lc(), rc() {}
	};
	std::vector<Node> nodes;
	std::vector<int> versions;

	int g_L, g_R, g_Pos, g_Val;
	int query_(int node, int l, int r)
	{
		Node& t = nodes[node];
		if (g_L <= l && r <= g_R)
		{
			return nodes[node].sum;
		}
		int mid = (l + r) >> 1;
		int ret = 0;
		if (g_L <= mid) ret += query_(t.lc, l, mid);
		if (g_R > mid) ret += query_(t.rc, mid + 1, r);
		return ret;
	}
	void add_(int& node, int l, int r, int src)
	{
		if (!(l <= g_Pos && g_Pos <= r))
		{
			node = src;
			return;
		}
		node = nodes.size();
		nodes.push_back(nodes[src]);
		Node& t = nodes[node];
		if (l == r)
		{
			t.sum += g_Val;
			return;
		}
		int mid = (l + r) >> 1;
		add_(t.lc, l, mid, nodes[src].lc);
		add_(t.rc, mid + 1, r, nodes[src].rc);
		t.sum = nodes[t.lc].sum + nodes[t.rc].sum;
	}

public:
	FuncSegTree()
	{
		nodes.reserve(maxn * 20);
		nodes.push_back(Node());
		versions.push_back(0);
	}
	void clone()
	{
		versions.push_back(versions.back());
	}
	int query(int l, int r, int verl, int verr)
	{
		g_L = l;
		g_R = r;
		return query_(versions[verr], 1, n) - query_(versions[verl], 1, n);
	}
	void add(int pos, int val)
	{
		g_Pos = pos;
		g_Val = val;
		add_(versions.back(), 1, n, versions.back());
	}
};
struct cheat
{
	static const int maxN = 40005;
	int size[maxN];
	bool vis[maxN];
	void DFS1(int node, int parent)
	{
		size[node] = 1;
		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = edges[G[node][i]];
			if (e.to == parent || vis[e.to]) continue;
			DFS1(e.to, node);
			size[node] += size[e.to];
		}
	}
	int findRoot(int node, int parent, int s)
	{
		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = edges[G[node][i]];
			if (e.to == parent || vis[e.to]) continue;
			if (size[e.to] >(s >> 1))
				return findRoot(e.to, node, s);
		}
		return node;
	}
	int root;
	std::vector<std::vector<int> > DG;
	int solve(int node, int d)
	{
		DFS1(node, 0);
		node = findRoot(node, 0, size[node]);
		vis[node] = true;

		DFS2(node, 0, d, node, 0);

		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = edges[G[node][i]];
			if (vis[e.to]) continue;
			DG[node].push_back(solve(e.to, d + 1));
		}
		return node;
	}

	LL depth[19][maxN];
	std::vector<int> centerNodes[19][maxN];
	std::vector<int> belongNodes[19][maxN];
	std::vector<LL> centerDepth[19][maxN];
	std::vector<LL> belongDepth[19][maxN];
	int center[19][maxN];
	int belong[19][maxN];
	void DFS2(int node, int parent, int d, int c, int b)
	{
		center[d][node] = c;
		belong[d][node] = b;
		centerNodes[d][c].push_back(node);
		if (b) belongNodes[d][b].push_back(node);
		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = edges[G[node][i]];
			if (e.to == parent || vis[e.to]) continue;
			DFS2(e.to, node, d, c, b ? b : e.to);
		}
		if (node == c)
			std::sort(centerNodes[d][c].begin(), centerNodes[d][c].end());
		if (node == b)
			std::sort(belongNodes[d][b].begin(), belongNodes[d][b].end());
	}

	struct Todo
	{
		int x;
		LL delta;
		Todo() {}
		Todo(int x, LL delta) : x(x), delta(delta) {}
	};
	std::vector<Todo> todo;
	int threshold;

	void DFS3(int node, int parent, int d)
	{
		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = edges[G[node][i]];
			if (e.to == parent || vis[e.to]) continue;
			depth[d][e.to] = depth[d][node] + e.cost;
			DFS3(e.to, node, d);
		}
	}
	void DFSDG(int node, int d)
	{
		vis[node] = true;
		depth[d][node] = 0;
		DFS3(node, 0, d);

		for (int i = 0; i < DG[node].size(); i++)
			DFSDG(DG[node][i], d + 1);
	}

	void rebuild()
	{
		todo.clear();
		std::memset(vis, 0, sizeof(vis[0]) * (n + 1));
		DFSDG(root, 0);
		for (int i = 0, sum = 1; sum <= n; i++, sum <<= 1)
		{
			for (int j = 1; j <= n; j++)
			{
				std::vector<int>& cn = centerNodes[i][j];
				std::vector<LL>& cd = centerDepth[i][j];
				cd.resize(cn.size());
				for (int k = 0; k < cn.size(); k++)
					cd[k] = depth[i][cn[k]] + (k ? cd[k - 1] : 0);

				std::vector<int>& bn = belongNodes[i][j];
				std::vector<LL>& bd = belongDepth[i][j];
				bd.resize(bn.size());
				for (int k = 0; k < bn.size(); k++)
					bd[k] = depth[i][bn[k]] + (k ? bd[k - 1] : 0);
			}
		}
	}

	std::pair<LL, int> queryCenter(int L, int R, int d, int c)
	{
		int l = std::lower_bound(centerNodes[d][c].begin(),
			centerNodes[d][c].end(), L) - centerNodes[d][c].begin();
		int r = std::upper_bound(centerNodes[d][c].begin(),
			centerNodes[d][c].end(), R) - centerNodes[d][c].begin() - 1;
		if (l > r) return std::make_pair(0ll, 0);
		return std::make_pair(centerDepth[d][c][r] - (l ? centerDepth[d][c][l - 1] : 0),
			r - l + 1);
	}
	std::pair<LL, int> queryBelong(int L, int R, int d, int c)
	{
		int l = std::lower_bound(belongNodes[d][c].begin(),
			belongNodes[d][c].end(), L) - belongNodes[d][c].begin();
		int r = std::upper_bound(belongNodes[d][c].begin(),
			belongNodes[d][c].end(), R) - belongNodes[d][c].begin() - 1;
		if (l > r) return std::make_pair(0ll, 0);
		return std::make_pair(belongDepth[d][c][r] - (l ? belongDepth[d][c][l - 1] : 0),
			r - l + 1);
	}

	LL query(int L, int R, int x)
	{
		LL ret = 0;
		for (int i = 0; ; i++)
		{
			if (center[i][x] == x)
			{
				ret += queryCenter(L, R, i, x).first;
				break;
			}
			std::pair<LL, int> infoCenter = queryCenter(L, R, i, center[i][x]);
			std::pair<LL, int> infoBelong = queryBelong(L, R, i, belong[i][x]);
			ret += infoCenter.first - infoBelong.first +
				(LL)depth[i][x] * (infoCenter.second - infoBelong.second);
		}
		for (int i = 0; i < todo.size(); i++)
		{
			const Todo& t = todo[i];
			const Edge& e = edges[(t.x - 1) << 1];
			int u = e.from;
			int v = e.to;
			if (Depth[u] < Depth[v])
				std::swap(u, v);
			int count = fst.query(dfn[u], end[u], L - 1, R); // l, r, verl, verr
			if (dfn[u] <= dfn[x] && dfn[x] <= end[u])
				ret += (LL)t.delta * (R - L + 1 - count);
			else
				ret += (LL)t.delta * count;
		}
		return ret;
	}

	int stamp;
	int dfn[maxN];
	int end[maxN];
	int Depth[maxN];
	void DFS(int node, int parent)
	{
		++stamp;
		dfn[node] = stamp;
		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = edges[G[node][i]];
			if (e.to == parent) continue;
			Depth[e.to] = Depth[node] + 1;
			DFS(e.to, node);
		}
		end[node] = stamp;
	}

	FuncSegTree fst;

	cheat() : vis(), stamp()
	{
		threshold = 500;
		Depth[1] = 1;
		DFS(1, 0);
		for (int i = 1; i <= n; i++)
		{
			fst.clone();
			fst.add(dfn[i], 1);
		}
		DG.resize(n + 1);
		root = solve(1, 0);
		rebuild();

		while (m--)
		{
			char ins[10];
			scanf("%s", ins);
			if (ins[0] == 'm')
			{
				LL x = readIn();
				LL y = readIn();
				if (type)
				{
					x ^= lastans;
					y ^= lastans;
				}
				todo.push_back(Todo(x, y - edges[((x - 1) << 1)].cost));
				edges[((x - 1) << 1)].cost = y;
				edges[((x - 1) << 1) | 1].cost = y;

				if (todo.size() >= threshold)
					rebuild();
			}
			else if (ins[0] == 'q')
			{
				LL l = readIn();
				LL r = readIn();
				LL x = readIn();
				if (type)
				{
					l ^= lastans;
					r ^= lastans;
					x ^= lastans;
				}
				printOut(lastans = query(l, r, x));
			}
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	type = readIn();
	G.resize(n + 1);
	for (int i = 2; i <= n; i++)
	{
		int from = readIn();
		int to = readIn();
		LL cost = readIn();
		addEdge(from, to, cost);
	}

	RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	run();
	return 0;
}