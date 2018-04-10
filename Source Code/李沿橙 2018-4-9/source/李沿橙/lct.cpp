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

const LL INF = (~(LL(1) << (sizeof(LL) * 8 - 1))) >> 1;
const int maxn = int(3e5) + 5;
int n, K;
struct Edge
{
	int to;
	int cost;
	Edge() {}
	Edge(int to, int cost) : to(to), cost(cost) {}
};
std::vector<Edge> G[maxn];

template<typename T, typename R>
void maxeq(T& a, const R& b) { a = a < b ? b : a; }

#define RunInstance(x) delete new x
struct cheat
{
	LL ans;
	LL f[maxn];

	void DFS(int node, int parent)
	{
		f[node] = 0;
		LL major = 0;
		LL minor = 0;
		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = G[node][i];
			if (e.to == parent) continue;
			DFS(e.to, node);

			LL t = f[e.to] + e.cost;
			f[node] = std::max(f[node], t);
			if (t > minor)
			{
				if (t > major)
				{
					minor = major;
					major = t;
				}
				else
					minor = t;
			}
		}
		ans = std::max(ans, major + minor);
	}

	cheat() : ans()
	{
		DFS(1, 0);
		printOut(ans);
	}
};
struct brute
{
	static const int maxk = 105;
	int size[maxn];
	LL f[3][maxn][maxk];
	LL non[maxk], one[maxk], two[maxk];
	void DFS(int node, int parent)
	{
		size[node] = 1;
		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = G[node][i];
			int to = e.to;
			if (to == parent) continue;
			DFS(to, node);
		}

		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = G[node][i];
			int to = e.to;
			if (to == parent) continue;
			LL cost = e.cost;

			for (int i = 0; i <= K; i++)
				non[i] = one[i] = two[i] = -INF; // 额外开一个大小为 k 的数组用于临时转移
			int bound = std::min(K, size[node]); // 首先确定本次转移的最大状态量
			for (int x = 0; x <= bound; x++)
			{
				int r = std::min(K - x, size[to]); // 确定子结点的最大状态量
				for (int y = 0; y <= r; y++)
				{
					LL t = -INF;
					maxeq(t, f[0][to][y]);
					maxeq(t, f[1][to][y]);
					maxeq(t, f[2][to][y]);
					maxeq(non[x + y], f[0][node][x] + t);
					maxeq(one[x + y], f[1][node][x] + t);
					maxeq(two[x + y], f[2][node][x] + t);

					maxeq(non[x + y - 1], f[0][node][x] + tf);
				}
			}
		}
	}

	brute()
	{
		DFS(1, 0);
	}
};

void run()
{
	n = readIn();
	K = readIn();
	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		int cost = readIn();
		G[from].push_back(Edge(to, cost));
		G[to].push_back(Edge(from, cost));
	}

	if (K == 0)
		RunInstance(cheat);
	else if (K <= 100)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("lct.in", "r", stdin);
	freopen("lct.out", "w", stdout);
#endif
	run();
	return 0;
}