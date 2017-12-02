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

const INT mod = 1000000007;
const INT maxn = 100005;
INT n, m;
INT weight[maxn];
INT parent[maxn];
struct EDGE
{
	INT to;
	INT next;
} edges[maxn];
INT head[maxn];
inline void addEdge(INT from, INT to)
{
	static INT count_ = 0;
	count_++;
	edges[count_].to = to;
	edges[count_].next = head[from];
	head[from] = count_;
}
INT ans;

INT f[maxn];
void dfs(INT node = 1)
{
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		dfs(to);
		f[node] = (f[node] + f[to]) % mod;
	}
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		ans = (ans + (f[node] - f[to] + mod) * f[to] % mod * weight[node]) % mod;
	}
	ans = (ans + f[node] % mod * weight[node] % mod * weight[node] % mod * 2) % mod;
	ans = (ans + weight[node] % mod * weight[node] % mod * weight[node]) % mod;
	f[node] = (f[node] + weight[node]) % mod;
}
void work()
{
	dfs();
	cout << ans << endl;
}

void run()
{
	n = readIn();
	m = n - 1;
	weight[1] = readIn();
	for (int i = 2; i <= n; i++)
	{
		parent[i] = readIn();
		weight[i] = readIn();
		addEdge(parent[i], i);
	}
	work();
}

int main()
{
	run();
	return 0;
}
