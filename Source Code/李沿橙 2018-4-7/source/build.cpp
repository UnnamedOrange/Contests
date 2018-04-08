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
}

const int maxn = 2005;
int n, k;
int parent[maxn];
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn];
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
	static const int maxN = 55;
	int depth[maxN];
	void DFS(int node)
	{
		depth[node] = depth[parent[node]] + 1;
		wander(G, node)
		{
			DEF(G);
			DFS(to);
		}
	}
	int GetDis(int u, int v)
	{
		int ret = 0;
		if (depth[u] < depth[v]) std::swap(u, v);
		while (depth[u] != depth[v])
		{
			ret++;
			u = parent[u];
		}
		while (u != v)
		{
			ret += 2;
			u = parent[u];
			v = parent[v];
		}
		return ret;
	}
	brute()
	{
		depth[0] = 0;
		DFS(1);

		int ans = 0;
		for (int s = 1; s <= n; s++)
		{
			for (int t = s; t <= n; t++)
			{
				int maxVal = 0;
				for (int i = 1; i <= n; i++)
				{
					for (int j = i + 1; j <= n; j++)
					{
						int temp = GetDis(i, j);
						temp = std::min(temp, std::min(GetDis(i, s) + GetDis(t, j), GetDis(i, t) + GetDis(s, j)));
						maxVal = std::max(maxVal, temp);
					}
				}
				if (maxVal <= k) ans++;
			}
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	k = readIn();
	for (int i = 2; i <= n; i++)
		parent[i] = readIn() + 1; // code plus 1
	for (int i = 2; i <= n; i++)
		G.addEdge(parent[i], i);

	if (n <= 50)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("build.in", "r", stdin);
	freopen("build.out", "w", stdout);
#endif
	run();
	return 0;
}