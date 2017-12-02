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
	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}

const INT mod = 998244353;
const INT maxn = 100005;
INT n;
INT like[maxn];
INT maxLike;
std::vector<std::vector<INT> > edges;
INT f0[maxn]; //选了当前结点且没有包含最大结点的方案数
INT f1[maxn]; //选了当前结点且包含最大结点的方案数
INT g0[maxn]; //没选当前结点且没有包含最大结点的方案数
INT g1[maxn]; //没选当前结点且包含最大结点的方案数

void dfs(INT node = 1, INT parent = 0)
{
	if(like[node] == maxLike)
	{
		f0[node] = 0;
		f1[node] = 1;
	}
	else
	{
		f0[node] = 1;
		f1[node] = 0;
	}
	g0[node] = 1;
	g1[node] = 0;
	if(edges[node].size() == bool(parent)) return;

	INT F0 = 1, F1 = 1, G0 = 1, G1 = 1;
	for(int i = 0; i < edges[node].size(); i++)
	{
		INT& to = edges[node][i];
		if(to == parent) continue;
		dfs(to, node);

		if(like[node] == maxLike)
		{
			F0 = 0;
			F1 *= (f0[to] + f1[to]) % mod;
			F1 %= mod;
		}
		else
		{
			F0 *= f0[to];
			F0 %= mod;
			F1 *= f1[to];
			F1 %= mod;
		}
		G0 *= (f0[to] + g0[to]) % mod;
		G0 %= mod;
		G1 *= (f1[to] + g1[to]) % mod;
		G1 %= mod;
	}
	f0[node] += F0;
	f0[node] %= mod;
	f1[node] += F1;
	f1[node] %= mod;
	g0[node] += G0;
	g0[node] %= mod;
	g1[node] += G1;
	g1[node] %= mod;
}

void run()
{
	n = readIn();
	edges.resize(n + 1);
	for(int i = 1; i <= n; i++)
	{
		maxLike = std::max(maxLike, like[i] = readIn());
	}
	for(int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		edges[from].push_back(to);
		edges[to].push_back(from);
	}
	dfs();

	cout << (f1[1] + g1[1]) % mod << endl;
}

int main()
{
#ifndef DEBUG
	freopen("home.in", "r", stdin);
	freopen("home.out", "w", stdout);
#endif
	run();
	return 0;
}
