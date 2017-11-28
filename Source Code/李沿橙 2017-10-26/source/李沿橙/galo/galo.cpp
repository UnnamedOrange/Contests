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
#include <functional>
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
		{
			putchar(buffer[--length]);
		} while (length);
	}
}

const INT maxn = INT(1e5) + 5;
INT n, K;
INT parent[maxn];
INT w[maxn];
struct Edge
{
	INT to;
	INT next;
} edges[maxn];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

#define RunInstance(x) delete new x
struct cheat
{
	std::vector<std::vector<INT> > f;
	std::vector<INT> temp;
	INT size[maxn];

	void dfs(INT node)
	{
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			dfs(to);
			size[node] += size[to];
			temp = f[node];
			for (int j = 1; j <= size[to] && j <= K; j++)
				for (int k = K; k >= j; k--)
					temp[k] = std::max(temp[k], f[node][k - j] + f[to][j]);
			for (int j = K; j >= 1; j--)
				temp[j] = std::max(temp[j], f[node][j - 1] + w[to]);
			for (int j = 1; j <= K; j++)
				f[node][j] = std::max(f[node][j], temp[j]);
		}
		size[node]++;
	}

	cheat() : size()
	{
		f.resize(n + 1);
		for (int i = 0; i <= n; i++) f[i].resize(K + 1);
		dfs(1);
		INT ans = 0;
		for (int i = 1; i <= K; i++)
			ans = std::max(ans, f[1][i]);
		printOut(ans);
	}
};
struct work
{
	INT dfn[maxn];
	INT size[maxn];
	INT seq[maxn];

	void dfs(INT node)
	{
		static INT nClock = 0;
		dfn[node] = ++nClock;
		seq[nClock] = node;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			dfs(to);
			size[node] += size[to];
		}
		size[node]++;
	}

	std::vector<std::vector<INT> > f;

	work() : size()
	{
		f.resize(n + 2);
		for (int i = 0; i <= n + 1; i++) f[i].resize(K + 2);
		dfs(1);
		for (int i = n; i >= 1; i--)
		{
			INT node = seq[i];
			for (int j = K; j >= 0; j--)
			{
				f[i][j] = f[i + 1][j];
				if (j) f[i][j] = std::max(f[i][j], f[i + size[node]][j - 1] + w[node]);
			}
		}

		INT ans = 0;
		for (int i = 1; i <= K; i++) ans = std::max(ans, f[1][i]);
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	K = readIn() + 1;
	for (int i = 2; i <= n; i++)
	{
		parent[i] = readIn();
		w[i] = readIn();
		addEdge(parent[i], i);
	}

	if (n * K * K <= INT(1e7) + 5)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("galo.in", "r", stdin);
	freopen("galo.out", "w", stdout);
#endif
	run();
	return 0;
}
