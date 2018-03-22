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
}

const int maxn = 55;
int n;
struct Graph
{
	struct Edge
	{
		int from;
		int to;
		int next;
	} edges[maxn * maxn];
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
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to
} G;

bool rect[maxn][maxn];
int a[maxn];
int c[maxn];
int budget;

int degree[maxn];
int topo[maxn];
int q[maxn];
int head, tail;
void toposort()
{
	for (int i = 0; i <= n; i++)
	{
		wander(G, i)
		{
			DEF(G);
			degree[to]++;
		}
	}
	for (int i = 0; i <= n; i++)
		if (!degree[i])
			q[tail++] = i;
	while (head != tail)
	{
		int from = q[head];
		head++;
		topo[++topo[0]] = from;
		wander(G, from)
		{
			DEF(G);
			degree[to]--;
			if (!degree[to]) q[tail++] = to;
		}
	}
}

int dis[maxn];
int pre[maxn];
void RunDis(int* cost)
{
	memset(pre, -1, sizeof(pre));
	memset(dis, 0, sizeof(dis));
	for (int i = 1; i <= topo[0]; i++)
	{
		int from = topo[i];
		wander(G, from)
		{
			DEF(G);
			if (dis[from] + cost[from] > dis[to])
			{
				dis[to] = dis[from] + cost[from];
				pre[to] = idx(G);
			}
		}
	}
}

#define RunInstance(x) delete new x
struct brute
{
	int buf[maxn];
	int temp[maxn];
	int ans;
	void search(int depth, LL sum)
	{
		if (sum > budget) return;
		if (depth == n)
		{
			RunDis(temp);
			ans = std::min(ans, dis[n]);
			return;
		}
		for (int i = a[depth]; ~i; i--)
		{
			buf[depth] = i;
			temp[depth] = a[depth] - i;
			search(depth + 1, sum + c[depth] * i);
		}
	}
	brute()
	{
		ans = 25 * n;
		buf[0] = 0;
		search(0, 0);
		printOut(ans);
	}
};
struct cheat
{
	cheat()
	{
		int ans;
		while (true)
		{
			RunDis(a);
			ans = dis[n];

			int minCost;
			int minIdx = -1;
			for (int u = n; ~pre[u]; u = G.edges[pre[u]].from)
			{
				const Graph::Edge& e = G.edges[pre[u]];
				if (a[e.from] && (!~minIdx || c[e.from] < minCost))
				{
					minCost = c[e.from];
					minIdx = e.from;
				}
			}
			if (!~minIdx || minCost > budget)
				break;
			budget -= minCost;
			a[minIdx]--;
		}
		printOut(ans);
	}
};
struct work
{
	int reach[maxn][maxn];
	std::bitset<maxn> isReach[maxn];
	void DFS(int node)
	{
		if (isReach[node][node]) return;
		isReach[node][node] = true;
		wander(G, node)
		{
			DEF(G);
			DFS(to);
			isReach[node] |= isReach[to];
		}
	}
	void init()
	{
		for (int i = 0; i < n; i++)
			DFS(i);
		for (int i = 0; i < n; i++)
		{
			reach[i][0] = 0;
			for (int j = 0; j < n; j++)
				if (isReach[i][j]) reach[i][++reach[i][0]] = j;
		}
	}

	LL cost[maxn];
	int save[maxn];

	work()
	{
		init();

		int ans;
		while (true)
		{
			RunDis(a);
			ans = dis[n];
			memset(cost, -1, sizeof(cost));
			for (int i = 0; i < n; i++)
				if (dis[i] + a[i] == dis[n])
					cost[i] = c[i];

			for (int i = topo[0]; i; i--)
			{
				int node = topo[i];
				if (~cost[node] || !a[node]) continue;
				LL sum = 0;
				save[0] = 0;
				for (int j = 1; j <= reach[node][0]; j++)
					if (~cost[reach[node][j]] && reach[node][j] != node)
					{
						save[++save[0]] = reach[node][j];
						sum += c[reach[node][j]];
					}
				if (!save[0]) continue;
				if (c[node] <= sum)
				{
					cost[node] = c[node];
					for (int i = 1; i <= save[0]; i++)
						cost[save[i]] = -1;
				}
			}
			LL sum = 0;
			for (int i = 0; i < n; i++)
				if (~cost[i]) sum += cost[i];
			if (sum <= budget)
			{
				budget -= sum;
				for (int i = 0; i < n; i++)
					if (~cost[i]) a[i]--;
			}
			else
				break;
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			char ch = getchar();
			while (!isdigit(ch)) ch = getchar();
			rect[i][j] = (ch == '1');
		}
	}
	for (int i = 0; i < n; i++)
	{
		int cost = a[i] = readIn();
		for (int j = 0; j < n; j++)
			if (rect[j][i])
				G.addEdge(i, j);
		G.addEdge(i, n);
	}
	for (int i = 0; i < n; i++)
		c[i] = readIn();
	budget = readIn();
	toposort();

	RunInstance(work);
	//	if (n <= 5)
	//		RunInstance(brute);
	//	else
	//		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("heihei.in", "r", stdin);
	freopen("heihei.out", "w", stdout);
#endif
	run();
	return 0;
}