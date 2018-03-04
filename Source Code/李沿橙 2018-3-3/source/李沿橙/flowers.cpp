#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
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
#include <cassert>
#include <cctype>
#include <climits>
typedef long long LL;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	if (!(ch == '-' || std::isdigit(ch))) ch = getchar();
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

const int mod = 998244353;
const int maxn = int(8e4) + 5;
int n, m;
int a[maxn];
int p1 = true, p2 = true;
struct Graph
{
	struct Edge
	{
		int to;
		int next;
	} edges[maxn * 2];
	int head[maxn];
	int size[maxn];
	int i;
	Graph() : i(), size()
	{
		memset(head, -1, sizeof(head));
	}
	void addEdge(int from, int to)
	{
		size[from]++;
		edges[i].to = to;
		edges[i].next = from;
		head[from] = i;
		i++;
	}
#define wander(G, node) for (int idx_##G = G.head[node]; ~idx_##G; idx_##G = G.edges[idx_##G].next)
#define DEF(G) const Graph::Edge& e = G.edges[idx_##G]; int to = e.to
} G;

struct FNTT
{
	static int power(int x, int y)
	{
		int ret = 1;
		while (y)
		{
			if (y & 1) ret = (long long)ret * x % mod;
			x = (long long)x * x % mod;
			y >>= 1;
		}
		return ret;
	}
	const int g = 3;
	const int limit = 23;
	const int base = 119;
	int n, logn;
	inline int revbit(int x)
	{
		int ret = 0;
		for (int i = 0; i < logn; i++, x >>= 1)
			ret = (ret << 1) | (bool)(x & 1);
		return ret;
	}
	FNTT(int* a, int logn, int sig) : n(1 << logn), logn(logn)
	{
		for (int i = 0; i < n; i++)
		{
			int t = revbit(i);
			if (i < t) std::swap(a[i], a[t]);
		}
		for (int i = 1; i <= logn; i++)
		{
			int S = 1 << i;
			int half = S >> 1;
			int g1 = power(g, base * (1 << (23 - i)));
			if (!~sig) g1 = power(g1, mod - 2);
			for (int j = 0; j < n; j += S)
			{
				int g = 1;
				int* A = a + j;
				for (int k = 0; k < half; k++)
				{
					int t = (long long)A[k + half] * g % mod;
					A[k + half] = (A[k] - t) % mod;
					A[k] = (A[k] + t) % mod;
					g = (long long)g * g1 % mod;
				}
			}
		}
		for (int i = 0; i < n; i++)
			if (a[i] < 0) a[i] += mod;
	}
};
struct NTT : private FNTT
{
	NTT(int* a, int logn) : FNTT(a, logn, 1) {}
};
struct INTT : private FNTT
{
	INTT(int* a, int logn) : FNTT(a, logn, -1)
	{
		int n = 1 << logn;
		int inv = FNTT::power(n, mod - 2);
		for (int i = 0; i < n; i++)
			a[i] = (long long)a[i] * inv % mod;
	}
};


#define RunInstance(x) delete new x
struct subtask4
{
	struct Area
	{
		int l;
		int r;
		std::vector<int> poly;
	};
	std::vector<Area> topo;

	void BFS(int l, int r)
	{

	}

};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		G.addEdge(from, to);
		G.addEdge(to, from);
		if (!(from == i && to == i + 1)) p1 = false;
		if (!(from == 1 && to == i + 1)) p2 = false;
	}

	if (p1)
		RunInstance(subtask4);
}

int main()
{
#ifndef LOCAL
	freopen("flowers.in", "r", stdin);
	freopen("flowers.out", "w", stdout);
#endif
	run();
	return 0;
}