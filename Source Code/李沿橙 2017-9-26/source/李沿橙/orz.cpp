#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = 150005;
INT n, K;
INT a[maxn], b[maxn];

#define RunInstance(x) delete new x
struct work
{
	work()
	{

	}
};
struct cheat2
{
	struct Edge
	{
		INT from;
		INT to;
		INT cap;
		INT flow;
		INT cost;

		Edge() {}
		Edge(INT u, INT v, INT c, INT f, INT cost) : from(u), to(v), cap(c), flow(f), cost(cost) {}
	};
	std::vector<Edge> edges;
	std::vector<std::vector<INT> > G;

	inline void addEdge(INT from, INT to, INT cap, INT cost)
	{
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		INT size = edges.size();
		G[from].push_back(size - 2);
		G[to].push_back(size - 1);
	}

	bool BellmanFord(INT N, INT s, INT t, INT& flow, INT& cost)
	{
		std::vector<bool> inQ(N + 1);
		std::vector<INT> dis(N + 1, INF);
		std::vector<INT> opt(N + 1);
		std::vector<INT> pre(N + 1);

		dis[s] = 0;
		pre[s] = 0;
		opt[s] = INF;

		std::queue<INT> q;
		q.push(s);
		inQ[s] = true;
		while (!q.empty())
		{
			INT u = q.front();
			q.pop();
			inQ[u] = false;
			for (int i = 0; i < G[u].size(); i++)
			{
				Edge& e = edges[G[u][i]];
				if (e.cap > e.flow && dis[e.to] > dis[u] + e.cost)
				{
					dis[e.to] = dis[u] + e.cost;
					pre[e.to] = G[u][i];
					opt[e.to] = std::min(opt[u], e.cap - e.flow);
					if (!inQ[e.to])
					{
						q.push(e.to);
						inQ[e.to] = true;
					}
				}
			}
		}
		if (!opt[t]) return false;
		flow += opt[t];
		cost += dis[t] * opt[t];
		for (int u = t; u != s; u = edges[pre[u]].from)
		{
			edges[pre[u]].flow += opt[t];
			edges[pre[u] ^ 1].flow -= opt[t];
		}
		return true;
	}
	INT MCMF(INT s, INT t)
	{
		INT flow = 0;
		INT cost = 0;
		while (BellmanFord(2 * n + 3, s, t, flow, cost));
		return cost;
	}

	cheat2()
	{
		const INT s = 2 * n + 1;
		const INT t = 2 * n + 2;
		const INT x = 2 * n + 3;
		G.resize(x + 1);
		addEdge(x, s, K, 0);
		for (int i = 1; i <= n; i++)
		{
			addEdge(s, 2 * i - 1, 1, a[i]);
			addEdge(2 * i - 1, 2 * i, 1, 0);
			addEdge(2 * i, t, 1, b[i]);
			if (i != n) addEdge(2 * i, 2 * (i + 1), INF, 0);
		}

		cout << MCMF(x, t) << endl;
	}
};
struct cheat1
{
	INT f[2][405][405];

	cheat1() : f()
	{
		memset(f[1], 0x3f, sizeof(f[1]));
		f[1][0][0] = 0;
		f[1][1][0] = a[1];
		f[1][1][1] = a[1] + b[1];
		for (int i = 2; i <= n; i++)
		{
			INT cnt = i & 1;
			INT pre = !cnt;
			memset(f[cnt], 0x3f, sizeof(f[cnt]));

			f[cnt][0][0] = 0;
			for (int j = 1; j <= std::min(INT(i), INT(K)); j++)
			{
				for (int k = 0; k <= j; k++)
				{
					INT& ans = f[cnt][j][k];
					if (j < i) ans = std::min(ans, f[pre][j][k]);
					if (j && j > k) ans = std::min(ans, f[pre][j - 1][k] + a[i]);
					if (k) ans = std::min(ans, f[pre][j][k - 1] + b[i]);
					if (j && k) ans = std::min(ans, f[pre][j - 1][k - 1] + a[i] + b[i]);
				}
			}
		}
		cout << f[n & 1][K][K] << endl;
	}
};
struct sameA
{
	sameA()
	{
		std::sort(b + 1, b + 1 + n);
		INT ans = a[1] * K;
		for (int i = 1; i <= K; i++)
		{
			ans += b[i];
		}
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	K = readIn();

	bool sign = true;
	INT A = -1;
	for (int i = 1; i <= n; i++)
	{
		a[i] = readIn();
		if (!sign) {}
		else if (A == -1)
			A = a[i];
		else if (A != a[i])
			sign = false;
	}
	for (int i = 1; i <= n; i++)
	{
		b[i] = readIn();
	}

	if (sign) RunInstance(sameA);
	//else if (n <= 400) RunInstance(cheat1);
	else if (n <= 2000) RunInstance(cheat2); //Network flowing: can't pass
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("orz.in", "r", stdin);
	freopen("orz.out", "w", stdout);
#endif
	run();
	return 0;
}