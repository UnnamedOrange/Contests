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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = 255;
INT n, m, w;
struct Point
{
	INT x;
	INT y;
	void read()
	{
		x = readIn();
		y = readIn();
	}
} points[maxn];
struct Circle
{
	INT r;
	INT c;
	void read()
	{
		r = readIn();
		c = readIn();
	}
	bool operator< (const Circle& b) const
	{
		if (r != b.r) return r < b.r;
		return c < b.c;
	}
} circles[maxn];

#define MP(x, y) (((x) - 1) * (m + 1) + (y))
#define ST() (n * (m + 1))
#define ED() (n * (m + 1) + 1)

#define RunInstance(x) delete new x
struct brute
{
	static const INT maxN = 40;
	struct Edge
	{
		INT to;
		INT cost;
		INT next;
	} edges[3 * maxN * maxN * maxN * maxN];
	INT head[maxN * maxN + 5];
	void addEdge(INT from, INT to, INT cost)
	{
		static INT i;
		i++;
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
	}

	INT dis[maxN * maxN + 5];
	INT SPFA()
	{
		std::fill(dis, dis + maxN * maxN + 5, INF);
		dis[ST()] = 0;
		std::vector<bool> inq(maxN * maxN + 5);
		std::queue<INT> q;
		q.push(ST());
		inq[ST()] = true;
		while (!q.empty())
		{
			INT from = q.front();
			q.pop();
			inq[from] = false;
			for (int i = head[from]; i; i = edges[i].next)
			{
				Edge& e = edges[i];
				INT to = e.to;
				if (dis[from] + e.cost < dis[to])
				{
					dis[to] = dis[from] + e.cost;
					if (!inq[to])
					{
						q.push(to);
						inq[to] = true;
					}
				}
			}
		}
		return dis[ED()];
	}

	brute() : head()
	{
		for (int i = 1; i <= n; i++)
			for (int k = 1; k <= n; k++)
			{
				if (i == k) continue;
				long long X = points[i].x - points[k].x;
				long long Y = points[i].y - points[k].y;
				X *= X;
				Y *= Y;
				for (int j = 0; j <= m; j++)
					for (int l = 0; l <= m; l++)
					{
						INT r = circles[j].r + circles[l].r;
						if ((long long)r * r >= X + Y)
						{
							addEdge(MP(i, j), MP(k, l), circles[l].c);
						}
					}
			}

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				INT r = circles[j].r;
				if (r >= points[i].y)
					addEdge(ST(), MP(i, j), circles[j].c);
				if (r >= w - points[i].y)
					addEdge(MP(i, j), ED(), 0);
			}
		}

		INT ans = SPFA();
		if (ans < INF)
			printOut(ans);
		else
			puts("impossible");
	}
};
struct work
{
	INT M;

	struct Edge
	{
		INT to;
		INT cost;
		INT next;
	} edges[maxn * maxn * maxn + 5];
	INT head[maxn * maxn + 5];
	void addEdge(INT from, INT to, INT cost)
	{
		static INT i;
		i++;
		edges[i].to = to;
		edges[i].cost = cost;
		edges[i].next = head[from];
		head[from] = i;
	}

	struct HeapNode
	{
		INT node;
		INT dis;
		HeapNode() {}
		HeapNode(INT node, INT dis) : node(node), dis(dis) {}
		bool operator< (const HeapNode& b) const
		{
			return dis > b.dis;
		}
	};
	INT dis[maxn * maxn + 5];
	INT Dijkstra()
	{
		std::fill(dis, dis + maxn * maxn + 5, INF);
		dis[ST()] = 0;
		std::priority_queue<HeapNode> q;
		q.push(HeapNode(ST(), 0));
		while (!q.empty())
		{
			HeapNode from = q.top();
			q.pop();
			if (from.dis > dis[from.node]) continue;
			for (int i = head[from.node]; i; i = edges[i].next)
			{
				Edge& e = edges[i];
				INT to = e.to;
				if (dis[from.node] + e.cost < dis[to])
				{
					dis[to] = dis[from.node] + e.cost;
					q.push(HeapNode(to, dis[to]));
				}
			}
		}
		return dis[ED()];
	}
	work() : M()
	{
		for (int i = 1; i <= m; i++)
		{
			while (M && circles[i].c <= circles[M].c) M--;
			if (!M || circles[i].r > circles[M].r) circles[++M] = circles[i];
		}
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < M; j++)
				addEdge(MP(i, j), MP(i, j + 1), circles[j + 1].c - circles[j].c);

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				if (i == j) continue;
				long long X = points[i].x - points[j].x;
				long long Y = points[i].y - points[j].y;
				X *= X;
				Y *= Y;
				INT p = M;
				for (int k = 0; k <= M; k++)
				{
					INT r;
					while (p && (long long)(r = circles[p - 1].r + circles[k].r) * r >= X + Y)
						p--;
					if ((long long)(r = circles[p].r + circles[k].r) * r >= X + Y)
						addEdge(MP(i, k), MP(j, p), circles[p].c);
				}
			}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= M; j++)
			{
				INT r = circles[j].r;
				if (r >= points[i].y)
					addEdge(ST(), MP(i, j), circles[j].c);
				if (r >= w - points[i].y)
					addEdge(MP(i, j), ED(), 0);
			}

		INT ans = Dijkstra();
		if (ans < INF)
			printOut(ans);
		else
			puts("impossible");
	}
};

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		w = readIn();
		for (int i = 1; i <= n; i++)
			points[i].read();
		for (int i = 1; i <= m; i++)
			circles[i].read();
		std::sort(circles + 1, circles + 1 + m);

		RunInstance(work);
	}
}

int main()
{
#ifndef LOCAL
	freopen("river.in", "r", stdin);
	freopen("river.out", "w", stdout);
#endif
	run();
	return 0;
}
