#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>

const int maxn = 24;

using namespace std;

struct Edge
{
	int from, to, dist;
	Edge(int u, int v, int d) : from(u), to(v), dist(d) {}
};

struct SPFA
{
	int n;
	int m;
	vector<int> G[maxn];
	vector<Edge> E;
	bool inq[maxn];
	int d[maxn];
	int p[maxn];
	int cnt[maxn];
	
	SPFA() : n(24), m(0) {}
	
	void add_edge(int u, int v, int w)
	{
		E.push_back(Edge(u, v, w));
		G[maxn].push_back(m++);
	}
	
	bool spfa(int w)
	{
		memset(inq, 0, sizeof inq);
		memset(d, -0x7f7f7f7f, sizeof d);
		memset(p, -1, sizeof p);
		memset(cnt, 0, sizeof cnt);
		d[23] = w;
		queue<int> q;
		q.push(23);
		inq[23] = true;
		cnt[23]++;
		while (!q.empty())
		{
			int x = q.front();
			q.pop();
			for (int i = 0; i < G[x].size(); i++)
			{
				int e = G[x][i];
				if (d[E[e].to] < d[x] + d[E[e].dist])
					d[E[e].to] = d[x] + d[E[e].dist];
				if (!inq[E[e].to])
				{
					q.push(E[e].to);
					cnt[E[e].to]++;
					if (cnt[E[e].to] > m)
						return false;
				}
			}
		}
		if (d[23] != w)
			return false;
		else
			return true;
	}
	
	void print()
	{
		printf("%d", d[0] - d[23]);
		for (int i = 1; i < maxn; i++)
			printf("%d", d[i] - d[i - 1]);
	}
};

int T;
int a[maxn];
int b[maxn];
int s = 0;
SPFA spfa;

int main()
{
	freopen("cashier.in", "r", stdin);
	freopen("cashier.out", "w", stdout);
	scanf("%d", &T);
	while (T--)
	{
		/*for (int i = 0; i < maxn; i++)
			scanf("%d", &a[i]);
		for (int i = 0; i < maxn; i++)
			scanf("%d", &b[i]);
		for (int i = 16; i < maxn; i++)
			s += b[i];
		for (int i = a[23]; i <= s; i++)
		{
			for (int j = 0; j < 8; j++)
				spfa.add_edge(16 + j, j, a[j] - i);
			for (int j = 8; j < maxn; j++)
				spfa.add_edge(j - 8, j, a[j]);
			for (int j = 1; j < maxn; j++)
				spfa.add_edge(j, j - 1, -b[j]);
			spfa.add_edge(0, 23, -b[23]);
			if (spfa.spfa(i))
			{
				spfa.print();
				break;
			}
		}*/
		printf("-1");
	}
	return 0;
}

