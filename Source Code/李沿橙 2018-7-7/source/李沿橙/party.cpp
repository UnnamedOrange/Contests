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

const int INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
const int maxn = int(3e5) + 5;
const int maxm = int(1e3) + 5;
int n, m, q;
int a[maxn];
int LCA(int, int);
struct Query
{
	int c[6];
	int lca;
	void read()
	{
		c[0] = readIn();
		for (int i = 1; i <= c[0]; i++)
			c[i] = readIn();
		lca = LCA(c[1], c[2]);
		for (int i = 3; i <= c[0]; i++)
			lca = LCA(lca, c[i]);
	}
} querys[maxn];

typedef std::vector<std::vector<int> > Graph;
Graph G;
int parent[20][maxn];
int depth[maxn];
void DFS(int node)
{
	depth[node] = depth[parent[0][node]] + 1;
	for (int i = 0; i < G[node].size(); i++)
	{
		int to = G[node][i];
		DFS(to);
	}
}
int logn;
void goDouble()
{
	while (1 << logn < n) logn++;
	for (int i = 1; i <= logn; i++)
		for (int j = 1; j <= n; j++)
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
}
int LCA(int u, int v)
{
	if (depth[u] < depth[v])
		std::swap(u, v);
	for (int i = logn; ~i; i--)
		if (depth[parent[i][u]] >= depth[v])
			u = parent[i][u];
	if (u != v)
	{
		for (int i = logn; ~i; i--)
			if (parent[i][u] != parent[i][v])
			{
				u = parent[i][u];
				v = parent[i][v];
			}
		u = parent[0][u];
	}
	return u;
}

#define RunInstance(x) delete new x
struct brute
{
	int stamp;
	int vis[maxm];
	int appear[6][maxm];

	struct NetworkFlow
	{
		struct Edge
		{
			int from, to, cap, flow;
			Edge() {}
			Edge(int from, int to, int cap) : from(from), to(to), cap(cap), flow() {}
		};
		Graph G;
		std::vector<Edge> edges;
		int addEdge(int from, int to, int cap)
		{
			edges.push_back(Edge(from, to, cap));
			edges.push_back(Edge(to, from, 0));
			int i = edges.size();
			G[from].push_back(i - 2);
			G[to].push_back(i - 1);
			return i - 2;
		}
		void operator=(const NetworkFlow& b)
		{
			G = b.G;
			edges = b.edges;
			s = b.s;
			t = b.t;
		}

		int s, t;

		int level[maxn];
		std::vector<int> cur;
		int Dinic(int node, int opt)
		{
			if (node == t || !opt) return opt;
			int flow = 0;
			for (int& i = cur[node]; i < G[node].size(); i++)
			{
				int t;
				Edge& e = edges[G[node][i]];
				if (e.flow < e.cap && level[node] + 1 == level[e.to] &&
					(t = Dinic(e.to, std::min(opt, e.cap - e.flow))))
				{
					flow += t;
					opt -= t;
					e.flow += t;
					edges[G[node][i] ^ 1].flow -= t;
					if (!opt) break;
				}
			}
			return flow;
		}

		struct Queue
		{
			int c[maxn];
			int head, tail;
			Queue() : head(), tail() {}
			void clear() { head = tail = 0; }
			void push(int x) { c[tail++] = x; }
			void pop() { head++; }
			int front() { return c[head]; }
			bool empty() { return head == tail; }
		} q;
		int stamp;
		int vis[maxn];
		NetworkFlow() : stamp(), vis() {}
		bool BFS()
		{
			q.clear();
			stamp++;
			vis[s] = stamp;
			q.push(s);
			level[s] = 0;
			while (!q.empty())
			{
				int from = q.front();
				q.pop();
				for (int i = 0; i < G[from].size(); i++)
				{
					const Edge
						& e = edges[G[from][i]];
					if (e.flow < e.cap && vis[e.to] != stamp)
					{
						vis[e.to] = stamp;
						level[e.to] = level[from] + 1;
						q.push(e.to);
					}
				}
			}
			return vis[t] == stamp;
		}
		int maxflow()
		{
			int flow = 0;
			while (BFS())
			{
				cur.clear();
				cur.resize(G.size());
				flow += Dinic(s, INF);
			}
			return flow;
		}
	} nf, backup;

	brute() : stamp(), vis(), appear()
	{
		backup.G.resize(m + 7);
		backup.s = 0;
		backup.t = m + 1;
		for (int i = 1; i <= m; i++)
			backup.addEdge(i, backup.t, 1);

		for (int i = 1; i <= q; i++)
		{
			const int* c = querys[i].c;
			int lca = querys[i].lca;
			for (int j = 1; j <= c[0]; j++)
			{
				stamp++;
				appear[j][0] = 0;
				int cnt = c[j];
				while (true)
				{
					if (vis[a[cnt]] != stamp)
					{
						vis[a[cnt]] = stamp;
						appear[j][++appear[j][0]] = a[cnt];
					}
					if (cnt == lca)
						break;
					cnt = parent[0][cnt];
				}
			}

			int l = 0, r = m / c[0] + 1;
			while (r - l > 1)
			{
				int mid = (l + r) >> 1;
				nf = backup;
				for (int j = 1; j <= c[0]; j++)
					for (int k = appear[j][0]; k; k--)
						nf.addEdge(m + 1 + j, appear[j][k], 1);
				for (int j = 1; j <= c[0]; j++)
					nf.addEdge(nf.s, m + 1 + j, mid);
				if (nf.maxflow() == mid * c[0])
					l = mid;
				else
					r = mid;
			}
			printOut(l * c[0]);
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	if (!q)
		return;
	G.resize(n + 1);
	for (int i = 2; i <= n; i++)
		G[parent[0][i] = readIn()].push_back(i);
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	DFS(1);
	goDouble();
	for (int i = 1; i <= q; i++)
		querys[i].read();

	if (n <= 3000 && q <= 3000)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("party.in", "r", stdin);
	freopen("party.out", "w", stdout);
#endif
	run();
	return 0;
}