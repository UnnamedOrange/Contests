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
#define wander(G, node) for (int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx_##G]; int to = e.to
} G;

int f[maxn];
int buffer[maxn];
void DFS1(int node, int parent)
{
	wander(G, node)
	{
		DEF(G);
		if (to == parent) continue;
		DFS1(to, node);
	}
	buffer[0] = 0;
	wander(G, node)
	{
		DEF(G);
		if (to == parent) continue;
		buffer[++buffer[0]] = f[to];
	}
	std::sort(buffer + 1, buffer + 1 + buffer[0], std::greater<int>());
	f[node] = 0;
	for (int i = 1; i <= buffer[0]; i++)
		f[node] = std::max(f[node], buffer[i] + i);
}
bool comp(const int& a, const int& b)
{
	return f[a] > f[b];
}
int ans;
void DFS2(int node, int parent)
{
	buffer[0] = 0;
	int maxVal = 0;
	int son = 0;
	wander(G, node)
	{
		DEF(G);
		buffer[++buffer[0]] = to;

		if (to != parent && f[to] > maxVal)
		{
			maxVal = f[to];
			son = to;
		}
	}
	std::sort(buffer + 1, buffer + 1 + buffer[0], comp);
	int v = 0;
	int t = 1;
	for (int i = 1; i <= buffer[0]; i++)
		v = std::max(v, f[buffer[i]] + t++);
	ans = std::min(ans, v);

	if (son)
	{
		f[node] = 0;
		t = 1;
		for (int i = 1; i <= buffer[0]; i++)
			if (buffer[i] != son)
				f[node] = std::max(f[node], f[buffer[i]] + t++);
		DFS2(son, node);
	}
}
void test1()
{
	DFS1(1, 0);
	ans = f[1];

	buffer[0] = 0;
	wander(G, 1)
	{
		DEF(G);
		buffer[++buffer[0]] = to;
	}
	std::sort(buffer + 1, buffer + 1 + n, comp);
	int to = buffer[1];
	int t = 1;
	f[1] = 0;
	for (int i = 1; i <= buffer[0]; i++)
		if (buffer[i] != to)
			f[1] = std::max(f[1], f[buffer[i]] + t++);
	DFS2(to, 1);
	printOut(ans);
}

int p[maxn];
void DFS3(int node)
{
	wander(G, node)
	{
		DEF(G);
		if (to == p[node]) continue;
		p[to] = node;
		DFS3(to);
	}
}
int seq[maxn];
int code[maxn];
int calc(int node, int parent, int s, bool isA)
{
	wander(G, node)
	{
		DEF(G);
		if (to == parent) continue;
		if (code[to])
		{
			if (isA && code[to] > s) continue;
			if (!isA && code[to] <= s) continue;
		}
		calc(to, node, s, isA);
	}
	buffer[0] = 0;
	wander(G, node)
	{
		DEF(G);
		if (to == parent) continue;
		if (code[to])
		{
			if (isA && code[to] > s) continue;
			if (!isA && code[to] <= s) continue;
		}
		buffer[++buffer[0]] = f[to];
	}
	std::sort(buffer + 1, buffer + 1 + buffer[0], std::greater<int>());
	f[node] = 0;
	for (int i = 1; i <= buffer[0]; i++)
		f[node] = std::max(f[node], buffer[i] + i);
	return f[node];
}

void test2()
{
	DFS3(a);
	seq[0] = 0;
	int cnt = b;
	while (cnt)
	{
		seq[++seq[0]] = cnt;
		cnt = p[cnt];
	}
	std::reverse(seq + 1, seq + 1 + seq[0]);
	for (int i = 1; i <= seq[0]; i++)
		code[seq[i]] = i;

	int l = 1, r = seq[0];
	int t1, t2;
	while (r - l > 1)
	{
		int mid = l + ((r - l) >> 1);
		if ((t1 = calc(a, 0, mid, true)) < (t2 = calc(b, 0, mid, false)))
			l = mid;
		else
			r = mid;
	}
	printOut(std::min(
		std::max(calc(a, 0, l, true), calc(b, 0, l, false)),
		l + 1 != seq[0] ? std::max(calc(a, 0, l + 1, true), calc(b, 0, l + 1, false)) : 0
	));
}

void run()
{
	n = readIn();
	a = readIn();
	b = readIn();
	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
	}
	test1();
	test2();
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