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
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
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

const int maxn = int(1e5) + 5;
const int maxm = int(1.5e5) + 5;
struct Graph
{
	struct Edge
	{
		int to;
		int next;
		bool unavailable;
		bool isSquare;
	} edges[maxm * 4];
	int i;
	int head[maxn * 2];
	Graph() : i() { memset(head, -1, sizeof(head)); }
	void addEdge(int from, int to, bool isSquare)
	{
		edges[i].to = to;
		edges[i].next = head[from];
		edges[i].unavailable = false;
		edges[i].isSquare = isSquare;
		head[from] = i;
		i++;
	}
#define idx(x) idx_##x
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next) if (!G.edges[idx(G)].unavailable && !G.edges[idx(G) ^ 1].unavailable)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to
} G;

int n, m;
int a[maxn];
int bound;
int disc[maxn];
void discretize()
{
	memcpy(disc, a, sizeof(int) * (n + 1));
	std::sort(disc + 1, disc + 1 + n);
	bound = std::unique(disc + 1, disc + 1 + n) - (disc + 1);
	for (int i = 1; i <= n; i++)
		a[i] = std::lower_bound(disc + 1, disc + 1 + bound, a[i]) - disc;
}
int locate(int x)
{
	return std::upper_bound(disc + 1, disc + 1 + bound, x) - disc - 1;
}
int q;
struct Query
{
	int ty;
	int pos, limit;
	int ans;
	void read()
	{
		ty = readIn();
		pos = readIn();
		limit = readIn();
	}
} querys[maxn];
std::vector<int> offline[maxn * 2];

class SegTree
{
	struct Node
	{
		int odd;
		int even;
		Node *lc, *rc;
		Node() : odd(), even() {}
	};
	static int g_L, g_R, g_Pos, g_Val;
	static Node* null;
	static struct Initializer
	{
		Initializer()
		{
			null = new Node;
			null->lc = null->rc = null;
		}
	} initializer;

	static void alloc(Node* &r)
	{
		if (r == null)
		{
			r = new Node;
			r->lc = r->rc = null;
		}
	}
	Node* root;
	void add(Node* &node, int l, int r)
	{
		alloc(node);
		if (l == r)
		{
			if (node->odd)
			{
				node->odd = 0;
				node->even = 1;
			}
			else
			{
				node->odd = 1;
				node->even = 0;
			}
			return;
		}
		int mid = (l + r) >> 1;
		if (g_Pos <= mid) add(node->lc, l, mid);
		if (g_Pos > mid) add(node->rc, mid + 1, r);
		node->odd = node->lc->odd + node->rc->odd;
		node->even = node->lc->even + node->rc->even;
	}
	int query(Node* node, int l, int r)
	{
		if (node == null) return 0;
		if (g_L <= l && r <= g_R)
		{
			return g_Val ? node->odd : node->even; // g_Val = true -> odd
		}
		int mid = (l + r) >> 1;
		int ret = 0;
		if (g_L <= mid) ret += query(node->lc, l, mid);
		if (g_R > mid) ret += query(node->rc, mid + 1, r);
		return ret;
	}
	static void merge(Node*& des, Node* &src, int l, int r)
	{
		if (src == null) return;
		if (des == null)
		{
			des = src;
			src = null;
			return;
		}
		if (l == r)
		{
			int val = (des->odd + src->odd) & 1;
			if (val)
			{
				des->odd = 1;
				des->even = 0;
			}
			else
			{
				des->odd = 0;
				des->even = 1;
			}
		}
		else
		{
			int mid = (l + r) >> 1;
			merge(des->lc, src->lc, l, mid);
			merge(des->rc, src->rc, mid + 1, r);
			des->odd = des->lc->odd + des->rc->odd;
			des->even = des->lc->even + des->rc->even;
		}
		delete src;
		src = null;
	}

public:
	SegTree()
	{
		root = null;
	}
	void add(int pos)
	{
		g_Pos = pos;
		add(root, 1, bound);
	}
	int queryOdd(int l, int r)
	{
		if (!r) return 0;
		g_L = l;
		g_R = r;
		g_Val = 1;
		return query(root, 1, bound);
	}
	int queryEven(int l, int r)
	{
		if (!r) return 0;
		g_L = l;
		g_R = r;
		g_Val = 0;
		return query(root, 1, bound);
	}
	static void merge(SegTree& des, SegTree& src)
	{
		merge(des.root, src.root, 1, bound);
	}
};
SegTree::Initializer SegTree::initializer;
SegTree::Node* SegTree::null;
int SegTree::g_L, SegTree::g_R, SegTree::g_Pos, SegTree::g_Val;

#define RunInstance(x) delete new x
struct cheat
{
	bool vis[maxn];
	int c[maxn];
	int head, tail;
	int parent[maxn];
	SegTree st[maxn];
	cheat() : vis(), head(), tail()
	{
		c[tail++] = 1;
		vis[1] = true;
		while (head != tail)
		{
			int from = c[head];
			head++;
			wander(G, from)
			{
				DEF(G);
				if (vis[to]) continue;
				c[tail++] = to;
				vis[to] = true;
				parent[to] = from;
			}
		}
		parent[1] = 0;
		for (int i = tail - 1; ~i; i--)
		{
			int node = c[i];
			st[node].add(a[node]);
			for (int j = 0; j < offline[node].size(); j++)
			{
				Query& Q = querys[offline[node][j]];
				if (Q.ty == 1) // odd
				{
					Q.ans = st[node].queryOdd(1, locate(Q.limit));
				}
				else if (Q.ty == 0)
				{
					Q.ans = st[node].queryEven(1, locate(Q.limit));
				}
			}
			if (i) SegTree::merge(st[parent[node]], st[node]);
		}
		for (int i = 1; i <= q; i++)
		{
			printOut(querys[i].ans);
		}
	}
};
struct work
{
	SegTree st[maxn * 2];
	int isSquare[maxn * 2]; // square vertex

	int stackv[maxn * 2]; // vertex
	int stacke[maxm * 2]; // edge
	bool vise[maxm * 2]; // edge in original graph
	bool vis[maxn * 2];
	void Tarjan(int node)
	{
		if (vis[node]) // build square vertex
		{
			isSquare[++n] = true;
			for (int i = stackv[0], j = stacke[0]; i && j; i--, j--)
			{
				int v = stackv[i];
				int e = stacke[j];
				G.edges[e].unavailable = G.edges[e ^ 1].unavailable = true;
				G.addEdge(v, n, true);
				G.addEdge(n, v, true);
				if (node == v) break;
			}
			return;
		}
		vis[node] = true;
		stackv[++stackv[0]] = node;
		wander(G, node) if (!G.edges[idx(G)].isSquare && !vise[idx(G)])
		{
			DEF(G);
			vise[idx(G)] = vise[idx(G) ^ 1] = true;
			stacke[++stacke[0]] = idx(G);
			Tarjan(to);
			stacke[0]--;
		}
		stackv[0]--;
	}

	void DFS(int node)
	{
		vis[node] = true;
		if (!isSquare[node]) st[node].add(a[node]);
		wander(G, node)
		{
			DEF(G);
			if (vis[to]) continue;
			DFS(to);
			SegTree::merge(st[node], st[to]);
		}
		for (int j = 0; j < offline[node].size(); j++)
		{
			Query& Q = querys[offline[node][j]];
			if (Q.ty == 1) // odd
			{
				Q.ans = st[node].queryOdd(1, locate(Q.limit));
			}
			else if (Q.ty == 0)
			{
				Q.ans = st[node].queryEven(1, locate(Q.limit));
			}
		}
	}

	work() : isSquare(), vis(), vise()
	{
		stackv[0] = stacke[0] = 0;
		Tarjan(1);
		std::memset(vis, 0, sizeof(vis));
		DFS(1);
		for (int i = 1; i <= q; i++)
			printOut(querys[i].ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	discretize();
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		G.addEdge(from, to, false);
		G.addEdge(to, from, false);
	}
	q = readIn();
	for (int i = 1; i <= q; i++)
	{
		querys[i].read();
		offline[querys[i].pos].push_back(i);
	}

	if (m + 1 == n)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("map.in", "r", stdin);
	freopen("map.out", "w", stdout);
#endif
	run();
	return 0;
}