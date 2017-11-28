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

const INT maxn = INT(1e5) + 5;
const INT maxk = 25;
INT n, s, K;

struct Edge
{
	INT to;

	INT next;
} edges[maxn * 2];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT count_ = 0;
	count_++;
	edges[count_].to = to;
	edges[count_].next = head[from];
	head[from] = count_;
}

#define RunInstance(x) delete new x
struct work
{
	INT f[maxn][maxk];
	INT g[maxn][maxk];
	INT ans;

	void DFS(INT node, INT parent)
	{
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			DFS(to, node);

			for(int j = 1; j <= K; j++)
			{
				f[node][j] += f[to][j - 1];
				g[node][j] += g[to][j - 1];
			}
		}
		g[node][0]++;

		if(g[node][K])
		{
			INT need = (g[node][K] + s - 1) / s;
			f[node][0] = need * s;
			ans += need;
		}
		for(int i = 0; i <= K; i++)
		{
			INT depth = K - i;
			INT count = std::min(f[node][i], g[node][depth]);
			f[node][i] -= count;
			g[node][depth] -= count;
		}
		for(int i = 0; i < K; i++)
		{
			INT depth = K - i - 1;
			INT count = std::min(f[node][i], g[node][depth]);
			f[node][i] -= count;
			g[node][depth] -= count;
		}
	}

	work() : ans(), f(), g()
	{
		DFS(1, 0);
		for(int i = 1; i <= K; i++)
		{
			for(int j = K - i; j >= 0; j--)
			{
				INT d = std::min(f[1][i], g[1][j]);
				f[1][i] -= d;
				g[1][j] -= d;
			}
		}
		INT count = 0;
		for(int i = 0; i <= K; i++) count += g[1][i];
		ans += (count + s - 1) / s;
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	s = readIn();
	K = readIn();
	for (int i = 1; i < n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to);
		addEdge(to, from);
	}

	if (s == 1) cout << n << endl;
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("repulsed.in", "r", stdin);
	freopen("repulsed.out", "w", stdout);
#endif
	run();
	return 0;
}
