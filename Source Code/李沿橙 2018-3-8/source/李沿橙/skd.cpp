#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
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
typedef long long INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
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

const int maxn = 3005;
int n, m, k;
struct Graph
{
	struct Edge
	{
		int to;
		LL cost;
		int next;
	} edges[maxn * 2];
	int head[maxn];
	int i;
	Graph() : i()
	{
		memset(head, -1, sizeof(head));
	}
	void addEdge(int from, int to, LL cost)
	{
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define wander(G, node) for (int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx_##G]; int to = e.to; LL cost = e.cost
} G;

LL costs[maxn];

struct Node
{
	int idx;
	LL dis;
	Node() {}
	Node(int idx, LL dis) : idx(idx), dis(dis) {}
	bool operator> (const Node& b) const
	{
		return dis > b.dis;
	}
};

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		LL cost = readIn();
		costs[i] = cost;
		G.addEdge(from, to, cost);
		G.addEdge(to, from, cost);
	}
	std::sort(costs + 1, costs + 1 + m);
	m = std::unique(costs + 1, costs + 1 + m) - (costs + 1);

	LL ans;
	std::memset(&ans, 0x3f, sizeof(ans));
	for (int i = 0; i <= m; i++)
	{
		static LL dis[maxn];
		memset(dis, 0x3f, sizeof(dis));
		dis[1] = 0;
		std::priority_queue<Node, std::vector<Node>, std::greater<Node> > pq;
		pq.push(Node(1, 0));
		while (!pq.empty())
		{
			Node t = pq.top();
			pq.pop();
			if (t.dis > dis[t.idx]) continue;
			wander(G, t.idx)
			{
				DEF(G);
				cost = (cost >= costs[i]) ? cost - costs[i] : 0;
				if (dis[t.idx] + cost < dis[to])
				{
					dis[to] = dis[t.idx] + cost;
					pq.push(Node(to, dis[to]));
				}
			}
		}
		ans = std::min(ans, dis[n] + costs[i] * k);
	}
	printOut(ans);
}

int main()
{
#ifndef LOCAL
	freopen("skd.in", "r", stdin);
	freopen("skd.out", "w", stdout);
#endif
	run();
	return 0;
}