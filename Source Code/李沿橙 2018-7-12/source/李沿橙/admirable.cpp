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

const int mod = int(1e9) + 9;
LL power(LL x, int y)
{
	LL ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
const int maxn = int(1e5);
int n, m;
std::vector<std::vector<int> > G;

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 10;
	int parent[maxN];
	int depth[maxN];
	void DFS(int node)
	{
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			if (to == parent[node]) continue;
			parent[to] = node;
			depth[to] = depth[node] + 1;
			DFS(to);
		}
	}
	int lca(int u, int v)
	{
		if (depth[u] < depth[v])
			std::swap(u, v);
		while (depth[u] > depth[v])
			u = parent[u];
		while (u != v)
		{
			u = parent[u];
			v = parent[v];
		}
		return u;
	}

	int t[maxN][2];
	int sum[maxN];
	void prefix(int node)
	{
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			if (to == parent[node]) continue;
			prefix(to);
			sum[node] += sum[to];
		}
	}
	int ans;
	void search(int d)
	{
		if (d > m)
		{
			std::memset(sum, 0, sizeof(sum));
			for (int i = 1; i <= m; i++)
			{
				sum[t[i][0]]++;
				sum[t[i][1]]++;
				sum[lca(t[i][0], t[i][1])] -= 2;
			}
			prefix(1);
			bool bOk = false;
			for (int i = 2; i <= n; i++)
			{
				if (2 <= sum[i] && sum[i] <= m - 1)
					return;
				if (sum[i] == m)
					bOk = true;
			}
			if (bOk)
			{
				ans++;
#ifdef LOCAL
				//for (int i = 1; i <= m; i++)
				//	printf("%d: %d %d\n", i, t[i][0], t[i][1]);
#endif
			}
			return;
		}
		for (t[d][0] = 1; t[d][0] <= n; t[d][0]++)
		{
			for (t[d][1] = t[d][0] + 1; t[d][1] <= n; t[d][1]++)
			{
				search(d + 1);
			}
		}
	}

	brute() : ans()
	{
		depth[1] = 1;
		parent[1] = 0;
		DFS(1);
		search(1);
		printOut(ans);
	}
};
typedef long double REAL;
const REAL PI = std::acos((long double)-1);
struct Complex
{
	REAL x, y;
	Complex() {};
	Complex(const REAL& x, const REAL& y) : x(x), y(y) {}
	Complex operator+(const Complex& b) const
	{
		return Complex(x + b.x, y + b.y);
	}
	Complex operator-(const Complex& b) const
	{
		return Complex(x - b.x, y - b.y);
	}
	Complex operator*(const Complex& b) const
	{
		return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
	}
	void operator/=(const REAL& b)
	{
		x /= b;
		y /= b;
	}
};
typedef std::vector<Complex> Base;
struct Poly : public Base
{
	Poly() : Base(1) {}
	Poly(int size) : Base(size) {}
	static void DFT(Complex* a, int logn, bool IDFT)
	{
		int n = 1 << logn;
		static int revbit[1 << 18];
		revbit[0] = 0;
		for (int i = 1; i < n; i++)
			revbit[i] = (revbit[i >> 1] >> 1) | ((i & 1) << (logn - 1));
		for (int i = 1; i < n; i++)
			if (i < revbit[i])
				std::swap(a[i], a[revbit[i]]);

		for (int i = 1; i <= logn; i++)
		{
			int S = 1 << i;
			int half = S >> 1;
			Complex w1(std::cos(2 * PI / S), std::sin(2 * PI / S) * (IDFT ? -1 : 1));
			for (int j = 0; j < n; j += S)
			{
				Complex* A = a + j;
				Complex w(1, 0);
				for (int k = 0; k < half; k++)
				{
					Complex t = A[k + half] * w;
					A[k + half] = A[k] - t;
					A[k] = A[k] + t;
					w = w * w1;
				}
			}
		}
		if (IDFT)
			for (int i = 0; i < n; i++)
				a[i] /= n;
	}
	Poly operator*(const Poly& c) const
	{
		Poly ret(size() + c.size() - 1);
		static Complex a[1 << 18];
		static Complex b[1 << 18];
		int logn = 0;
		while ((1 << logn) < ret.size()) logn++;
		int n = 1 << logn;
		std::memcpy(a, data(), sizeof(Complex) * size());
		std::memset(a + size(), 0, sizeof(Complex) * (n - size()));
		std::memcpy(b, c.data(), sizeof(Complex) * c.size());
		std::memset(b + c.size(), 0, sizeof(Complex) * (n - c.size()));
		DFT(a, logn, false);
		DFT(b, logn, false);
		for (int i = 0; i < n; i++)
			a[i] = a[i] * b[i];
		DFT(a, logn, true);
		std::memcpy(ret.data(), a, sizeof(Complex) * ret.size());
		return ret;
	}
};
struct cheat
{
	cheat()
	{
		int ans = (LL)n * (n - 1) / 2 % mod;
		/*
		 *for (int i = 2; i <= n; i++)
		 *{
		 *	for (int l = 1; l + i - 1 <= n; l++)
		 *	{
		 *		ans++;
		 *		ans = (ans + (LL)m * (l - 1)) % mod;
		 *		ans = (ans + (LL)m * (n - (l + i - 1))) % mod;
		 *		ans = (ans + (LL)m * m % mod * (l - 1) % mod * (n - (l + i - 1))) % mod;
		 *	}
		 *}
		 */
		int t = 0;
		for (int l = 1; l <= n; l++)
			t = (t + (LL)m * (l - 1) % mod * (n - l)) % mod;
		ans = (ans + (t << 1)) % mod;
		Poly mul(n + 1);
		for (int i = 0; i <= n; i++)
			mul[i] = Complex(i, 0);
		mul = mul * mul;
		int mm = (LL)m * m % mod;
		for (int i = 2; i <= n - 2; i++)
			ans = (ans + (LL)mm % mod * ((LL)(mul[i].x + 0.5) % mod)) % mod;

		printOut(ans);
	}
};
struct brute2
{
	static const int maxN = 105;
	int size[maxN];
	void DFS1(int node, int parent)
	{
		size[node] = 1;
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			if (to == parent) continue;
			DFS1(to, node);
			size[node] += size[to];
		}
	}
	int ans;
	int left;
	int f[maxN];
	void DFS2(int node, int parent, bool root)
	{
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			if (to == parent) continue;
			if (root)
			{
				left = 0;
				std::memset(f, 0, sizeof(f));
				f[0] = 1;
				for (int j = 0; j < G[node].size(); j++) if (j != i)
				{
					int t = G[node][j];
					for (int k = m; k; k--)
						f[k] = (f[k] + (LL)size[t] * f[k - 1]) % mod;
				}
				int mul = 1;
				for (int j = 0; j <= m; j++)
				{
					left = (left + (LL)mul * f[j]) % mod;
					mul = (LL)mul * (m - j) % mod;
				}
			}
			DFS2(to, node, false);

			int right = 0;
			std::memset(f, 0, sizeof(f));
			f[0] = 1;
			for (int j = 0; j < G[to].size(); j++)
			{
				int t = G[to][j];
				if (t == node) continue;
				for (int k = m; k; k--)
					f[k] = (f[k] + (LL)size[t] * f[k - 1]) % mod;
			}
			int mul = 1;
			for (int j = 0; j <= m; j++)
			{
				right = (right + (LL)mul * f[j]) % mod;
				mul = (LL)mul * (m - j) % mod;
				//printf("right: %d\n", right);
			}
			ans = (ans + (LL)left * right) % mod;
			//printf("ans: %d\n", ans);
		}
	}

	brute2() : ans()
	{
		for (int i = 1; i <= n; i++)
		{
			DFS1(i, 0);
			DFS2(i, 0, true);
		}
		ans = (LL)ans * power(2, mod - 2) % mod;
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	if (m == 1)
	{
		printOut((LL)n * (n - 1) / 2 % mod);
		return;
	}

	G.resize(n + 1);
	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		G[from].push_back(to);
		G[to].push_back(from);
	}

	if (n <= 5)
		RunInstance(brute);
	else if (n <= 100)
		RunInstance(brute2);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("admirable.in", "r", stdin);
	freopen("admirable.out", "w", stdout);
#endif
	run();
	return 0;
}