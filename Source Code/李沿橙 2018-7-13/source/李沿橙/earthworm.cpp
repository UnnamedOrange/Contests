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
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
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
}

const int maxn = 255;
const int maxq = int(5e4) + 5;
int n, m, q;
std::vector<std::vector<int> > G;
struct Ins
{
	int a, b, c;
	void read()
	{
		a = readIn();
		b = readIn();
		c = readIn();
	}
} inss[maxq];

#define RunInstance(x) delete new x
struct brute
{
	int belong[10];
	bool onWay[10];
	void DFS(int node, int parent, int target)
	{
		if (node == target)
		{
			onWay[node] = true;
			return;
		}
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			if (to == parent) continue;
			DFS(to, node, target);
			if (onWay[to])
				onWay[node] = true;
		}
	}

	void search(int depth)
	{
		if (depth > m)
		{
			for (int i = 1; i <= q; i++)
			{
				const Ins& ins = inss[i];
				std::memset(onWay, 0, sizeof(onWay));
				DFS(belong[ins.a], 0, belong[ins.b]);
				if (!onWay[ins.c])
					return;
			}
			for (int i = 1; i <= m; i++)
			{
				printOut(belong[i]);
				putchar(' ');
			}
			exit(0);
			return;
		}
		for (int i = 1; i <= n; i++)
		{
			belong[depth] = i;
			search(depth + 1);
		}
	}

	brute()
	{
		search(1);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	G.resize(n + 1);
	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		G[from].push_back(to);
		G[to].push_back(from);
	}
	for (int i = 1; i <= q; i++)
		inss[i].read();

	if (n <= 5 && m <= 5)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("earthworm.in", "r", stdin);
	freopen("earthworm.out", "w", stdout);
#endif
	run();
	return 0;
}