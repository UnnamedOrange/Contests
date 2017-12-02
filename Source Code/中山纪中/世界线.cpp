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

const INT maxn = 6e4 + 5;
const INT maxm = 1e5 + 5;
INT n, m;
struct EDGE
{
	INT to;
	INT next;
} edges[maxm];
INT head[maxn];
INT out[maxn];

void work()
{

}

namespace cheat
{
	INT ans;
	INT temp;
	bool vis[2005];
	void dfs(INT node)
	{
		vis[node] = true;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (!vis[to])
			{
				temp++;
				dfs(to);
			}
		}
	}
	void work()
	{
		for (int i = 1; i <= n; i++)
		{
			temp = 0;
			memset(vis, 0, sizeof(vis));
			dfs(i);
			ans += temp - out[i];
		}
		cout << ans << endl;
	}
}
void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		edges[i].to = readIn();
		edges[i].next = head[from];
		head[from] = i;

		out[edges[i].to]++;
	}

	if (n <= 2000) cheat::work();
	else work();
}

int main()
{
#ifndef JUDGE
	freopen("worldline.in", "r", stdin);
	freopen("worldline.out", "w", stdout);
#endif
	run();
	return 0;
}
