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
typedef long long INT;
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

#define pow2(x) ((x) * (x))
const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = INT(1e6) + 5;
const INT maxk = 6005;
INT n, m, k;
struct Point
{
	INT x;
	INT y;
	bool operator< (const Point& b) const
	{
		if (x != b.x) return x < b.x;
		return y < b.y;
	}
	friend INT dis(const Point& a, const Point& b)
	{
		return pow2(a.x - b.x) + pow2(a.y - b.y);
	}
} points[maxk];

#define RunInstance(x) delete new x
struct Eighty
{
	INT corner[maxk][4];
	INT cornerDis[maxk][4];

	struct DS
	{
		INT parent[maxk];

		void clear(INT size)
		{
			for (int i = 1; i <= size; i++)
			{
				parent[i] = i;
			}
		}

		INT find(INT x)
		{
			if (x == parent[x]) return x;
			return parent[x] = find(parent[x]);
		}

		void unite(INT x, INT y)
		{
			parent[find(y)] = find(x);
		}
		bool judge(INT x, INT y)
		{
			return find(x) == find(y);
		}
	} ds;

	bool check(double s)
	{
		s *= 2;
		s *= s;
		ds.clear(k + 2);
		for (int i = 1; i <= k; i++)
		{
			bool bCeil = (pow2(m - points[i].y) <= s);
			bool bFloor = (pow2(points[i].y) <= s);
			if (bCeil) ds.unite(i, k + 1);
			if (bFloor) ds.unite(i, k + 2);

			if (corner[i][0] && cornerDis[i][0] <= s) ds.unite(i, corner[i][0]);
			if (corner[i][1] && cornerDis[i][1] <= s) ds.unite(i, corner[i][1]);
			if (corner[i][2] && cornerDis[i][2] <= s) ds.unite(i, corner[i][2]);
			if (corner[i][3] && cornerDis[i][3] <= s) ds.unite(i, corner[i][3]);

			if (ds.judge(k + 1, k + 2)) return false;
		}
		return true;
	}

	Eighty() : corner(), cornerDis()
	{
		for (int i = 1; i <= k; i++)
		{
			for (int j = 1; j <= k; j++)
			{
				if (i == j) continue;
				INT t = dis(points[i], points[j]);
				if (points[j].x <= points[i].x && points[j].y >= points[i].y && (!corner[i][0] || t < cornerDis[i][0]))
				{
					corner[i][0] = j;
					cornerDis[i][0] = t;
				}
				if (points[j].x >= points[i].x && points[j].y >= points[i].y && (!corner[i][1] || t < cornerDis[i][1]))
				{
					corner[i][1] = j;
					cornerDis[i][1] = t;
				}
				if (points[j].x >= points[i].x && points[j].y <= points[i].y && (!corner[i][2] || t < cornerDis[i][2]))
				{
					corner[i][2] = j;
					cornerDis[i][2] = t;
				}
				if (points[j].x <= points[i].x && points[j].y <= points[i].y && (!corner[i][3] || t < cornerDis[i][3]))
				{
					corner[i][3] = j;
					cornerDis[i][3] = t;
				}
			}
		}

		double l = 0, r = double(m) / 2;
		while (r - l >= 1e-8)
		{
			double mid = (l + r) / 2;
			if (check(mid)) l = mid;
			else r = mid;
		}
		printf("%.8f\n", l);
	}
};

struct AC
{
	INT Dis[maxk];
	bool vis[maxk];
	INT from[maxk];
	struct Edge
	{
		INT to;
		INT cost;

		INT next;
	} edges[2 * maxk];
	INT head[maxk];
	void addEdge(INT from, INT to, INT cost)
	{
		static INT i = 0;
		i++;
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
	}

	static INT getDis(INT x, INT y)
	{
#define pow2(x) ((x) * (x))
		if (x > y) std::swap(x, y);
		if (x <= k && y <= k)
		{
			return pow2(points[x].x - points[y].x) + pow2(points[x].y - points[y].y);
		}
		else if (y == k + 1)
		{
			return pow2(m - points[x].y);
		}
		else if (x != k + 1 && y == k + 2)
		{
			return pow2(points[x].y);
		}
		return pow2(m);
#undef pow2
	}

	void Prim()
	{
		std::fill(Dis, Dis + 1 + k + 2, INF);
		Dis[k + 1] = 0;

		for (int i = 1; i <= k + 2; i++)
		{
			INT minVal = INF;
			INT minIndex = 0;
			for (int j = 1; j <= k + 2; j++)
			{
				if (!vis[j] && Dis[j] < minVal)
				{
					minVal = Dis[j];
					minIndex = j;
				}
			}
			if (!minIndex) break;
			vis[minIndex] = true;
			if (from[minIndex])
			{
				addEdge(from[minIndex], minIndex, Dis[minIndex]);
				addEdge(minIndex, from[minIndex], Dis[minIndex]);
			}

			for (int j = 1; j <= k + 2; j++)
			{
				if (!vis[j])
				{
					INT t = getDis(minIndex, j);
					if (Dis[j] > t)
					{
						Dis[j] = t;
						from[j] = minIndex;
					}
				}
			}
		}
	}

	double ans;

	void DFS(INT node = k + 1, INT parent = 0, INT mx = 0)
	{
		if (node == k + 2)
		{
			ans = mx;
			return;
		}
		for (int i = head[node]; i; i = edges[i].next)
		{
			Edge& e = edges[i];
			if (e.to == parent) continue;
			DFS(e.to, node, std::max(mx, e.cost));
			if (ans) return;
		}
	}

	AC() : ans(), from(), vis(), head()
	{
		Prim();
		DFS();
		printf("%.8f\n", std::sqrt(ans) / 2);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= k; i++)
	{
		points[i].x = readIn();
		points[i].y = readIn();
	}

	RunInstance(Eighty);
}

int main()
{
#ifndef JUDGE
	freopen("starway.in", "r", stdin);
	freopen("starway.out", "w", stdout);
#endif
	run();
	return 0;
}
