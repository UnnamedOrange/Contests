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

const INT maxn = 1005;
const INT maxh = 24;
INT a[maxh + 5];
INT b[maxh + 5];

#define RunInstance(x, param...) delete new x(param)
struct cheat1
{
	INT n;
	INT st[30];
	INT count1[1 << 20];

	cheat1() : n(), st(), count1()
	{
		for(int i = 1; i <= maxh; i++)
		{
			for(int j = 1; j <= b[i]; j++)
			{
				st[n++] = i;
			}
		}

		INT ans = -1;
		INT U = 1 << n;
		for(int i = 1; i < U; i++)
		{
			count1[i] = count1[i ^ (i & -i)] + 1;
		}
		for(int S = 0; S < U; S++)
		{
			if(~ans && count1[S] >= ans) continue;
			INT sign[40] = { 0 };
			for(int i = 0; i < n; i++)
			{
				if(S & (1 << i))
				{
					sign[st[i]]++;
					sign[st[i] + 8]--;
				}
			}
			for(int i = 1; i <= 32; i++)
			{
				sign[i] += sign[i - 1];
			}
			for(int i = 1; i <= 7; i++)
			{
				sign[i] += sign[i + maxh];
			}
			bool bOk = true;
			for(int i = 1; i <= maxh; i++)
			{
				if(sign[i] < a[i])
				{
					bOk = false;
					break;
				}
			}
			if(!bOk) continue;
			ans = count1[S];
		}
		cout << ans << endl;
	}
};
struct work
{
	INT n;
	struct Edge
	{
		INT to;
		INT cost;
		Edge() {}
		Edge(INT to, INT cost) : to(to), cost(cost) {}
	};
	std::vector<Edge> edges[25];

	INT build(INT b24)
	{
		for(int i = 0; i <= 24; i++) edges[i].clear();
		for(int i = 0; i <= 16; i++)
			edges[i].push_back(Edge(i + 8, a[i + 8]));
		for(int i = 1; i <= 8; i++)
			edges[i + 16].push_back(Edge(i, a[i] - b24));

		for(int i = 1; i <= 24; i++)
		{
			edges[i].push_back(Edge(i - 1, -b[i]));
			edges[i - 1].push_back(Edge(i, 0));
		}

		edges[24].push_back(Edge(0, -b24));
		edges[0].push_back(Edge(24, b24));
	}

	bool vis[25];
	INT dis[25];
	bool DFS(INT node)
	{
		vis[node] = true;
		for(int i = 0; i < edges[node].size(); i++)
		{
			Edge& e = edges[node][i];
			if(dis[node] + e.cost > dis[e.to])
			{
				dis[e.to] = dis[node] + e.cost;
				if(vis[e.to])
					return false;
				else if(!DFS(e.to)) return false;
			}
		}
		vis[node] = false;
		return true;
	}

	bool check(INT s)
	{
		build(s);
		memset(vis, 0, sizeof(vis));
		memset(dis, 0x80, sizeof(dis));
		dis[0] = 0;
		return DFS(0);
	}

	work(INT n) : n(n)
	{
		INT l = 0;
		INT r = n + 1;
		while(r - l > 0)
		{
			INT mid = l + ((r - l) >> 1);
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		if(l == n + 1) l = -1; 
		cout << l << endl;
	}
};

void run()
{
	INT T = readIn();
	while(T--)
	{
		INT n = 0;
		for(int i = 1; i <= maxh; i++)
		{
			a[i] = readIn();
		}
		for(int i = 1; i <= maxh; i++)
		{
			b[i] = readIn();
			n += b[i];
		}

//		if(n <= 20 && !T) RunInstance(cheat1);
//		else
		RunInstance(work, n);
	}
}

int main()
{
#ifndef JUDGE
	freopen("cashier.in", "r", stdin);
	freopen("cashier.out", "w", stdout);
#endif
	run();
	return 0;
}
