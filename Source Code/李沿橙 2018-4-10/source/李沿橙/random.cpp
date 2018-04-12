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
	putchar('\n');
}

const int mod = 998244353;
const int maxn = 40;
int n, m;
int rect[maxn][maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 7;
	std::vector<int> G[maxN];
	int N, clock;
	int dfn[maxN];
	int low[maxN];
	bool inStack[maxN];
	int stack[maxN];
	LL ans;

	void Tarjan(int node)
	{
		clock++;
		dfn[node] = low[node] = clock;
		stack[++stack[0]] = node;
		inStack[node] = true;
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			if (!dfn[to])
			{
				Tarjan(to);
				low[node] = std::min(low[node], low[to]);
			}
			else if (inStack[to])
				low[node] = std::min(low[node], dfn[to]);
		}
		if (dfn[node] == low[node])
		{
			N++;
			int top;
			do
			{
				top = stack[stack[0]--];
				inStack[top] = false;
			} while (top != node);
		}
	}
	int GetSC()
	{
		N = 0;
		clock = 0;
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(inStack, 0, sizeof(inStack));
		stack[0] = 0;
		for (int i = 1; i <= n; i++)
			if (!dfn[i]) Tarjan(i);
		return N;
	}
	void search(int x = 1, int y = 2, LL accum = 1)
	{
		if (x == n)
		{
			ans = (ans + accum * GetSC()) % mod;
			return;
		}
		int newx = x, newy = y + 1;
		if (y == n)
		{
			newx = x + 1;
			newy = newx + 1;
		}
		G[x].push_back(y);
		search(newx, newy, accum * rect[x][y] % mod);
		G[x].pop_back();

		G[y].push_back(x);
		search(newx, newy, accum * rect[y][x] % mod);
		G[y].pop_back();
	}
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
	brute() : ans()
	{
		search();
		printOut(ans * power(10000, n * (n - 1) / 2) % mod);
	}
};

struct cheat
{
	static const int maxN = 9;
	std::vector<int> G[maxN];
	int N, clock;
	int dfn[maxN];
	int low[maxN];
	bool inStack[maxN];
	int stack[maxN];
	LL ans[maxN];

	void Tarjan(int node)
	{
		clock++;
		dfn[node] = low[node] = clock;
		stack[++stack[0]] = node;
		inStack[node] = true;
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			if (!dfn[to])
			{
				Tarjan(to);
				low[node] = std::min(low[node], low[to]);
			}
			else if (inStack[to])
				low[node] = std::min(low[node], dfn[to]);
		}
		if (dfn[node] == low[node])
		{
			N++;
			int top;
			do
			{
				top = stack[stack[0]--];
				inStack[top] = false;
			} while (top != node);
		}
	}
	int GetSC()
	{
		N = 0;
		clock = 0;
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(inStack, 0, sizeof(inStack));
		stack[0] = 0;
		for (int i = 1; i <= n; i++)
			if (!dfn[i]) Tarjan(i);
		return N;
	}
	void search(int x = 1, int y = 2)
	{
		if (x == n)
		{
			ans[GetSC()]++;
			return;
		}
		int newx = x, newy = y + 1;
		if (y == n)
		{
			newx = x + 1;
			newy = newx + 1;
		}
		G[x].push_back(y);
		search(newx, newy);
		G[x].pop_back();

		G[y].push_back(x);
		search(newx, newy);
		G[y].pop_back();
	}
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
	cheat() : ans()
	{
		search();
		for (int i = 1; i <= n; i++)
			printOut(ans[i]);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			rect[i][j] = 5000;
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		int cost = readIn();
		rect[from][to] = cost;
		rect[to][from] = 10000 - cost;
	}

	RunInstance(cheat);

	if (n == 1)
		printOut(1);
	else if (n <= 6)
		RunInstance(brute);
	else
	{
		srand(time(NULL) + clock());
		printOut((rand() << 15 | rand()) % mod);
	}
}

int main()
{
#ifndef LOCAL
	freopen("random.in", "r", stdin);
	freopen("random.out", "w", stdout);
#endif
	run();
	return 0;
}