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
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = 1005;
const int maxh = 24;
int a[maxh + 5];
int b[maxh + 5];

#define RunInstance(x, param...) delete new x(param)
struct cheat1
{
	int n;
	int st[30];
	int count1[1 << 20];

	cheat1() : n(), st(), count1()
	{
		for (int i = 1; i <= maxh; i++)
		{
			for (int j = 1; j <= b[i]; j++)
			{
				st[n++] = i;
			}
		}

		int ans = -1;
		int U = 1 << n;
		for (int i = 1; i < U; i++)
		{
			count1[i] = count1[i ^ (i & -i)] + 1;
		}
		for (int S = 0; S < U; S++)
		{
			if (~ans && count1[S] >= ans) continue;
			int sign[40] = { 0 };
			for (int i = 0; i < n; i++)
			{
				if (S & (1 << i))
				{
					sign[st[i]]++;
					sign[st[i] + 8]--;
				}
			}
			for (int i = 1; i <= 32; i++)
			{
				sign[i] += sign[i - 1];
			}
			for (int i = 1; i <= 7; i++)
			{
				sign[i] += sign[i + maxh];
			}
			bool bOk = true;
			for (int i = 1; i <= maxh; i++)
			{
				if (sign[i] < a[i])
				{
					bOk = false;
					break;
				}
			}
			if (!bOk) continue;
			ans = count1[S];
		}
		cout << ans << endl;
	}
};
struct work
{
	int n;
	struct Edge
	{
		int to;
		int cost;
		Edge() {}
		Edge(int to, int cost) : to(to), cost(cost) {}
	};
	std::vector<Edge> edges[25];

	int build(int b24)
	{
		for (int i = 0; i <= 24; i++) edges[i].clear();
		for (int i = 0; i <= 16; i++)
			edges[i].push_back(Edge(i + 8, a[i + 8]));
		for (int i = 1; i <= 8; i++)
			edges[i + 16].push_back(Edge(i, a[i] - b24));

		for (int i = 1; i <= 24; i++)
		{
			edges[i].push_back(Edge(i - 1, -b[i]));
			edges[i - 1].push_back(Edge(i, 0));
		}

		edges[24].push_back(Edge(0, -b24));
		edges[0].push_back(Edge(24, b24));
	}

	bool vis[25];
	int dis[25];
	bool DFS(int node)
	{
		vis[node] = true;
		for (int i = 0; i < edges[node].size(); i++)
		{
			Edge& e = edges[node][i];
			if (dis[node] + e.cost > dis[e.to])
			{
				dis[e.to] = dis[node] + e.cost;
				if (vis[e.to])
					return false;
				else if (!DFS(e.to)) return false;
			}
		}
		vis[node] = false;
		return true;
	}

	bool check(int s)
	{
		build(s);
		memset(vis, 0, sizeof(vis));
		memset(dis, 0x80, sizeof(dis));
		dis[0] = 0;
		return DFS(0);
	}

	work(int n) : n(n)
	{
		int l = 0;
		int r = n + 1;
		while (r - l > 0)
		{
			int mid = l + ((r - l) >> 1);
			if (check(mid)) r = mid;
			else l = mid + 1;
		}
		if (l == n + 1) l = -1;
		cout << l << endl;
	}
};

void run()
{
	int T = readIn();
	while (T--)
	{
		int n = 0;
		for (int i = 1; i <= maxh; i++)
		{
			a[i] = readIn();
		}
		for (int i = 1; i <= maxh; i++)
		{
			b[i] = readIn();
			n += b[i];
		}

		RunInstance(work, n);
	}
}

int main()
{
#ifndef LOCAL
	freopen("cashier.in", "r", stdin);
	freopen("cashier.out", "w", stdout);
#endif
	run();
	return 0;
}