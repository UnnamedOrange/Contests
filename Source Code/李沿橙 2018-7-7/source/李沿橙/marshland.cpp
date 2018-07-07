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

const int maxn = 55;
int n, m, k;
int v[maxn][maxn];
bool forbid[maxn][maxn];

#define RunInstance(x) delete new x
struct brute
{
	LL f[12][26][1 << 10];

	enum { FRT = 1, SEC, TRD, FRTH };
	int temp[12];
	void MakeTransfer(int x, int S)
	{
		if (x & 1)
		{
			int base = n >> 1;
			if (temp[0] == base)
			{
				int nextS = (S << base) & ((1 << n) - 1);
				LL sum = 0;
				int cnt = 0;
				for (int i = 1; i <= temp[0]; i++)
				{
					if (temp[i])
					{
						sum += v[x][i << 1];
						cnt++;
					}
					switch (temp[i])
					{
					case FRT:
					{
						nextS |= 1 << (base + i);
						break;
					}
					case SEC:
					{
						nextS |= 1 << (base + i - 1);
						break;
					}
					case TRD:
					{
						nextS |= 1 << (base + i - 1);
						nextS |= 1 << (i - 1);
						break;
					}
					case FRTH:
					{
						nextS |= 1 << (base + i);
						nextS |= 1 << (i - 1);
						break;
					}
					}
				}
				for (int i = 0; i + cnt <= m; i++)
					f[x + 1][i + cnt][nextS] = std::max(f[x + 1][i + cnt][nextS], f[x][i][S] + sum);
				return;
			}
			temp[++temp[0]] = 0;
			MakeTransfer(x, S);
			temp[0]--;
			int i = temp[0] + 1;
			int y = i << 1;
			if (!forbid[x][y])
			{
				if (!forbid[x - 1][y] && !(S & (1 << (base + i - 1))) &&
					!forbid[x][y + 1] && !(S & (1 << i)))
				{
					temp[++temp[0]] = FRT;
					MakeTransfer(x, S);
					temp[0]--;
				}
				if (!forbid[x - 1][y] && !(S & (1 << (base + i - 1))) &&
					!forbid[x][y - 1] && !(S & (1 << (i - 1))) &&
					(!temp[0] || temp[temp[0]] != FRT && temp[temp[0]] != FRTH))
				{
					temp[++temp[0]] = SEC;
					MakeTransfer(x, S);
					temp[0]--;
				}
				if (!forbid[x][y - 1] && !(S & (1 << (i - 1))) &&
					!forbid[x + 1][y] &&
					(!temp[0] || temp[temp[0]] != FRT && temp[temp[0]] != FRTH))
				{
					temp[++temp[0]] = TRD;
					MakeTransfer(x, S);
					temp[0]--;
				}
				if (!forbid[x][y + 1] && !(S & (1 << i)) &&
					!forbid[x + 1][y])
				{
					temp[++temp[0]] = FRTH;
					MakeTransfer(x, S);
					temp[0]--;
				}
			}
		}
		else
		{
			int base = n - (n >> 1);
			if (temp[0] == base)
			{
				int nextS = (S << base) & ((1 << n) - 1);
				LL sum = 0;
				int cnt = 0;
				for (int i = 1; i <= temp[0]; i++)
				{
					if (temp[i])
					{
						sum += v[x][(i << 1) - 1];
						cnt++;
					}
					switch (temp[i])
					{
					case FRT:
					{
						nextS |= 1 << (base + i - 1);
						break;
					}
					case SEC:
					{
						nextS |= 1 << (base + i - 2);
						break;
					}
					case TRD:
					{
						nextS |= 1 << (base + i - 2);
						nextS |= 1 << (i - 1);
						break;
					}
					case FRTH:
					{
						nextS |= 1 << (base + i - 1);
						nextS |= 1 << (i - 1);
						break;
					}
					}
				}
				for (int i = 0; i + cnt <= m; i++)
					f[x + 1][i + cnt][nextS] = std::max(f[x + 1][i + cnt][nextS], f[x][i][S] + sum);
				return;
			}
			temp[++temp[0]] = 0;
			MakeTransfer(x, S);
			temp[0]--;
			int i = temp[0] + 1;
			int y = (i << 1) - 1;
			if (!forbid[x][y])
			{
				if (!forbid[x - 1][y] && !(S & (1 << (base + i - 1))) &&
					!forbid[x][y + 1] && !(S & (1 << (i - 1))))
				{
					temp[++temp[0]] = FRT;
					MakeTransfer(x, S);
					temp[0]--;
				}
				if (!forbid[x - 1][y] && !(S & (1 << (base + i - 1))) &&
					!forbid[x][y - 1] && !(S & (1 << (i - 2))) &&
					(!temp[0] || temp[temp[0]] != FRT && temp[temp[0]] != FRTH))
				{
					temp[++temp[0]] = SEC;
					MakeTransfer(x, S);
					temp[0]--;
				}
				if (!forbid[x][y - 1] && !(S & (1 << (i - 2))) &&
					!forbid[x + 1][y] &&
					(!temp[0] || temp[temp[0]] != FRT && temp[temp[0]] != FRTH))
				{
					temp[++temp[0]] = TRD;
					MakeTransfer(x, S);
					temp[0]--;
				}
				if (!forbid[x][y + 1] && !(S & (1 << (i - 1))) &&
					!forbid[x + 1][y])
				{
					temp[++temp[0]] = FRTH;
					MakeTransfer(x, S);
					temp[0]--;
				}
			}
		}
	}

	brute() : f(), temp()
	{
		int U = 1 << n;
		for (int i = 1; i <= n; i++)
			for (int S = 0; S < U; S++)
				MakeTransfer(i, S);
		LL sum = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				sum += v[i][j];
		printOut(sum - *std::max_element(f[n + 1][m], f[n + 1][m] + (1 << n)));
	}
};
struct work
{
	struct NetworkFlow
	{
		struct Edge
		{
			int from, to, cap, cost, flow;
			Edge() {}
			Edge(int from, int to, int cap, int cost) : from(from), to(to), cap(cap), cost(cost), flow() {}
		};
		int s, t;
		std::vector<std::vector<int> > G;
		std::vector<Edge> edges;
		void addEdge(int from, int to, int cap, int cost)
		{
			edges.push_back(Edge(from, to, cap, cost));
			edges.push_back(Edge(to, from, 0, -cost));
			int i = edges.size();
			G[from].push_back(i - 2);
			G[to].push_back(i - 1);
		}

		std::vector<LL> dis;
		std::vector<int> opt;
		std::vector<int> pre;
		struct Queue
		{
			static const int size = maxn * maxn * 10;
			int c[size];
			int head, tail;
			void clear() { head = tail = 0; }
			void push(int x) { c[tail] = x; tail = tail + 1 < size ? tail + 1 : 0; }
			void pop() { head = head + 1 < size ? head + 1 : 0; }
			int front() { return c[head]; }
			bool empty() { return head == tail; }
		} q;
		std::vector<bool> inQ;
		bool Bellman_Ford(int& flow, LL& cost)
		{
			dis.clear();
			dis.resize(G.size(), LLONG_MAX / 2);
			opt.clear();
			opt.resize(G.size());
			q.clear();
			q.push(s);
			dis[s] = 0;
			inQ[s] = true;
			opt[s] = INT_MAX;
			while (!q.empty())
			{
				int from = q.front();
				q.pop();
				inQ[from] = false;
				for (int i = 0; i < G[from].size(); i++)
				{
					const Edge& e = edges[G[from][i]];
					if (e.flow < e.cap && dis[from] + e.cost < dis[e.to])
					{
						dis[e.to] = dis[from] + e.cost;
						opt[e.to] = std::min(e.cap - e.flow, opt[from]);
						pre[e.to] = G[from][i];
						if (!inQ[e.to])
						{
							q.push(e.to);
							inQ[e.to] = true;
						}
					}
				}
			}
			if (!opt[t] || dis[t] >= 0)
				return false;
			flow += opt[t];
			cost += opt[t] * dis[t];
			for (int u = t; u != s; u = edges[pre[u]].from)
			{
				edges[pre[u]].flow += opt[t];
				edges[pre[u] ^ 1].flow -= opt[t];
			}
			return true;
		}
		LL mincost()
		{
			int flow = 0;
			LL cost = 0;
			inQ.clear();
			inQ.resize(G.size());
			pre.clear();
			pre.resize(G.size());
			while (Bellman_Ford(flow, cost));
			return cost;
		}
	} nf;

	int N;
	int idx[maxn][maxn][2];

	work() : N(), idx()
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				idx[i][j][0] = ++N;
				if ((i + j) & 1)
					idx[i][j][1] = ++N;
			}
		nf.G.resize(N + 3);
		nf.s = N + 1;
		nf.t = N + 2;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (!forbid[i][j])
				{
					if ((i + j) & 1)
					{
						if (i & 1)
						{
							if (i > 1) nf.addEdge(idx[i][j][1], idx[i - 1][j][0], 1, 0);
							if (i < n) nf.addEdge(idx[i][j][1], idx[i + 1][j][0], 1, 0);
							if (j > 1) nf.addEdge(idx[i][j - 1][0], idx[i][j][0], 1, 0);
							if (j < n) nf.addEdge(idx[i][j + 1][0], idx[i][j][0], 1, 0);
						}
						else
						{
							if (i > 1) nf.addEdge(idx[i - 1][j][0], idx[i][j][0], 1, 0);
							if (i < n) nf.addEdge(idx[i + 1][j][0], idx[i][j][0], 1, 0);
							if (j > 1) nf.addEdge(idx[i][j][1], idx[i][j - 1][0], 1, 0);
							if (j < n) nf.addEdge(idx[i][j][1], idx[i][j + 1][0], 1, 0);
						}
						nf.addEdge(idx[i][j][0], idx[i][j][1], 1, -v[i][j]);
					}
					else
					{
						if (i & 1)
							nf.addEdge(nf.s, idx[i][j][0], 1, 0);
						else
							nf.addEdge(idx[i][j][0], nf.t, 1, 0);
					}
				}
		nf.s = 0;
		nf.addEdge(nf.s, N + 1, m, 0);
		LL sum = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				sum += v[i][j];
		printOut(sum + nf.mincost());
	}
};

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	m = std::min(m, n * n / 4);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			v[i][j] = readIn();
	for (int i = 1; i <= k; i++)
	{
		int x = readIn();
		int y = readIn();
		forbid[x][y] = true;
	}
	for (int i = 0; i <= n; i++)
		forbid[0][i] = forbid[i][0] =
		forbid[n + 1][i] = forbid[i][n + 1] = true;

	if (n <= 10 && !(n & 1)) // 编码方式只适用于 n 为偶数的情况……
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("marshland.in", "r", stdin);
	freopen("marshland.out", "w", stdout);
#endif
	run();
	return 0;
}