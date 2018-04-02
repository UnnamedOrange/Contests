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

const int maxn = 1005;
int n, m, maxc;
int c[maxn];
struct Graph
{
	struct Edge
	{
		int to;
		int cost;
		int next;
	} edges[maxn];
	int i;
	int head[maxn];
	Graph() : i() { memset(head, -1, sizeof(head)); }
	void addEdge(int from, int to, int cost)
	{
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(G) idx_##G
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to; int cost = e.cost
} G;

#define RunInstance(x) delete new x
struct brute
{
	int rect[maxn][maxn];

	brute()
	{
		memset(rect, -1, sizeof(rect));
		for (int i = 0; i <= n; i++)
		{
			wander(G, i)
			{
				DEF(G);
				rect[i][to] = cost;
			}
		}

		int INF;
		memset(&INF, 0x3f, sizeof(INF));
		int ans = INF;
		int U = 1 << maxc;
		for (int S = 0; S < U; S++)
		{
			bool bOk = true;
			int cnt = 0;
			int accum = 0;
			for (int i = 1; i < n; i++)
			{
				if (S & (1 << c[i]))
				{
					if (!~rect[cnt][i])
					{
						bOk = false;
						break;
					}
					accum += rect[cnt][i];
					cnt = i;
				}
			}
			if (!bOk) continue;
			if (!~rect[cnt][n]) continue;
			accum += rect[cnt][n];
			ans = std::min(ans, accum);
		}
		printOut(ans >= INF ? -1 : ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i < n; i++)
		maxc = std::max(maxc, (c[i] = readIn() - 1) + 1);
	c[0] = c[n] = -1;
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		int cost = readIn();
		G.addEdge(from, to, cost);
	}

	if (maxc <= 10)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
#endif
	run();
	return 0;
}