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
typedef long long INT_PUT;
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
	putchar('\n');
}

const int maxn = int(2e5) + 5;
int n, k;

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
		Edge& e = edges[i];
		e.to = to;
		e.cost = cost;
		e.next = head[from];
		head[from] = i;
		i++;
	}
#define wander(G, node) for (int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx_##G]; int to = e.to; int cost = e.cost
} G;

#define RunInstance(x) delete new x
struct work
{
	bool vis[maxn];

	int size[maxn];
	void DFS1(int node, int parent)
	{
		size[node] = 1;
		wander(G, node)
		{
			DEF(G);
			if (to == parent || vis[to]) continue;
			DFS1(to, node);
			size[node] += size[to];
		}
	}
	int GetRoot(int node, int parent, int s)
	{
		wander(G, node)
		{
			DEF(G);
			if (to == parent || vis[to]) continue;
			if (size[to] > (s >> 1))
				return GetRoot(to, node, s);
		}
		return node;
	}
	LL depth[maxn];
	struct Node
	{
		int idx;
		int belong;
		LL depth;
		Node() {}
		Node(int idx, int belong, LL depth) : idx(idx), belong(belong), depth(depth) {}
		bool operator< (const Node& b) const
		{
			if (belong != b.belong) return belong < b.belong;
			return depth > b.depth;
		}
	};
	std::vector<Node> vset[maxn];
	std::vector<int> begin[maxn];
	void DFS2(int node, int parent, int belong, int center)
	{
		vset[center].push_back(Node(node, belong, depth[node]));
		wander(G, node)
		{
			DEF(G);
			if (to == parent || vis[to]) continue;
			depth[to] = depth[node] + cost;
			DFS2(to, node, belong ? belong : to, center);
		}
	}

	int deal[maxn];
	void solve(int node)
	{
		DFS1(node, 0);
		vset[node].reserve(size[node]);
		node = GetRoot(node, 0, size[node]);
		vis[node] = true;

		depth[node] = 0;
		DFS2(node, 0, 0, node);
		std::sort(vset[node].begin(), vset[node].end());
		std::vector<int>& b = begin[node];
		std::vector<Node>& t = vset[node];
		int pre = 0;
		for (int i = 1; i < t.size(); i++)
			if (t[i].belong != pre)
			{
				b.push_back(i);
				pre = t[i].belong;
			}

		wander(G, node)
		{
			DEF(G);
			if (vis[to]) continue;
			solve(to);
		}
		deal[++deal[0]] = node;
	}

	LL ans[maxn];
	LL check(LL s, LL c, bool add)
	{
		LL accum = 0;
		for (int i = 1; i <= n; i++)
		{
			int node = deal[i];
			std::vector<int>& b = begin[node];
			std::vector<Node>& t = vset[node];
			for (int j = -1; j < int(b.size()); j++)
			{
				for (int e = j + 1; e < b.size(); e++)
				{
					int pos1 = (j == -1 ? 0 : b[j]);
					int bound1 = b[j + 1] - 1;
					int pos2 = b[e] - 1;
					int bound2 = ((e == b.size() - 1) ? t.size() - 1 : b[e + 1] - 1);
					while (pos2 + 1 <= bound2 && t[pos1].depth + t[pos2 + 1].depth >= s)
						pos2++;
					int left = b[e];
					int right = pos2;
					for (; pos1 <= bound1; pos1++)
					{
						while (pos2 >= left && t[pos1].depth + t[pos2].depth < s)
						{
							pos2--;
						}
						if (add)
						{
							for (int g = left; g <= pos2; g++)
							{
								ans[++ans[0]] = t[pos1].depth + t[g].depth;
								if (ans[0] >= k) return 0;
							}
						}
						accum += pos2 - left + 1;
						if (!add && accum >= c) return accum;
					}
				}
			}
		}
		return accum;
	}

	work() : vis()
	{
		deal[0] = 0;
		solve(1);

		std::reverse(deal + 1, deal + 1 + deal[0]);
		int L;
		L = INT_MAX;
		LL sum = 0;
		for (int i = 1; i <= n; i++)
			wander(G, i)
		{
			DEF(G);
			L = std::min(L, cost);
			sum += cost;
		}
		sum >>= 1;
		LL l = L, r = sum + 1;
		while (r - l > 1)
		{
			LL mid = l + ((r - l) >> 1);
			if (check(mid, k, false) < k)
				r = mid;
			else
				l = mid;
		}

		ans[0] = 0;
		check(l, k, true);
		std::sort(ans + 1, ans + 1 + k, std::greater<LL>());
		for (int i = 1; i <= ans[0]; i++)
			printOut(ans[i]);
	}
};

void run()
{
	n = readIn();
	k = readIn();
	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		int cost = readIn();
		G.addEdge(from, to, cost);
		G.addEdge(to, from, cost);
	}

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	run();
	return 0;
}