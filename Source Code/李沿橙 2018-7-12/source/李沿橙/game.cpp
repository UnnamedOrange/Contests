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
typedef LL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
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
	putchar('\n');
}

const int maxn = 20005;
int n;
enum { ROAD = 1, RAIL };
struct Edge
{
	int type;
	int to;
	Edge() {}
	Edge(int type, int to) : type(type), to(to) {}
};
std::vector<Edge> edges;
std::vector<std::vector<int> > G;
int a[maxn * 2], b[maxn * 2], c[maxn * 2];

#define RunInstance(x) delete new x
struct brute1
{
	int sel[maxn];
	LL ans;
	LL accum;
	void DFS(int node, int road, int rail)
	{
		if (node >= n)
		{
			accum += (LL)c[node] * (a[node] + road) * (b[node] + rail);
			return;
		}
		for (int i = 0; i < G[node].size(); i++)
		{
			int idx = G[node][i];
			const Edge& e = edges[idx];
			if (sel[idx])
				DFS(e.to, road, rail);
			else
			{
				if (e.type == ROAD)
					DFS(e.to, road + 1, rail);
				else if (e.type == RAIL)
					DFS(e.to, road, rail + 1);
			}
		}
	}
	void search(int depth, int begin)
	{
		if (G.size() - begin < n - 1 - depth)
			return;
		if (depth == n - 1)
		{
			accum = 0;
			DFS(1, 0, 0);
			ans = std::min(ans, accum);
			return;
		}
		for (int i = begin; i < G.size(); i++)
		{
			sel[i] = true;
			search(depth + 1, i + 1);
			sel[i] = false;
		}
	}
	brute1() : sel(), ans(LLONG_MAX)
	{
		search(0, 0);
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	G.resize(2 * n);
	for (int i = 1; i < n; i++)
	{
		int road = readIn();
		int rail = readIn();
		if (road < 0) road = n - 1 - road;
		if (rail < 0) rail = n - 1 - rail;
		edges.push_back(Edge(ROAD, road));
		G[i].push_back(edges.size() - 1);
		edges.push_back(Edge(RAIL, rail));
		G[i].push_back(edges.size() - 1);
	}
	for (int i = n, to = n * 2 - 1; i <= to; i++)
	{
		a[i] = readIn();
		b[i] = readIn();
		c[i] = readIn();
	}

	if (n <= 12)
		RunInstance(brute1);
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