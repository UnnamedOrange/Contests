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
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int n;
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn * 2];
	int head[maxn];
	int i;
	Graph() : i(), maxHead()
	{
		memset(head, -1, sizeof(head));
	}
	int maxHead;
	void addEdge(int from, int to)
	{
		maxHead = std::max(maxHead, from);
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
	void clear()
	{
		i = 0;
		memset(head, -1, sizeof(int) * (maxHead + 1));
		maxHead = 0;
	}
#define wander(G, node) for (int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx_##G]; int to = e.to
} G;

int a, b;
int ra[maxn], sa[maxn];
int rb[maxn], sb[maxn];
int limita[maxn];
int limitb[maxn];

int parent[maxn];
int size[maxn];
int topo[maxn];
void DFS(int node)
{
	size[node] = 1;
	wander(G, node)
	{
		DEF(G);
		if (to == parent[node]) continue;
		parent[to] = node;
		DFS(to);
		size[node] += size[to];
	}
	topo[++topo[0]] = node;
}

int lb[maxn];
int ub[maxn];
int t1[maxn];
int t2[maxn];
bool check(int s)
{
	memset(t1, 0, sizeof(int) * (n + 1));
	memset(t2, 0, sizeof(int) * (n + 1));
	lb[1] = std::max(limita[1], s);
	ub[1] = std::min(s - limitb[1], s);
	if (lb[1] > ub[1]) return false;
	for (int i = 2; i <= n; i++)
	{
		lb[i] = limita[i];
		ub[i] = std::min(size[i], s - limitb[i]);
		if (lb[i] > ub[i]) return false;
	}
	for (int i = 1; i <= topo[0]; i++)
	{
		int node = topo[i];
		lb[node] = std::max(lb[node], t1[node]);
		ub[node] = std::min(ub[node], t2[node] + 1);
		if (lb[node] > ub[node]) return false;

		t1[parent[node]] += lb[node];
		t2[parent[node]] += ub[node];
	}
	return true;
}

void run()
{
	int T = readIn();
	while (T--)
	{
		G.clear();
		n = readIn();
		for (int i = 1; i < n; i++)
		{
			int from = readIn();
			int to = readIn();
			G.addEdge(from, to);
			G.addEdge(to, from);
		}

		memset(limita, 0, sizeof(int) * (n + 1));
		memset(limitb, 0, sizeof(int) * (n + 1));
		a = readIn();
		for (int i = 1; i <= a; i++)
		{
			ra[i] = readIn();
			sa[i] = readIn();
			limita[ra[i]] = std::max(limita[ra[i]], sa[i]);
		}
		b = readIn();
		for (int i = 1; i <= b; i++)
		{
			rb[i] = readIn();
			sb[i] = readIn();
			limitb[rb[i]] = std::max(limitb[rb[i]], sb[i]);
		}

		topo[0] = 0;
		DFS(1);
		bool bOk = true;
		for (int i = 1; i <= n; i++)
			if (limita[i] > size[i] || limitb[i] > n - size[i])
			{
				bOk = false;
				break;
			}
		if (!bOk)
		{
			printOut(-1);
			continue;
		}

		int l = 0, r = n + 1;
		while (r - l > 0)
		{
			int mid = l + ((r - l) >> 1);
			if (!check(mid))
				l = mid + 1;
			else
				r = mid;
		}
		if (r == n + 1) printOut(-1);
		else printOut(r);
	}
}

int main()
{
#ifndef LOCAL
	freopen("rbtree.in", "r", stdin);
	freopen("rbtree.out", "w", stdout);
#endif
	run();
	return 0;
}