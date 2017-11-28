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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
		a = a * 10 + ch - '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[12];
		INT length = 0;
		bool minus = x < 0;
		if (minus) x = -x;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
			putchar(buffer[--length]);
		while (length);
	}
	putchar('\n');
}

const INT maxn = 100005;
INT n, m;
struct Edge
{
	INT to;
	INT next;
} edges[maxn * 2];
INT head[maxn];
INT count_;
void addEdge(INT from, INT to)
{
	count_++;
	edges[count_].to = to;
	edges[count_].next = head[from];
	head[from] = count_;
}

INT f[maxn], g[maxn];
void dfs(INT node)
{
	f[node] = g[node] = 0;
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		dfs(to);
		g[node] += std::max(f[to], g[to]);
	}
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		f[node] = std::max(f[node], g[node] - std::max(f[to], g[to]) + g[to] + 1);
	}
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		memset(head, 0, sizeof(INT) * (n + 1));
		count_ = 0;
		for (int i = 2; i <= n; i++)
		{
			addEdge(readIn(), i);
		}

		dfs(1);
		INT maxVal = std::max(f[1], g[1]);
		if (maxVal * 2 >= m)
		{
			printOut((m + 1) / 2);
		}
		else
		{
			printOut(m - maxVal);
		}
	}
}

int main()
{
#ifndef JUDGE
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	run();
	return 0;
}
