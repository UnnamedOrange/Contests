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
	putchar(' ');
}

const int INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
const int maxn = 205;
int T, C;
int n, m;
int b[maxn];
int rect[maxn][maxn];
std::vector<std::vector<int> > teacher[maxn];
int s[maxn];

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
	int s, t;
	void addEdge(int from, int to, int cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}

	std::vector<int> vis;
	std::vector<int> opt;
	std::vector<int> pre;
	bool BFS(int& flow)
	{
		static int stamp;
		stamp++;
		static int q[maxn * 2];
		int head = 0, tail = 0;
		q[tail++] = s;
		vis[s] = stamp;
		opt.clear();
		opt.resize(n + m + 2, 0);
		pre.resize(n + m + 2);
		opt[s] = INF;
		while (head != tail)
		{
			int from = q[head++];
			for (int i = 0; i < G[from].size(); i++)
			{
				const Edge& e = edges[G[from][i]];
				if (e.flow < e.cap && vis[e.to] != stamp)
				{
					opt[e.to] = std::min(opt[from], e.cap - e.flow);
					pre[e.to] = G[from][i];
					vis[e.to] = stamp;
					q[tail++] = e.to;
					if (vis[t] == stamp) break;
				}
			}
		}
		if (vis[t] != stamp) return false;
		flow += opt[t];
		for (int u = t; u != s; u = edges[pre[u]].from)
		{
			edges[pre[u]].flow += opt[t];
			edges[pre[u] ^ 1].flow -= opt[t];
		}
		return true;
	}

	int EdmondsKarp()
	{
		int flow = 0;
		while (BFS(flow));
		return flow;
	}

	void clear(int newSize)
	{
		edges.clear();
		edges.reserve(n * m * 10);
		G.clear();
		G.resize(newSize);
		vis.resize(newSize);
	}
} nf;

#define RunInstance(x) delete new x
struct cheat
{
	cheat()
	{
		int lastSel = 0;
		int remain = b[1];
		for (int i = 1; i <= n; i++)
			if (rect[i][1] == 1)
			{
				if (remain)
				{
					printOut(1);
					lastSel = i;
					remain--;
				}
				else
					printOut(m + 1);
			}
			else
				printOut(m + 1);
		putchar('\n');
		for (int i = 1; i <= n; i++)
			if (rect[i][1] == 1)
				printOut(std::max(0, i - lastSel));
			else
				printOut(i);
	}
};
struct work
{
	int ans1[maxn];
	int ans2[maxn];

	work() : ans1(), ans2()
	{
		nf.clear(n + m + 2);
		nf.s = 0;
		nf.t = n + m + 1;
		for (int i = 1; i <= n; i++)
			nf.addEdge(nf.s, i, 1);
		for (int i = 1; i <= m; i++)
			nf.addEdge(n + i, nf.t, b[i]);
		for (int i = 1; i <= n; i++)
		{
			int& j = ans1[i];
			for (j = 1; j <= m; j++)
			{
				for (int k = 0; k < teacher[i][j].size(); k++)
					nf.addEdge(i, n + teacher[i][j][k], 1);
				if (nf.EdmondsKarp()) break;
			}
		}

		for (int i = 1; i <= n; i++)
		{
			if (ans1[i] <= s[i])
			{
				ans2[i] = 0;
				continue;
			}
			nf.clear(n + m + 2);
			for (int j = 1; j <= n; j++)
				nf.addEdge(nf.s, j, 1);
			for (int j = 1; j <= m; j++)
				nf.addEdge(n + j, nf.t, b[j]);
			for (int j = 1; j <= s[i]; j++)
				for (int k = 0; k < teacher[i][j].size(); k++)
					nf.addEdge(i, n + teacher[i][j][k], 1);
			if (!nf.EdmondsKarp())
			{
				ans2[i] = i;
				continue;
			}

			int& j = ans2[i];
			for (j = 1; j < i; j++) // try to be the j + 1(th)
			{
				if (ans1[j] == m + 1) continue;
				const std::vector<int> Teacher = teacher[j][ans1[j]];
				for (int k = 0; k < Teacher.size(); k++)
					nf.addEdge(j, n + Teacher[k], 1);
				int aug = nf.EdmondsKarp();
				if (!aug) break; // fail to be the j + 1(th), be the j(th)
			}
			j = i - j;
		}

		for (int i = 1; i <= n; i++)
			printOut(ans1[i]);
		putchar('\n');
		for (int i = 1; i <= n; i++)
			printOut(ans2[i]);
	}
};

void run()
{
	T = readIn();
	C = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		for (int i = 1; i <= m; i++)
			b[i] = readIn();
		for (int i = 1; i <= n; i++)
		{
			teacher[i].clear();
			teacher[i].resize(m + 1);
			for (int j = 1; j <= m; j++)
				if (rect[i][j] = readIn())
					teacher[i][rect[i][j]].push_back(j);
		}
		for (int i = 1; i <= n; i++)
			s[i] = readIn();

		if (m == 1)
			RunInstance(cheat);
		else
			RunInstance(work);

		putchar('\n');
	}
}

int main()
{
#ifndef LOCAL
	freopen("mentor.in", "r", stdin);
	freopen("mentor.out", "w", stdout);
#endif
	run();
	return 0;
}