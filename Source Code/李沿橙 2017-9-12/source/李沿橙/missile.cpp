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
INT n;
struct Point
{
	INT x;
	INT y;
	INT z;

	void read()
	{
		x = readIn();
		y = readIn();
		z = readIn();
	}
	bool operator< (const Point& b) const
	{
		return x < b.x;
	}
	friend bool gt(const Point& a, const Point& b)
	{
		return a.x > b.x && a.y > b.y && a.z > b.z;
	}
} points[maxn];

INT f[maxn];
std::vector<std::vector<INT> > edges;
inline void addEdge(INT from, INT to)
{
	edges[from].push_back(to);
}

bool vis[maxn];
INT linkX[maxn];
bool augment(INT from)
{
	for (int i = 0; i < edges[from].size(); i++)
	{
		INT to = edges[from][i];
		if (vis[to]) continue;
		vis[to] = true;
		if (!linkX[to] || augment(linkX[to]))
		{
			linkX[to] = from;
			return true;
		}
	}
	return false;
}

void run()
{
	n = readIn();
	edges.resize(n + 1);
	for (int i = 1; i <= n; i++) points[i].read();
	std::sort(points + 1, points + 1 + n);

	INT ans;
	//Q1
	ans = f[1] = 1;
	for (int i = 1; i <= n; i++)
	{
		f[i] = 1;
		for (int j = 1; j < i; j++)
		{
			if (gt(points[i], points[j]))
			{
				f[i] = std::max(f[i], f[j] + 1);
				addEdge(i, j);
			}
		}
		ans = std::max(ans, f[i]);
	}
	cout << ans << endl;

	//Q2 - augment
	ans = n;
	for (int i = 1; i <= n; i++)
	{
		memset(vis, 0, sizeof(vis));
		ans -= augment(i);
	}
	cout << ans << endl;
}

int main()
{
#ifndef JUDGE
	freopen("missile.in", "r", stdin);
	freopen("missile.out", "w", stdout);
#endif
	run();
	return 0;
}