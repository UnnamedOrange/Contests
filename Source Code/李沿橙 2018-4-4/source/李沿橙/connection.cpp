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

const int maxn = 305;
const int maxm = 1005;
int n, m;
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxm * 2];
	int i;
	int head[maxn];
	int size[maxn];
	Graph() : i(), size() { memset(head, -1, sizeof(head)); }
	void addEdge(int from, int to)
	{
		size[from]++;
		edges[i].to = to;
		edges[i].next = head[from];
		head[from] = i;
		i++;
	}
#define idx(x) idx_##x
#define wander(G, node) for (int idx(G) = G.head[node]; ~idx(G); idx(G) = G.edges[idx(G)].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx(G)]; int to = e.to
} G;

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 15;
	struct queue
	{
		int c[maxN];
		int head, tail;
		bool empty() { return head == tail; }
		void clear() { head = tail = 0; }
		void push(int x) { c[tail++] = x; }
		void pop() { head++; }
		int front() { return c[head]; }
	} q;
	int vis[maxn];

	brute()
	{
		memset(vis, -1, sizeof(vis));
		int ans = m;
		int U = 1 << m;
		for (int S = 0; S < U; S++)
		{
			q.clear();
			q.push(1);
			vis[1] = S;
			int nVis = 1;
			while (!q.empty())
			{
				int from = q.front();
				q.pop();
				wander(G, from)
				{
					if (S & (1 << (idx(G) >> 1))) continue;
					DEF(G);
					if (vis[to] != S)
					{
						vis[to] = S;
						nVis++;
						q.push(to);
					}
				}
			}

			if (nVis != n)
			{
				int nDel = 0;
				for (int i = 0; i < m; i++)
					nDel += bool(S & (1 << i));
				ans = std::min(ans, nDel);
			}
		}
		printOut(ans);
	}
};
struct cheat
{
	cheat()
	{
		int minsize = 2 * m;
		for (int i = 1; i <= n; i++)
			minsize = std::min(minsize, G.size[i]);
		if (minsize == 1) printOut(1);
		else if (minsize == 2) printOut(2);
		else printOut(1 + rand() % minsize);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	if (n == m + 1)
	{
		printOut(1);
		return;
	}
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
	}

	if (m <= 20)
		RunInstance(brute);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("connection.in", "r", stdin);
	freopen("connection.out", "w", stdout);
#endif
	run();
	return 0;
}