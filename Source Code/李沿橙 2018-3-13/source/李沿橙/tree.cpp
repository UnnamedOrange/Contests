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
typedef long long INT_PUT;
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
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0)
		putchar('-');
	else
		x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(2e5) + 5;
int n, k;

struct Graph
{
	struct Edge
	{
		int to;
		int cost;
		int next;
	} edges[maxn * 2];
	int head[maxn];
	int i;
	Graph() : i()
	{
		memset(head, -1, sizeof(head));
	}
	void addEdge(int from, int to, int cost)
	{
		Edge& e = edges[i];
		e.to = to;
		e.cost = cost;
		e.next = head[from];
		head[from] = i;
		i++;
	}
#define wander(G, node) for (int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx_##G]; int to = e.to; int cost = e.cost
} G;

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{

	}
};
struct work
{
	bool vis[maxn];

	int size[maxn];
	void DFS1(int node, int parent)
	{
		size[node] = 1;
		wander(G, node)
		{
			DEF(G);
			if (to == parent || vis[to]) continue;
			DFS1(to, node);
			size[node] += size[to];
		}
	}
	int GetRoot(int node, int parent, int s)
	{
		wander(G, node)
		{
			DEF(G);
			if (to == parent || vis[to]) continue;
			if (size[to] > (s >> 1))
				return GetRoot(to, node, s);
		}
		return node;
	}
	LL depth[maxn];
	struct Node
	{
		int idx;
		int belong;
		LL depth;
		Node() {}
		Node(int idx, int belong, LL depth) : idx(idx), belong(belong), depth(depth) {}
		bool operator> (const Node& b) const
		{
			return depth > b.depth;
		}
	};
	std::vector<Node> vset[maxn];
	void DFS2(int node, int parent, int belong, int center)
	{
		vset[center].push_back(Node(node, belong, depth[node]));
		wander(G, node)
		{
			DEF(G);
			if (to == parent || vis[to]) continue;
			depth[to] = depth[node] + cost;
			DFS2(to, node, belong ? belong : to, center);
		}
	}

	void solve(int node)
	{
		DFS1(node, 0);
		vset[node].reserve(size[node]);
		node = GetRoot(node, 0, size[node]);
		vis[node] = true;

		depth[node] = 0;
		DFS2(node, 0, 0, node);
		std::sort(vset[node].begin(), vset[node].end(), std::greater<Node>());

		wander(G, node)
		{
			DEF(G);
			if (vis[to]) continue;
			solve(to);
		}
	}

	struct HeapNode
	{
		int center;
		int a;
		int b;
		LL length;
		bool expand;
		HeapNode() {}
		HeapNode(int center, int a, int b, LL length, bool expand) : center(center), a(a), b(b), length(length), expand(expand) {}
		bool operator<(const HeapNode& b) const
		{
			return length < b.length;
		}
	};

	work() : vis()
	{
		std::priority_queue<HeapNode> pq;
		solve(1);
		for (int i = 1; i <= n; i++)
			if (vset[i].size() >= 2)
				pq.push(HeapNode(i, 0, 1, vset[i][0].depth + vset[i][1].depth, true));
		for (int i = 1; i <= k; )
		{
			HeapNode t = pq.top();
			pq.pop();
			if (t.a + 1 < t.b)
				pq.push(HeapNode(t.center, t.a + 1, t.b, vset[t.center][t.a + 1].depth + vset[t.center][t.b].depth, false));
			if (t.expand && t.b < vset[t.center].size() - 1)
				pq.push(HeapNode(t.center, t.a, t.b + 1, vset[t.center][t.a].depth + vset[t.center][t.b + 1].depth, true));

			if (vset[t.center][t.a].belong != vset[t.center][t.b].belong)
			{
				//printf("%d -> %d: ", vset[t.center][t.a].idx, vset[t.center][t.b].idx);
				printOut(t.length);
				i++;
			}
		}
	}
};

void run()
{
	n = readIn();
	k = readIn();
	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		int cost = readIn();
		G.addEdge(from, to, cost);
		G.addEdge(to, from, cost);
	}

	RunInstance(work);
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