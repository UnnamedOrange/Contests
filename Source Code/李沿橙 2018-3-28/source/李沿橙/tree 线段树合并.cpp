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
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = int(1e5) + 5;
int n;
int parent[maxn];
int val[maxn];
int bound;
int disc[maxn];
void discretize()
{
	memcpy(disc, val, sizeof(disc));
	std::sort(disc + 1, disc + 1 + n);
	bound = std::unique(disc + 1, disc + 1 + n) - (disc + 1);
	for (int i = 1; i <= n; i++)
		val[i] = std::lower_bound(disc + 1, disc + 1 + bound, val[i]) - disc;
}
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn];
	int i;
	int head[maxn];
	Graph() : i() { memset(head, -1, sizeof(head)); }
	void addEdge(int from, int to)
	{
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(G) idx_##G
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to
} G;

class SegTree
{
	struct Node
	{
		int sum;
		int max;
		Node *lc, *rc;
		Node() : sum(), max() {}
	};
	static Node* null;
	static struct Initializer
	{
		void operator()()
		{
			static bool initialized;
			if (!initialized)
			{
				initialized = true;
				null = new Node;
				null->lc = null->rc = null;
			}
		}
		Initializer() { (*this)(); }
	} initializer;
	static int g_L, g_R, g_Pos;
	static void alloc(Node* &node)
	{
		if (node == null)
		{
			node = new Node;
			node->lc = node->rc = null;
		}
	}
	void insert(Node* &node, int l = 1, int r = bound)
	{
		alloc(node);
		if (l == r)
		{
			node->sum++;
			node->max = l;
			return;
		}
		int mid = (l + r) >> 1;
		if (g_Pos <= mid) insert(node->lc, l, mid);
		if (g_Pos > mid) insert(node->rc, mid + 1, r);
		node->sum = node->lc->sum + node->rc->sum;
		node->max = std::max(node->lc->max, node->rc->max);
	}
	void erase(Node* &node, int l = 1, int r = bound)
	{
		if (node == null) return;
		if (l == r)
		{
			node->sum--;
			if (!node->sum)
			{
				delete node;
				node = null;
			}
			return;
		}
		int mid = (l + r) >> 1;
		if (g_Pos <= mid) erase(node->lc, l, mid);
		if (g_Pos > mid) erase(node->rc, mid + 1, r);
		node->sum = node->lc->sum + node->rc->sum;
		node->max = std::max(node->lc->max, node->rc->max);
		if (node->lc == null && node->rc == null)
		{
			delete node;
			node = null;
		}
	}
	int find(Node* &node, int l = 1, int r = bound)
	{
		if (node == null) return 0;
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (g_Pos <= mid && node->lc != null && node->lc->max >= g_Pos) return find(node->lc, l, mid);
		else return find(node->rc, mid + 1, r);
	}
	static void merge(Node* &des, Node* &src)
	{
		if (src == null) return;
		if (des == null)
		{
			des = src;
			src = null;
			return;
		}
		merge(des->lc, src->lc);
		merge(des->rc, src->rc);
		des->sum += src->sum;
		des->max = std::max(des->max, src->max);
		delete src;
		src = null;
	}
	Node* root;

public:
	SegTree()
	{
		initializer();
		root = null;
	}
	void insert(int pos)
	{
		g_Pos = pos;
		insert(root);
	}
	void erase(int pos)
	{
		g_Pos = pos;
		erase(root);
	}
	int find(int pos)
	{
		g_Pos = pos;
		return find(root);
	}
	int statistic() const
	{
		return root->sum;
	}
	static void merge(SegTree& des, SegTree& src)
	{
		merge(des.root, src.root);
	}
};
SegTree::Node* SegTree::null;
SegTree::Initializer SegTree::initializer;
int SegTree::g_L, SegTree::g_R, SegTree::g_Pos;

int BFS()
{
	static int q[maxn];
	static SegTree st[maxn];
	int head = 0, tail = 0;
	q[tail++] = 1;
	while (head != tail)
	{
		int from = q[head];
		head++;
		wander(G, from)
		{
			DEF(G);
			q[tail++] = to;
		}
	}
	for (int i = tail - 1; i; i--)
	{
		int node = q[i];
		if (int pos = st[node].find(val[node]))
			st[node].erase(pos);
		st[node].insert(val[node]);
		if (node != 1) SegTree::merge(st[parent[node]], st[node]);
	}
	return st[1].statistic();
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		val[i] = readIn();
		parent[i] = readIn();
	}
	for (int i = 2; i <= n; i++)
		G.addEdge(parent[i], i);
	discretize();

	printOut(BFS());
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