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

const int maxn = int(1e5) + 5;
int n, m;
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn * 2];
	int i;
	int head[maxn];
	int size[maxn];
	Graph() : i(), size()
	{
		memset(head, -1, sizeof(head));
	}
	void addEdge(int from, int to)
	{
		size[from]++;
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define wander(G, node) for (int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx_##G]; int to = e.to
} G, G2;

int stamp;
int dfn[maxn];
int low[maxn];
int belong[maxn];
bool inStack[maxn];
int stack[maxn];
int N;
void Tarjan(int node, int parent)
{
	low[node] = dfn[node] = ++stamp;
	stack[++stack[0]] = node;
	inStack[node] = true;
	wander(G, node)
	{
		DEF(G);
		if (to == parent) continue;
		if (!dfn[to])
		{
			Tarjan(to, node);
			low[node] = std::min(low[node], low[to]);
		}
		else if (inStack[to])
			low[node] = std::min(low[node], dfn[to]);
	}
	if (low[node] == dfn[node])
	{
		N++;
		int top;
		do
		{
			top = stack[stack[0]--];
			inStack[top] = false;
			belong[top] = N;
		} while (top != node);
	}
}

int ans;
int l;
int d;
bool vis[maxn];
int f[maxn];
void DP(int node, int parent)
{
	l += G2.size[node] <= 1;
	f[node] = 1;
	vis[node] = true;
	int major = 0;
	int minor = 0;
	wander(G2, node)
	{
		DEF(G2);
		if (to == parent) continue;
		DP(to, node);
		if (f[to] > minor)
		{
			if (f[to] > major)
			{
				minor = major;
				major = f[to];
			}
			else minor = f[to];
		}
		f[node] = std::max(f[node], f[to] + 1);
	}
	d = std::max(d, major + minor + 1);
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			Tarjan(i, 0);

	for (int i = 1; i <= n; i++)
	{
		wander(G, i)
		{
			DEF(G);
			if (belong[i] != belong[to])
				G2.addEdge(belong[i], belong[to]);
		}
	}

	int ans = n - 1;
	for (int i = 1; i <= N; i++)
	{
		if (!vis[i])
		{
			d = 0;
			l = 0;
			DP(i, 0);
			if (d != 1)
				ans -= d + l - 2;
			else
				ans--;
			ans++;
		}
	}
	printOut(ans);
}

int main()
{
#ifndef LOCAL
	freopen("merge.in", "r", stdin);
	freopen("merge.out", "w", stdout);
#endif
	run();
	return 0;
}