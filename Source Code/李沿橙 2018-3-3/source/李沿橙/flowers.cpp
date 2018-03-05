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
typedef int INT_PUT;
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

const int mod = 998244353;
const int maxn = 80005;
const int maxs = 262144 + 6;
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
	Graph() : size(), i()
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

int power(int x, int y)
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
void NTT(int* a, int logn, bool inv = false)
{
	static int rev[maxs];
	int n = 1 << logn;
	for (int i = 1; i < n; i++)
		rev[i] = ((i & 1) << (logn - 1)) | (rev[i >> 1] >> 1); // 使用线性递推，用空间换时间
	for (int i = 1; i < n; i++)
		if (i < rev[i])
			std::swap(a[i], a[rev[i]]);
	const int root = 3;
	const int base = 119;
	const int limit = 23;

	for (int i = 1; i <= logn; i++)
	{
		int S = 1 << i;
		int half = S >> 1;
		int g1 = power(root, base * (1 << (limit - i)));
		if (inv) g1 = power(g1, mod - 2);
		for (int j = 0; j < n; j += S)
		{
			int* A = a + j;
			int g = 1;
			for (int k = 0; k < half; k++)
			{
				int x = A[k];
				int y = (long long)A[k + half] * g % mod;
				A[k] = x + y < mod ? x + y : x + y - mod;
				A[k + half] = x - y < 0 ? x - y + mod : x - y;
				g = (long long)g * g1 % mod;
			}
		}
	}
	if (inv)
	{
		int t = power(n, mod - 2);
		for (int i = 0; i < n; i++)
			a[i] = (long long)a[i] * t % mod;
	}
}
struct Poly : std::vector<int>
{
	inline int times() const
	{
		return std::vector<int>::size();
	}
	Poly() : std::vector<int>(1, 0) {}
	Poly(const std::vector<int>& src) : std::vector<int>(src)
	{
		if (!std::vector<int>::size())
			std::vector<int>::push_back(0);
	}

	friend Poly operator* (const Poly&x, const Poly& y)
	{
		static int a[maxs], b[maxs];
		const int *srcA = x.data(), *srcB = y.data();
		int bound = x.times() + y.times() - 1;
		int logn = 0;
		while ((1 << logn) < bound)
			logn++;
		int n = 1 << logn;
		std::copy(srcA, srcA + x.times(), a);
		std::copy(srcB, srcB + y.times(), b);
		std::fill(a + x.times(), a + n, 0);
		std::fill(b + y.times(), b + n, 0);
		NTT(a, logn); NTT(b, logn);
		for (int i = 0; i < n; i++)
			a[i] = (long long)a[i] * b[i] % mod;
		NTT(a, logn, true);
		return std::vector<int>(a, a + bound);
	}
	friend Poly operator+ (const Poly& x, const Poly& y)
	{
		static int a[maxs];
		const int *srcA = x.data(), *srcB = y.data();
		int bound = std::max(x.times(), y.times());
		std::fill(a, a + bound, 0);
		std::copy(srcA, srcA + x.times(), a);
		for (int i = 0; i < y.times(); i++)
			a[i] = a[i] + srcB[i] < mod ? a[i] + srcB[i] : a[i] + srcB[i] - mod;
		return std::vector<int>(a, a + bound);
	}
	friend Poly operator- (const Poly& x, const Poly& y)
	{
		static int a[maxs];
		const int *srcA = x.data(), *srcB = y.data();
		int bound = std::max(x.times(), y.times());
		std::fill(a, a + bound, 0);
		std::copy(srcA, srcA + x.times(), a);
		for (int i = 0; i < y.times(); i++)
			a[i] = a[i] - srcB[i] < 0 ? a[i] - srcB[i] + mod : a[i] - srcB[i];
		return std::vector<int>(a, a + bound);
	}
};

int n, m;
int p1 = true, p2 = true;
int a[maxs];

#define RunInstance(x) delete new x
struct subtask2
{
	static const int maxN = 4005;
	Poly f[maxN];
	Poly g[maxN];

	void DFS(int node, int parent)
	{
		f[node].push_back(a[node]);
		g[node][0] = 1;
		wander(G, node)
		{
			DEF(G);
			if (to == parent) continue;
			DFS(to, node);
			f[node] = f[node] * g[to];
			g[node] = g[node] * (f[to] + g[to]);
		}
	}

	subtask2()
	{
		DFS(1, 0);
		f[1].resize(m + 1);
		g[1].resize(m + 1);
		printOut((f[1][m] + g[1][m]) % mod);
	}
};
struct subtask3
{
	Poly f[maxn];
	Poly g[maxn];

	void DFS(int node, int parent)
	{
		f[node].push_back(a[node]);
		g[node][0] = 1;
		wander(G, node)
		{
			DEF(G);
			if (to == parent) continue;
			DFS(to, node);
			f[node] = f[node] * g[to];
			g[node] = g[node] * (f[to] + g[to]);
			if (f[node].size() > 11) f[node].resize(11);
			if (g[node].size() > 11) g[node].resize(11);
		}
	}

	subtask3()
	{
		DFS(1, 0);
		f[1].resize(m + 1);
		g[1].resize(m + 1);
		printOut((f[1][m] + g[1][m]) % mod);
	}
};
struct subtask4
{
	Poly f[4][maxn * 2];
	static inline int code(int l, int r)
	{
		return (l + r) | (l != r);
	}
	void divide(int l, int r)
	{
		int cnt = code(l, r);
		Poly& f0 = f[0][cnt];
		Poly& f1 = f[1][cnt];
		Poly& f2 = f[2][cnt];
		Poly& f3 = f[3][cnt];
		if (l == r)
		{
			f0.resize(1);
			f0[0] = 1;
			f3.resize(2);
			f3[0] = 0;
			f3[1] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		divide(l, mid);
		divide(mid + 1, r);
		int lc = code(l, mid);
		int rc = code(mid + 1, r);
		f0 = (f[0][lc] + f[2][lc]) * f[0][rc] + f[0][lc] * f[1][rc];
		f1 = f[1][lc] * (f[0][rc] + f[1][rc]) + f[3][lc] * f[0][rc];
		f2 = (f[0][lc] + f[2][lc]) * f[2][rc] + f[0][lc] * f[3][rc];
		f3 = f[1][lc] * (f[2][rc] + f[3][rc]) + f[3][lc] * f[2][rc];
	}

	subtask4()
	{
		divide(1, n);
		int t = code(1, n);
		f[0][t].resize(m + 1);
		f[1][t].resize(m + 1);
		f[2][t].resize(m + 1);
		f[3][t].resize(m + 1);
		printOut(((long long)f[0][t][m] + f[1][t][m] + f[2][t][m] + f[3][t][m]) % mod);
	}
};
struct subtask5
{
	Poly f[maxn * 2];
	static inline int code(int l, int r)
	{
		return (l + r) | (l != r);
	}

	void divide(int l, int r)
	{
		Poly& f0 = f[code(l, r)];
		if (l == r)
		{
			f0.resize(2);
			f0[0] = 1;
			f0[1] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		int lc = code(l, mid);
		int rc = code(mid + 1, r);
		divide(l, mid);
		divide(mid + 1, r);
		const Poly& f1 = f[lc];
		const Poly& f2 = f[rc];
		f0 = f1 * f2;
	}

	subtask5()
	{
		divide(2, n);
		f[code(2, n)].resize(m + 1);
		printOut((f[code(2, n)][m] + (m == 1 ? a[1] : 0)) % mod);
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
	else if (p2)
		RunInstance(subtask5);
	else if (n <= 4000)
		RunInstance(subtask2);
	else if (m <= 10)
		RunInstance(subtask3);
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