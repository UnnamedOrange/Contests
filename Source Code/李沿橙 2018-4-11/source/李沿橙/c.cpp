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
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
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
	putchar(' ');
}

const int mod = int(1e9) + 7;
const int maxn = 105;
int n;
int rect[maxn][maxn];

#define RunInstance(x) delete new x
struct brute
{
	int g[maxn][maxn];
	LL ans[maxn];
	int stamp;
	int vis[maxn];
	int nVis;
	void DFS(int node)
	{
		vis[node] = stamp;
		nVis++;
		for (int i = 1; i <= n; i++)
		{
			if (g[node][i] && vis[i] != stamp)
			{
				DFS(i);
			}
		}
	}

	void search(int x, int y, int cnt, int nEdge)
	{
		if (nEdge >= n) return;
		if (x == n + 1)
		{
			nVis = 0;
			stamp++;
			DFS(1);
			if (nVis == n) ans[cnt]++;
			return;
		}
		int newx = x;
		int newy = y + 1;
		if (newy > n)
		{
			newx = x + 1;
			newy = newx + 1;
		}
		g[x][y] = g[y][x] = true;
		search(newx, newy, cnt + rect[x][y], nEdge + 1);
		g[x][y] = g[y][x] = false;
		search(newx, newy, cnt, nEdge);
	}

	brute() : g(), vis(), stamp(), ans()
	{
		search(1, 2, 0, 0);
		for (int i = 0; i < n; i++)
		{
			printOut(ans[i] % mod);
		}
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		rect[from][to] = rect[to][from] = 1;
	}

	if (n <= 6)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	run();
	return 0;
}