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
typedef LL INT_PUT;
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
}

const int maxn = int(3e5) + 5;
int n, k;
struct Edge
{
	int to;
	int cost;
	Edge() {}
	Edge(int to, int cost) : to(to), cost(cost) {}
};

#define RunInstance(x) delete new x
struct cheat
{
	std::vector<Edge> G[maxn];
	LL ans;
	LL f[maxn];

	void DFS(int node, int parent)
	{
		f[node] = 0;
		LL major = 0;
		LL minor = 0;
		for (int i = 0; i < G[node].size(); i++)
		{
			const Edge& e = G[node][i];
			if (e.to == parent) continue;
			DFS(e.to, node);

			LL t = f[e.to] + e.cost;
			f[node] = std::max(f[node], t);
			if (t > minor)
			{
				if (t > major)
				{
					minor = major;
					major = t;
				}
				else
					minor = t;
			}
		}
		ans = std::max(ans, major + minor);
	}

	cheat() : ans()
	{
		for (int i = 1; i < n; i++)
		{
			int from = readIn();
			int to = readIn();
			int cost = std::abs(readIn());
			G[from].push_back(Edge(to, cost));
			G[to].push_back(Edge(from, cost));
		}

		DFS(1, 0);
		printOut(ans);
	}
};
struct fake : cheat
{
	fake()
	{

	}
};

void run()
{
	n = readIn();
	k = readIn();
	if (k == 0)
		RunInstance(cheat);
	else
		RunInstance(fake);
}

int main()
{
#ifndef LOCAL
	freopen("lct.in", "r", stdin);
	freopen("lct.out", "w", stdout);
#endif
	run();
	return 0;
}
