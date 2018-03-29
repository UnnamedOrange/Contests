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
	int a = 0;
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
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = int(2e5) + 5;
int n;

struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn * 2];
	int head[maxn];
	int i;
	Graph() : i() { memset(head, -1, sizeof(head)); }
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
int a[maxn];

int parent[maxn];
int q[maxn];
int head, tail;
void BFS()
{
	q[tail++] = 1;
	while (head != tail)
	{
		int from = q[head];
		head++;
		wander(G, from)
		{
			DEF(G);
			if (to == parent[from]) continue;
			q[tail++] = to;
			parent[to] = from;
		}
	}
}

std::multiset<int, std::greater<int> > f[maxn];
int idx[maxn];
void merge(int des, int src)
{
	if (f[idx[des]].size() < f[idx[src]].size())
		std::swap(idx[des], idx[src]);
	std::multiset<int, std::greater<int> >& cnt = f[idx[des]];
	std::multiset<int, std::greater<int> >& pre = f[idx[src]];
	for (std::multiset<int, std::greater<int> >::iterator it = pre.begin(); it != pre.end(); it++)
		cnt.insert(*it);
	pre.clear();
}
int solve()
{
	for (int i = 1; i <= n; i++)
		idx[i] = i;
	for (int i = tail - 1; ~i; i--)
	{
		int node = q[i];
		std::multiset<int, std::greater<int> >& cnt = f[idx[node]];
		std::multiset<int, std::greater<int> >::iterator it = cnt.upper_bound(a[node]);
		if (it != cnt.end()) cnt.erase(it);
		cnt.insert(a[node]);

		if (i) merge(parent[node], node);
	}
	return n - f[idx[1]].size();
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
	}
	BFS();
	printOut(solve());
}

int main()
{
#ifndef LOCAL
	freopen("simple.in", "r", stdin);
	freopen("simple.out", "w", stdout);
#endif
	run();
	return 0;
}