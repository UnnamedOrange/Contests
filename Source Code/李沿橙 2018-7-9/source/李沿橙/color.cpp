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

const int maxn = 35;
int n;
char rect[maxn][maxn];

#define RunInstance(x) delete new x
struct brute
{
	int fill[maxn][maxn];
	bool check(int x, int y)
	{
		if (fill[x - 1][y - 1] == 0 &&
			fill[x - 1][y] == 0 &&
			fill[x][y - 1] == 0 &&
			fill[x][y] == 0)
			return false;
		if (fill[x - 1][y - 1] == 0 &&
			fill[x - 1][y] == 1 &&
			fill[x][y - 1] == 1 &&
			fill[x][y] == 0)
			return false;
		if (fill[x - 1][y - 1] == 1 &&
			fill[x - 1][y] == 0 &&
			fill[x][y - 1] == 0 &&
			fill[x][y] == 1)
			return false;
		if (fill[x - 1][y - 1] == 1 &&
			fill[x - 1][y] == 1 &&
			fill[x][y - 1] == 1 &&
			fill[x][y] == 1)
			return false;
		return true;
	}
	bool bFound;
	void search(int x, int y)
	{
		if (x == n)
		{
			if (check(n, n))
				bFound = true;
			return;
		}
		int newx = x;
		int newy = y + 1;
		if (newy == n)
		{
			newx++;
			newy = 2;
		}

		if (rect[x][y] == rect[x - 1][y] &&
			rect[x][y] == rect[x][y - 1])
		{
			if (fill[x - 1][y] != fill[x][y - 1])
				return;
			fill[x][y] = fill[x - 1][y];
			if (check(x, y) && (y != n - 1 || check(x, n)) && (x != n - 1 || check(n, y)))
				search(newx, newy);
		}
		else if (rect[x][y] == rect[x - 1][y])
		{
			fill[x][y] = fill[x - 1][y];
			if (check(x, y) && (y != n - 1 || check(x, n)) && (x != n - 1 || check(n, y)))
				search(newx, newy);
		}
		else if (rect[x][y] == rect[x][y - 1])
		{
			fill[x][y] = fill[x][y - 1];
			if (check(x, y) && (y != n - 1 || check(x, n)) && (x != n - 1 || check(n, y)))
				search(newx, newy);
		}
		else
		{
			fill[x][y] = 0;
			if (check(x, y) && (y != n - 1 || check(x, n)) && (x != n - 1 || check(n, y)))
				search(newx, newy);
			if (bFound) return;
			fill[x][y] = 1;
			if (check(x, y) && (y != n - 1 || check(x, n)) && (x != n - 1 || check(n, y)))
				search(newx, newy);
		}
	}

	brute() : fill(), bFound()
	{
		for (int i = 1; i <= n; i++)
		{
			fill[1][i] = rect[1][i] - '0';
			fill[i][1] = rect[i][1] - '0';
			fill[n][i] = rect[n][i] - '0';
			fill[i][n] = rect[i][n] - '0';
		}
		search(2, 2);
		puts(bFound ? "YES" : "NO");
	}
};
struct work
{
	struct NetworkFlow
	{
		struct Edge
		{
			int from, to, cap, flow;
			Edge() {}
			Edge(int from, int to, int cap) : from(from), to(to), cap(cap), flow() {}
		};
		std::vector<Edge> edges;
		std::vector<std::vector<int> > G;
		void addEdge(int from, int to, int cap)
		{
			edges.push_back(Edge(from, to, cap));
			edges.push_back(Edge(to, from, 0));
			int i = edges.size();
			G[from].push_back(i - 2);
			G[to].push_back(i - 1);
		}

		int s, t;

		std::vector<int> level;
		std::vector<int> cur;
		int Dinic(int node, int opt)
		{
			if (node == t || !opt) return opt;
			int flow = 0;
			for (int& i = cur[node]; i < G[node].size(); i++)
			{
				Edge& e = edges[G[node][i]];
				int t;
				if (level[node] + 1 == level[e.to] && e.flow < e.cap &&
					(t = Dinic(e.to, std::min(opt, e.cap - e.flow))))
				{
					e.flow += t;
					edges[G[node][i] ^ 1].flow -= t;
					flow += t;
					opt -= t;
					if (!opt) break;
				}
			}
			return flow;
		}
		struct Queue : private std::vector<int>
		{
			int head;
			bool empty() { return head == size(); }
			void clear() { head = 0; std::vector<int>::clear(); }
			void push(int x) { push_back(x); }
			void pop() { head++; }
			int front() { return operator[](head); }
		} q;
		std::vector<bool> vis;
		bool BFS()
		{
			q.clear();
			level.resize(G.size());
			vis.clear();
			vis.resize(G.size());
			level[s] = 0;
			vis[s] = true;
			q.push(s);
			while (!q.empty())
			{
				int from = q.front();
				q.pop();
				for (int i = 0; i < G[from].size(); i++)
				{
					const Edge& e = edges[G[from][i]];
					if (e.flow < e.cap && !vis[e.to])
					{
						vis[e.to] = true;
						level[e.to] = level[e.from] + 1;
						q.push(e.to);
					}
				}
			}
			return vis[t];
		}
		int maxFlow()
		{
			int flow = 0;
			while (BFS())
			{
				cur.clear();
				cur.resize(G.size());
				flow += Dinic(s, INT_MAX);
			}
			return flow;
		}
	} nf;

	int N;
	int idx[maxn][maxn];
	int color[maxn][maxn];
	int cnt[maxn * maxn];

	int countHelper(int x, int y)
	{
		int f = 0;
		if (std::isdigit(rect[x - 1][y - 1]))
			if (rect[x - 1][y - 1] == rect[x - 1][y])
				f++;
		if (std::isdigit(rect[x - 1][y]))
			if (rect[x - 1][y] == rect[x][y])
				f++;
		if (std::isdigit(rect[x][y]))
			if (rect[x][y] == rect[x][y - 1])
				f++;
		if (std::isdigit(rect[x][y - 1]))
			if (rect[x][y - 1] == rect[x - 1][y - 1])
				f++;
		return f;
	}

	int cap[maxn][maxn];

	work() : N(), idx(), cnt(), cap()
	{
		for (int i = 2; i <= n; i++)
			for (int j = 2; j <= n; j++)
				idx[i][j] = ++N;
		color[1][2] = 1;
		for (int i = 2; i <= n; i++)
		{
			color[i][2] = !color[i - 1][2];
			for (int j = 3; j <= n; j++)
				color[i][j] = !color[i][j - 1];
		}
		nf.G.resize(N + 2);
		nf.s = 0;
		nf.t = N + 1;
		for (int i = 2; i <= n; i++)
			for (int j = 2; j <= n; j++)
			{
				int c = countHelper(i, j);
				cap[i][j] += 2 - c;
			}
		for (int i = 2; i <= n; i++)
		{
			for (int j = 2; j <= n; j++) if (!color[i][j])
			{
				if (i > 2)
				{
					if (rect[i - 1][j - 1] == rect[i - 1][j])
					{
						cap[i][j]--;
						cap[i - 1][j]--;
					}
					else
						nf.addEdge(idx[i][j], idx[i - 1][j], 1);
				}
				if (i < n)
				{
					if (rect[i][j - 1] == rect[i][j])
					{
						cap[i][j]--;
						cap[i + 1][j]--;
					}
					else
						nf.addEdge(idx[i][j], idx[i + 1][j], 1);
				}
				if (j > 2)
				{
					if (rect[i - 1][j - 1] == rect[i][j - 1])
					{
						cap[i][j]--;
						cap[i][j - 1]--;
					}
					else
						nf.addEdge(idx[i][j], idx[i][j - 1], 1);
				}
				if (j < n)
				{
					if (rect[i - 1][j] == rect[i][j])
					{
						cap[i][j]--;
						cap[i][j + 1]--;
					}
					else
						nf.addEdge(idx[i][j], idx[i][j + 1], 1);
				}
			}
		}

		int full1 = 0, full2 = 0;
		for (int i = 2; i <= n; i++)
			for (int j = 2; j <= n; j++)
				if (color[i][j])
					full1 += cap[i][j];
				else
					full2 += cap[i][j];
		if (full1 != full2)
		{
			puts("NO");
			return;
		}

		for (int i = 2; i <= n; i++)
			for (int j = 2; j <= n; j++)
			{
				if (cap[i][j] < 0)
				{
					puts("NO");
					return;
				}
				if (cap[i][j])
				{
					if (color[i][j])
						nf.addEdge(idx[i][j], nf.t, cap[i][j]);
					else
						nf.addEdge(nf.s, idx[i][j], cap[i][j]);
				}
			}

		if (nf.maxFlow() != full1)
			puts("NO");
		else
			puts("YES");
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			char ch = getchar();
			while (!(std::isdigit(ch) || std::isalpha(ch))) ch = getchar();
			rect[i][j] = ch;
		}
	}

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
#endif
	run();
	return 0;
}