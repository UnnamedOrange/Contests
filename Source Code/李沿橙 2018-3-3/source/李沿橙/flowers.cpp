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
#include <list>
#include <cassert>
#include <cctype>
#include <climits>
typedef long long LL;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	if (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const int mod = 998244353;
const int maxn = int(8e4) + 5;
int n, m;
int a[maxn];
int p1 = true, p2 = true;
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn * 2];
	int head[maxn];
	int size[maxn];
	int i;
	Graph() : i(), size()
	{
		memset(head, -1, sizeof(head));
	}
	void addEdge(int from, int to)
	{
		size[from]++;
		edges[i].to = to;
		edges[i].next = from;
		head[from] = i;
		i++;
	}
#define wander(G, node) for (int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx_##G]; int to = e.to
} G;

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 505;
	int size[maxN];
	int f[2][maxN][maxN];
	
	void DFS(int node, int parent)
	{
		size[node] = 1;
		f[0][node][0] = 1;
		f[1][node][1] = a[node];
		if(G.size[node] - (bool)parent == 0)
		{
			return;
		}
		wander(G, node)
		{
			DEF(G);
			if(e.to != parent)
				DFS(e.to, node);
			size[node] += size[e.to];
			
			for(int i = size; i >= 1; i--)
			{
				for(int j = 0; j <= i; j++)
				{
					f[0][node][i] = (f[0][node][i] + ((long long)f[0][node][i - j] * (f[0][e.to][j] + f[1][e.to][j]))) % mod;
					f[1][node][i] = (f[1][node][i] + ((long long)f[0][node][i - j])) % mod;
				}
			}
			
		}
	}
	
	brute()
	{
		memset(f, 0, sizeof(f));
		DFS(1, 0);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for(int i = 1; i <= n; i++)
		a[i] = readIn();
	
	for(int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
		if(!(from == i && to == i + 1)) p1 = false;
		if(!(from == 1 && to == i + 1)) p2 = false;
	}
	
	if(n <= 500)
		RunInstance(brute);
	else if(p1)
		RunInstance(cheat1);
	else if(p2)
		RunInstance(cheat2);
}

int main()
{
#ifndef LOCAL
	freopen("flowers.in", "r", stdin);
	freopen("flowers.out", "w", stdout);
#endif
	run();
	return 0;
}
