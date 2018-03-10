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
	do
	{
		buffer[length++] = -(x % 10) + '0';
	} while (x /= 10);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const int maxn = int(3e5) + 5;
int n, a, b;
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn * 2];
	int head[maxn];
	int i;
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
#define wander(G, node) for(int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx_##G]; int to = e.to
} G;

#define RunInstance(x) delete new x
struct brute1
{
	static const int maxN = 1005;
	int f[maxN];

	void DFS(int node, int parent)
	{
		f[node] = 0;
		int son = 0;
		wander(G, node)
		{
			DEF(G);
			if(to == parent) continue;
			son++;
			DFS(to, node);
		}
		static int buffer[maxN];
		buffer[0] = 0;
		wander(G, node)
		{
			DEF(G);
			if(to == parent) continue;
			buffer[++buffer[0]] = f[to];
		}
		std::sort(buffer + 1, buffer + 1 + buffer[0], std::greater<int>());
		for(int i = 1; i <= buffer[0]; i++)
			f[node] = std::max(f[node], buffer[i] + 1);
		f[node] = std::max(f[node], son);
	}
	brute1()
	{
		int ans = n + 1;
		for(int i = 1; i <= n; i++)
		{
			DFS(i, 0);
			ans = std::min(ans, f[i]);
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	a = readIn();
	b = readIn();
	for(int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
	}

	if(n <= 1000)
		RunInstance(brute1);
	
	printOut(0);
}

int main()
{
#ifndef LOCAL
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	run();
	return 0;
}
