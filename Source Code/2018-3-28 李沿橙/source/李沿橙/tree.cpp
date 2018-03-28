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
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = int(1e5) + 5;
int n;
int t1 = true;
int parent[maxn];
int val[maxn];
int bound;
int disc[maxn];
void discretize()
{
	memcpy(disc, val, sizeof(disc));
	std::sort(disc + 1, disc + 1 + n);
	bound = std::unique(disc + 1, disc + 1 + n) - (disc + 1);
	for (int i = 1; i <= n; i++)
		val[i] = std::lower_bound(disc + 1, disc + 1 + bound, val[i]) - disc;
}
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

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = int(2e3) + 5;
	int f[maxN][maxN]; // 结点 i 对应的子树中选择的最大的结点的权值恰好为 j 时的答案 

	int buf[maxN];
	int temp[maxN];
	void DFS(int node)
	{
		f[node][val[node]] = 1;
		wander(G, node)
		{
			DEF(G);
			DFS(to);
		}
		buf[0] = 0;
		wander(G, node)
		{
			DEF(G);
			buf[++buf[0]] = to;
			temp[to] = 0;
		}
		int sum = 0;
		for (int i = 1; i < val[node]; i++)
		{
			bool bOk = false;
			for (int j = 1; j <= buf[0]; j++)
			{
				int to = buf[j];
				if (!~f[to][i]) continue;
				bOk = true;
				if (temp[to] < f[to][i])
				{
					sum += f[to][i] - temp[to];
					temp[to] = f[to][i];
				}
			}
			if (bOk) f[node][i] = sum;
		}
		int limit = sum;
		f[node][val[node]] = limit + 1;
		for (int i = val[node]; i <= bound; i++)
		{
			bool bOk = false;
			for (int j = 1; j <= buf[0]; j++)
			{
				int to = buf[j];
				if (!~f[to][i]) continue;
				bOk = true;
				if (temp[to] < f[to][i])
				{
					sum += f[to][i] - temp[to];
					temp[to] = f[to][i];
				}
			}
			if (bOk) f[node][i] = std::max(f[node][i], sum);
		}
	}

	brute()
	{
		memset(f, -1, sizeof(f));
		DFS(1);
		int ans = 0;
		for (int i = 1; i <= bound; i++)
			ans = std::max(ans, f[1][i]);
		printOut(ans);
	}
};
struct cheat
{
	std::vector<int> vec;
	cheat()
	{
		for (int i = 1; i <= n; i++)
		{
			if (vec.empty() || val[i] < vec.back()) vec.push_back(val[i]);
			*std::lower_bound(vec.begin(), vec.end(), val[i], std::greater<int>()) = val[i];
		}
		printOut(vec.size());
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		val[i] = readIn();
		parent[i] = readIn();
		if (parent[i] != i - 1) t1 = false;
	}
	for (int i = 2; i <= n; i++)
		G.addEdge(parent[i], i);
	discretize();

	if (t1)
		RunInstance(cheat);
	else if (n <= 2000)
		RunInstance(brute);
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