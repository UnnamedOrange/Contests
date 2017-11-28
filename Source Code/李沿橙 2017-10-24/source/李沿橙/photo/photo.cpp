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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT maxn = INT(2e5) + 5;
INT n, m, mod;
INT parent[maxn];
INT f[maxn];
INT size[maxn];

struct Edge
{
	INT to;
	INT next;
} edges[maxn];
INT head[maxn];
INT count_;
void addEdge(INT from, INT to)
{
	count_++;
	edges[count_].to = to;
	edges[count_].next = head[from];
	head[from] = count_;
}

INT fac[maxn];
INT inv[maxn];
INT invFac[maxn];
void init()
{
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	inv[1] = 1;
	for (int i = 2; i <= n; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	invFac[0] = 1;
	for (int i = 1; i <= n; i++) invFac[i] = invFac[i - 1] * inv[i] % mod;
}
#define C(m, n) (((n) > (m)) ? 0 : fac[m] * invFac[n] % mod * invFac[(m) - (n)] % mod)

INT vis;
void dfs(INT node)
{
	vis++;
	size[node] = 0;
	f[node] = 1;
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		dfs(to);
		size[node] += size[to];
		f[node] = f[node] * f[to] % mod * C(size[node], size[to]) % mod;
	}
	size[node]++;
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		mod = readIn();
		memset(parent, 0, sizeof(INT) * (n + 1));
		while (m--)
		{
			INT to = readIn();
			INT from = readIn();
			parent[to] = from;
		}

		memset(head, 0, sizeof(INT) * (n + 1));
		count_ = 0;
		for (int i = 1; i <= n; i++)
		{
			addEdge(parent[i], i);
		}

		init();
		vis = 0;
		dfs(0);

		if (vis != n + 1) f[0] = 0;
		cout << f[0] << endl;
	}
}

int main()
{
#ifndef JUDGE
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
#endif
	run();
	return 0;
}
