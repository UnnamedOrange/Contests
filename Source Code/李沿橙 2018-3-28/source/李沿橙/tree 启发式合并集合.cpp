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
int n;
int parent[maxn];
int val[maxn];
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn];
	int i;
	int head[maxn];
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

int idx[maxn];
std::multiset<int> S[maxn];
void merge(int des, int src)
{
	bool swap = false;
	if (S[idx[src]].size() > S[idx[des]].size())
	{
		swap = true;
		std::swap(src, des);
	}
	std::multiset<int>& cnt = S[idx[des]];
	for (std::multiset<int>::iterator it = S[idx[src]].begin(), end = S[idx[src]].end(); it != end; it++)
		cnt.insert(*it);
	S[idx[src]].clear();
	if (swap) std::swap(idx[src], idx[des]);
}
int BFS()
{
	static int q[maxn];
	int head = 0, tail = 0;
	q[tail++] = 1;
	while (head != tail)
	{
		int from = q[head];
		head++;
		wander(G, from)
		{
			DEF(G);
			q[tail++] = to;
		}
	}

	for (int i = 1; i <= n; i++) idx[i] = i;
	for (int i = tail - 1; ~i; i--)
	{
		int node = q[i];
		std::multiset<int>& cnt = S[idx[node]];
		std::multiset<int>::iterator it;
		if ((it = S[idx[node]].lower_bound(val[node])) != cnt.end())
			cnt.erase(it);
		cnt.insert(val[node]);
		if (i) merge(parent[node], node);
	}
	return S[idx[1]].size();
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		val[i] = readIn();
		parent[i] = readIn();
	}
	for (int i = 2; i <= n; i++)
		G.addEdge(parent[i], i);

	printOut(BFS());
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