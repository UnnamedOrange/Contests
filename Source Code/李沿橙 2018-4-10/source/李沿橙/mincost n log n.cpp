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
#define loop register int
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

const int INF = (~(int(1) << (sizeof(int) * 8 - 1)));
const int maxn = 300005;
const int maxm = 500005;
int n, m, K;
int a[maxn], b[maxn];
int idxa[maxn];
int idxb[maxn];
bool comp1(const int& x, const int& y) { return a[x] < a[y]; }
bool comp2(const int& x, const int& y) { return b[x] < b[y]; }

struct Graph
{
	struct Edge
	{
		int from;
		int to;
		int next;
	} edges[maxm * 2];
	int i;
	int head[maxn];
	Graph() : i()
	{
		memset(head, -1, sizeof(head));
	}
	void addEdge(int from, int to)
	{
		edges[i].from = from;
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(G) idx_##G
#define wander(G, node) for (loop idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int from = e.from; int to = e.to; int cost = std::max(b[from], b[to])
} G;

struct LCT
{
	struct Node
	{
		int weight;
		int size;

		int val, maxVal;
		int idx, maxIdx;

		void maintain()
		{
			size = weight + ch[0]->size + ch[1]->size;
			maxVal = val;
			maxIdx = idx;
			if (ch[0]->maxVal > maxVal)
			{
				maxVal = ch[0]->maxVal;
				maxIdx = ch[0]->maxIdx;
			}
			if (ch[1]->maxVal > maxVal)
			{
				maxVal = ch[1]->maxVal;
				maxIdx = ch[1]->maxIdx;
			}
		}

		bool flag;
		Node* parent;
		Node* ch[2];
		Node() : flag() {}
		void reverse()
		{
			flag ^= 1;
		}
		void pushdown()
		{
			if (flag)
			{
				std::swap(ch[0], ch[1]);
				ch[0]->flag ^= 1;
				ch[1]->flag ^= 1;
				flag = false;
			}
		};
	};
	Node* null;
	Node nodes[maxn + maxm];

	bool isRoot(Node* r)
	{
		return r->parent->ch[0] != r && r->parent->ch[1] != r;
	}
	int trace(Node* r)
	{
		return r->parent->ch[1] == r;
	}
	void rotate(Node* r)
	{
		Node* parent = r->parent;
		Node* grand = parent->parent;
		int d = trace(r);
		if (!isRoot(parent)) grand->ch[trace(parent)] = r;
		r->parent = grand;

		parent->ch[d] = r->ch[d ^ 1];
		r->ch[d ^ 1]->parent = parent;
		parent->maintain();

		r->ch[d ^ 1] = parent;
		parent->parent = r;
		r->maintain();
	}
	void pushdown(Node* r)
	{
		if (isRoot(r)) return void(r->pushdown());
		pushdown(r->parent);
		r->pushdown();
	}
	void splay(Node* r)
	{
		pushdown(r);
		while (!isRoot(r))
		{
			Node* parent = r->parent;
			if (!isRoot(parent)) rotate(trace(parent) == trace(r) ? parent : r);
			rotate(r);
		}
	}

public:
	LCT()
	{
		null = nodes;
		null->ch[0] = null->ch[1] = null->parent = null;
		null->weight = null->size = null->val =
			null->maxVal = null->idx = 0;
		null->maxIdx = -1;
	}
	void init()
	{
		for (int i = 1; i <= n; i++)
		{
			Node* r = nodes + i;
			r->ch[0] = r->ch[1] = r->parent = null;
			r->weight = 1;
			r->val = r->idx = 0;
			r->maintain();
		}
		for (int i = 1, j = n + 1; i <= m; i++, j++)
		{
			Node* r = nodes + j;
			r->ch[0] = r->ch[1] = r->parent = null;
			r->weight = 0;
			int idx(G) = (i - 1) << 1; // 除以二后加一
			DEF(G);
			r->idx = idx(G) >> 1; // 保存的除以二
			r->val = cost;
			r->maintain();
		}
	}
	void access(int code)
	{
		Node* node = nodes + code;
		Node* pre = null;
		while (node != null)
		{
			splay(node);

			node->weight += node->ch[1]->size;
			node->ch[1] = pre;
			node->weight -= node->ch[1]->size;
			node->maintain();

			pre = node;
			node = node->parent;
		}
	}
	void makeroot(int code)
	{
		Node* r = nodes + code;
		access(code);
		splay(r);
		r->reverse();
	}
	int findroot(int code)
	{
		access(code);
		Node* node = nodes + code;
		splay(node);
		while (node->ch[0] != null) node = node->ch[0];
		return splay(node), node - nodes;
	}
	void link(int x, int y)
	{
		makeroot(x);
		//if (findroot(y) == x) return;
		Node* X = nodes + x;
		Node* Y = nodes + y;
		makeroot(y);

		Y->weight += X->size;
		X->parent = Y;
		Y->maintain();
	}
	bool judge(int x, int y)
	{
		makeroot(x);
		access(y);
		Node* X = nodes + x;
		Node* Y = nodes + y;
		splay(Y);
		if (Y->ch[0] != X || X->ch[1] != null) return false;
		return true;
	}
	void cut(int x, int y)
	{
		makeroot(x);
		access(y);
		Node* X = nodes + x;
		Node* Y = nodes + y;
		splay(Y);
		X->parent = Y->ch[0] = null;
		Y->maintain();
	}
	void splay(int code) { splay(nodes + code); }
	Node* operator[](int code) { return nodes + code; }
} lct;

bool visa[maxn];
bool visb[maxn];

void run()
{
	int ans = INF;
	n = readIn();
	m = readIn();
	K = readIn();
	for (loop i = 1; i <= n; i++)
	{
		a[i] = readIn();
		b[i] = readIn();
	}
	if (K == 1)
	{
		for (int i = 1; i <= n; i++)
			ans = std::min(ans, a[i] + b[i]);
		printOut(ans);
		return;
	}
	for (loop i = 1; i <= n; i++)
	{
		idxa[i] = i;
		idxb[i] = i;
	}
	std::sort(idxa + 1, idxa + 1 + n, comp1);
	std::sort(idxb + 1, idxb + 1 + n, comp2);
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
	}

	lct.init();

	std::multiset<int> set;
	for (int i = 1; i <= n; i++) set.insert(1);
	int R = n;
	for (int L = 1; L <= n; L++)
	{
		int node = idxa[L];
		visa[node] = true;
		if (visb[node]) continue;
		wander(G, node)
		{
			DEF(G);
			if (!visa[to] || visb[to]) continue;
			lct.makeroot(from);
			if (lct.findroot(from) == lct.findroot(to))
			{
				lct.makeroot(from);
				lct.access(to);
				lct.splay(from);
				if (cost >= lct[from]->maxVal) continue;
				int idx = lct[from]->maxIdx;
				lct.cut(G.edges[idx << 1].from, idx + n + 1);
				lct.cut(G.edges[idx << 1].to, idx + n + 1);
				lct.link((idx(G) >> 1) + n + 1, from);
				lct.link((idx(G) >> 1) + n + 1, to);
			}
			else
			{
				lct.makeroot(from);
				set.erase(set.find(lct[from]->size));
				lct.makeroot(to);
				set.erase(set.find(lct[to]->size));
				lct.link((idx(G) >> 1) + n + 1, from);
				lct.link((idx(G) >> 1) + n + 1, to);
				lct.makeroot(to);
				set.insert(lct[to]->size);
			}
		}

		while (R && *set.rbegin() >= K)
		{
			node = idxb[R];
			visb[node] = true;
			ans = std::min(ans, a[idxa[L]] + b[idxb[R]]);
			wander(G, node)
			{
				DEF(G);
				if (!lct.judge(from, (idx(G) >> 1) + n + 1)) continue;
				lct.makeroot(from);
				set.erase(set.find(lct[from]->size));
				lct.cut(from, (idx(G) >> 1) + n + 1);
				lct.cut(to, (idx(G) >> 1) + n + 1);
				lct.makeroot(from);
				set.insert(lct[from]->size);
				lct.makeroot(to);
				set.insert(lct[to]->size);
			}
			R--;
		}
	}
	if (ans >= INF) puts("no solution");
	else printOut(ans);
}

int main()
{
#ifndef LOCAL
	freopen("mincost.in", "r", stdin);
	freopen("mincost.out", "w", stdout);
#endif
	run();
	return 0;
}