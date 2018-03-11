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
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int mod = 998244353; 
const int maxn = int(1e5) + 5;
int n, m, k;

struct Graph
{
	struct Edge
	{
		int to;
		int cost;
		int next;
	} edges[maxn * 2];
	int head[maxn];
	int i;
	Graph() : i()
	{
		memset(head, -1, sizeof(head));
	}
	void addEdge(int from, int to, int cost)
	{
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define wander(G, node) for (int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx_##G]; int to = e.to; int cost = e.cost
} G;

#define RunInstance(x) delete new x
struct cheat
{
	bool vis[maxn];
	int size[maxn];
	
	void DFS1(int node, int parent)
	{
		buf[++buf[0]] = depth[node];
		size[node] = 1;
		wander(G, node)
		{
			DEF(G);
			if(to == parent || vis[to]) continue;
			DFS1(to, node);
			size[node] += size[to];
		}
	}
	int GetRoot(int node, int parent, int s)
	{
		wander(G, node)
		{
			DEF(G);
			if(to == parent || vis[to]) continue;
			if(size[to] > s / 2)
				return GetRoot(to, node, s);
		}
		return node;
	}
	LL depth[maxn];
	LL buf[maxn];
	void DFS2(int node, int parent)
	{
		buf[++buf[0]] = depth[node];
		wander(G, node)
		{
			DEF(G);
			if(to == parent || vis[to]) continue;
			depth[to] = depth[node] + cost;
			DFS2(to, node);
		}
	}
	int ans;
	void solve(int node, int c)
	{
		depth[node] = 0;
		buf[0] = 0;
		DFS1(node, 0);
		if(node != 1)
		{
			std::sort(buf + 1, buf + 1 + buf[0]);
			int l = 1, r = buf[0];
			
		}
		node = GetRoot(node, 0, size[node]);
		vis[node] = true;
		
		depth[node] = 0;
		buf[0] = 0;
		DFS2(node, 0);
		
		
		wander(G, node)
		{
			DEF(G);
			if(vis[to]) continue;
			solve(to, cost);
		}
	}
		
	cheat() : vis(), ans()
	{
		solve(1, 0);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for(int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		int cost = readIn();
		G.addEdge(from, to, cost);
		G.addEdge(to, from, cost);
	}
	
	if (m == 2)
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("party.in", "r", stdin);
	freopen("party.out", "w", stdout);
#endif
	run();
	return 0;
}
