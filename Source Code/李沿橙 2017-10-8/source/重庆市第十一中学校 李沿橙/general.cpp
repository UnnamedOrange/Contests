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
typedef int INT;
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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = INT(1e5) + 5;
const INT maxk = 24;
INT n, K, T;

struct Edge
{
	INT to;

	INT next;
} edges[maxn * 2];
INT head[maxn];
inline void addEdge(INT from, INT to)
{
	static INT count_ = 0;
	count_++;
	edges[count_].to = to;
	edges[count_].next = head[from];
	head[from] = count_;
}

#define RunInstance(x) delete new x
struct cheat
{
	INT f[maxn];
	INT g[maxn];

	void dfs(INT node = 1, INT parent = 0)
	{
		f[node] = 1;
		g[node] = 0;
		for(int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if(to == parent) continue;
			dfs(to, node);

			f[node] += std::min(f[to], g[to]);
			g[node] += f[to];
		}
	}

	cheat()
	{
		dfs();
		INT ans = f[1];
		if(g[1]) ans = std::min(ans, g[1]);
		cout << ans << endl;
	}
};
struct work
{
	INT f[maxn][maxk];
	INT g[maxn][maxk];

	void dfs(INT node = 1, INT parent = 0)
	{

	}

	work()
	{
		dfs();
	}
};

void run()
{
	n = readIn();
	K = readIn();
	T = readIn();
	for(int i = 1; i < n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to);
		addEdge(to, from);
	}

	if(K == 0) cout << n << endl;
	else if(K == 1) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("general.in", "r", stdin);
	freopen("general.out", "w", stdout);
#endif
	run();
	return 0;
}
