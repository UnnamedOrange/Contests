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
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	bool minus = x < 0;
	INT length = 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT mod = 998244353;
const INT maxn = INT(1e5) + 5;
INT n;
struct Edge
{
	INT to;
	INT next;
} edges[maxn * 2];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}
INT degree[maxn];

INT inv[maxn];
void init()
{
	inv[1] = 1;
	for (int i = 2; i <= n; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}

#define RunInstance(x) delete new x
struct brute
{
	INT ans;

	void dfs(INT node, INT parent, INT sum)
	{
		ans = (ans + sum) % mod;
		INT size = degree[node] - bool(parent);
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			dfs(to, node, (sum + (size - 1) * inv[size]) % mod);
		}
	}

	brute()
	{
		for (int i = 1; i <= n; i++)
		{
			ans = 0;
			dfs(i, 0, 0);
			printOut(ans);
		}
	}
};
struct work
{
	struct Sum
	{
		INT c[maxn];
		Sum() : c() {}
		INT& operator[] (INT x)
		{
			return c[x];
		}
		const INT& operator[] (INT x) const
		{
			return c[x];
		}
		void add(INT l, INT r, INT x)
		{
			c[l] = ((c[l] + x) % mod + mod) % mod;
			c[r + 1] = ((c[r + 1] - x) % mod + mod) % mod;
		}
		void runSum()
		{
			for (int i = 1; i <= n; i++)
			{
				c[i] = (c[i] + c[i - 1]) % mod;
			}
		}
	} sum;

	INT size[maxn];

	INT dfn[maxn];
	INT end[maxn];
	void dfs1(INT node, INT parent)
	{
		static INT clock;
		dfn[node] = ++clock;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			dfs1(to, node);
		}
		end[node] = clock;
	}

	void dfs2(INT node, INT parent)
	{
		INT s = degree[node];
		INT t = s - 1;
		INT contri_self = (s - 1) * inv[s] % mod * (n - 1) % mod;
		INT contri_other = (t - 1) * inv[t] % mod;
		sum.add(dfn[node], dfn[node], contri_self);

		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			dfs2(to, node);
			size[node] += size[to];

			sum.add(dfn[to], end[to], contri_other * (n - size[to] - 1) % mod);
		}
		size[node]++;

		INT temp = contri_other * (size[node] - 1) % mod;
		sum.add(1, dfn[node] - 1, temp);
		sum.add(end[node] + 1, n, temp);
	}

	work() : size(), dfn()
	{
		dfs1(1, 0);
		dfs2(1, 0);
		sum.runSum();
		for (int i = 1; i <= n; i++)
		{
			printOut(sum[dfn[i]]);
		}
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i < n; i++)
	{
		INT u = readIn();
		INT v = readIn();
		degree[u]++;
		degree[v]++;
		addEdge(u, v);
		addEdge(v, u);
	}
	init();

	if (n <= 2000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("redemption.in", "r", stdin);
	freopen("redemption.out", "w", stdout);
#endif
	run();
	return 0;
}
