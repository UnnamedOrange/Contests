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
	INT length = 0;
	bool minus = x < 0;
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

const INT maxn = 1000005;
INT n, m;
struct Edge
{
	INT to;
	INT next;
} edges[maxn];
INT head[maxn];
void addEdge(INT from, INT to)
{
	if (from == to) return;
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

INT dfn[maxn];
INT low[maxn];
INT s[maxn];
bool inStack[maxn];
INT scc[maxn];
INT inscc[maxn];
void dfs(INT node)
{
	static INT clock;
	low[node] = dfn[node] = ++clock;
	s[++s[0]] = node;
	inStack[node] = true;
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (!dfn[to])
		{
			dfs(to);
			low[node] = std::min(low[node], low[to]);
		}
		else if (inStack[to])
			low[node] = std::min(low[node], dfn[to]);
	}

	if (dfn[node] == low[node])
	{
		scc[0]++;
		INT top;
		do
		{
			top = s[s[0]];
			scc[scc[0]]++;
			inscc[top] = scc[0];
			inStack[top] = false;
			s[0]--;
		} while (top != node);
	}
}

Edge e2[maxn];
INT h2[maxn];
void ae2(INT from, INT to)
{
	if (from == to) return;
	static INT i;
	i++;
	e2[i].to = to;
	e2[i].next = h2[from];
	h2[from] = i;
}
void reEdge()
{
	for (int i = 1; i <= n; i++)
		for (int j = head[i]; j; j = edges[j].next)
			ae2(inscc[i], inscc[edges[j].to]);
}

INT f[maxn];
INT dp(INT node)
{
	if (f[node]) return f[node];
	INT t = 0;
	for (int i = h2[node]; i; i = e2[i].next)
	{
		INT to = e2[i].to;
		t = std::max(t, dp(to));
	}
	return f[node] = scc[node] + t;
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT u = readIn();
		INT v = readIn();
		addEdge(u, v);
	}

	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
	reEdge();

	INT ans = 0;
	for (int i = 1; i <= scc[0]; i++)
		ans = std::max(ans, dp(i));
	printOut(ans);
}

int main()
{
#ifndef LOCAL
	freopen("bomb.in", "r", stdin);
	freopen("bomb.out", "w", stdout);
#endif
	run();
	return 0;
}
