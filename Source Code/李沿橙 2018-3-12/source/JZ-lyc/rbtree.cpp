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
	if (x < 0)
		putchar('-');
	else
		x = -x;
	do buffer[length++] = -(x % 10) + '0';
	while (x /= 10);
	do putchar(buffer[--length]);
	while (length);
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int n;
struct Edge
{
	int to;
	int cost;
	int next;
};
template <int cNode = maxn, int cEdge = maxn * 2>
struct Graph
{
	Edge edges[cEdge];
	int head[cNode];
	int maxHead;
	int i;
	Graph() : maxHead(cNode - 1)
	{
		clear();
	}
	void clear()
	{
		i = 0;
		memset(head, -1, sizeof(int) * (maxHead + 1));
		maxHead = 0;
	}
	void addEdge(int from, int to, int cost = 1)
	{
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
		maxHead = std::max(maxHead, from);
		i++;
	}
#define wander(G, node) for (int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Edge& e = G.edges[idx_##G]; int to = e.to; int cost = e.cost
};
Graph<> G;

int stamp;
int dfn[maxn];
int end[maxn];
void DFS(int node, int parent)
{
	stamp++;
	dfn[node] = stamp;
	wander(G, node)
	{
		DEF(G);
		if (to == parent) continue;
		DFS(to, node);
	}
	end[node] = stamp;
}
int a, b;
int limita[maxn];
int limitb[maxn];
int ra[maxn], sa[maxn];
int rb[maxn], sb[maxn];

#define RunInstance(x) x()
void brute()
{
	static int count1[1 << 17];
	if (!count1[1])
		for (int S = 1; S < (1 << 17); S++)
			count1[S] = count1[S ^ (S & -S)] + 1;
	int maska[20];
	int maskb[20];
	for (int i = 1; i <= a; i++)
	{
		int& t = maska[i];
		t = 0;
		for (int j = dfn[ra[i]] - 1, to = end[ra[i]] - 1; j <= to; j++)
			t |= (1 << j);
	}
	for (int i = 1; i <= b; i++)
	{
		int& t = maskb[i];
		t = 0;
		for (int j = 0, to = dfn[rb[i]] - 2; j <= to; j++)
			t |= (1 << j);
		for (int j = end[rb[i]]; j < n; j++)
			t |= (1 << j);
	}

	int U = 1 << n;
	int ans = n + 1;
	for (int S = 0; S < U; S++)
	{
		bool bOk = true;
		for (int i = 1; i <= a; i++)
		{
			if (count1[S & maska[i]] < sa[i])
			{
				bOk = false;
				break;
			}
		}
		if (!bOk) continue;
		for (int i = 1; i <= b; i++)
		{
			if (count1[S & maskb[i]] < sb[i])
			{
				bOk = false;
				break;
			}
		}
		if (!bOk) continue;
		if (count1[S] < ans)
			ans = count1[S];
	}
	if (ans > n) printOut(-1);
	else printOut(ans);
}

Graph<maxn, maxn * 4> GDC;
bool vis[maxn];
int dis[maxn];
int temp;
const int threshold = 15000000;
bool SPFA(int node)
{
	if (temp >= threshold) return false;
	vis[node] = true;
	wander(GDC, node)
	{
		if (temp >= threshold) return false;
		temp++;
		DEF(GDC);
		if (dis[node] + cost < dis[to])
		{
			dis[to] = dis[node] + cost;
			if (vis[to] || SPFA(to))
				return true;
		}
	}
	vis[node] = false;
	return false;
}
bool check(int s)
{
	if (s == n + 1) return true;
	GDC.clear();
	for (int i = 1; i <= n; i++)
	{
		GDC.addEdge(i - 1, i, 1);
		GDC.addEdge(i, i - 1, 0);
	}
	GDC.addEdge(0, n, s);
	GDC.addEdge(n, 0, -s);
	for (int i = 1; i <= n; i++)
		if (limita[i] != -1)
		{
			int left = dfn[i] - 1;
			int right = end[i];
			GDC.addEdge(right, left, -limita[i]);
		}
	for (int i = 1; i <= n; i++)
		if (limitb[i] != -1)
		{
			int left = dfn[i] - 1;
			int right = end[i];
			GDC.addEdge(left, right, s - limitb[i]);
		}
	memset(vis, 0, sizeof(int) * (n + 1));
	memset(dis, 0, sizeof(int) * (n + 1));
	static int order[maxn];
	if (order[0] != n + 1)
	{
		order[0] = 0;
		for (int i = 0; i <= n; i++)
			order[++order[0]] = i;
	}
	std::random_shuffle(order + 1, order + 1 + order[0]);
	temp = 0;
	for (int i = 1; i <= order[0]; i++)
		if (SPFA(order[i]))
			return false;
	return true;
}
void work()
{
	int l = 0, r = n + 1;
	while (r - l > 0)
	{
		int mid = l + ((r - l) >> 1);
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	if (r == n + 1)
		printOut(-1);
	else
		printOut(r);
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
		stamp = 0;
		DFS(1, 0);
		bool bOk = true;
		memset(limita, -1, sizeof(int) * (n + 1));
		memset(limitb, -1, sizeof(int) * (n + 1));
		a = readIn();
		for (int i = 1; i <= a; i++)
		{
			ra[i] = readIn();
			sa[i] = readIn();
			if (end[ra[i]] - dfn[ra[i]] + 1 < sa[i])
				bOk = false;
			limita[ra[i]] = (limita[ra[i]] == -1 ? sa[i] : std::max(limita[ra[i]], sa[i]));
		}
		b = readIn();
		for (int i = 1; i <= b; i++)
		{
			rb[i] = readIn();
			sb[i] = readIn();
			if (n - (end[rb[i]] - dfn[rb[i]] + 1) < sb[i])
				bOk = false;
			limitb[rb[i]] = (limitb[rb[i]] == -1 ? sb[i] : std::max(limitb[rb[i]], sb[i]));
		}
		if (!bOk)
		{
			printOut(-1);
			continue;
		}

		if (n <= 17)
			RunInstance(brute);
		else
			RunInstance(work);
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