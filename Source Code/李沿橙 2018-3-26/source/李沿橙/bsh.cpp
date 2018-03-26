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
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = 52005;
int n;

struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn * 4];
	int i;
	int head[maxn];
	Graph() : i()
	{
		memset(head, -1, sizeof(head));
	}
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

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 5005;
	struct Queue
	{
		int c[maxN];
		int head, tail;
		Queue() : head(), tail() {}
		bool empty() { return head == tail; }
		void push(int x) { c[tail++] = x; }
		void pop() { head++; }
		int front() { return c[head]; }
		void clear() { head = tail = 0; }
	} q;
	int dis[maxN][maxN];
	bool vis[maxN];
	brute() : dis()
	{
		for (int i = 1; i < n; i++)
		{
			G.addEdge(i, i + 1);
			G.addEdge(i + 1, i);
		}
		G.addEdge(n, 1);
		G.addEdge(1, n);
		for (int i = 1; i <= n; i++)
		{
			int* d = dis[i];
			q.clear();
			q.push(i);
			memset(vis, 0, sizeof(vis));
			vis[i] = true;
			d[i] = 0;
			while (!q.empty())
			{
				int from = q.front(); q.pop();
				wander(G, from)
				{
					DEF(G);
					if (vis[to]) continue;
					d[to] = d[from] + 1;
					q.push(to);
					vis[to] = true;
				}
			}
		}
		int q = readIn();
		while (q--)
		{
			int from = readIn();
			int to = readIn();
			printOut(dis[from][to]);
		}
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	for (int i = 1, to = n - 3; i <= to; i++)
	{
		int u = readIn();
		int v = readIn();
		G.addEdge(u, v);
		G.addEdge(v, u);
	}

	if (n <= 5000)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("bsh.in", "r", stdin);
	freopen("bsh.out", "w", stdout);
#endif
	run();
	return 0;
}