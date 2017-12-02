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

const INT maxn = INT(5e5) + 5;
INT n;
INT cost[maxn];
INT parent[maxn];

struct Edge
{
	INT to;

	INT next;
} edges[maxn];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i = 0;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

#define RunInstance(x) delete new x
struct work
{
	INT size;
	INT stack[20][maxn];
	INT depth[maxn];
	double ans[maxn];

	double slope(INT x, INT y)
	{
		return double(cost[y] - cost[x]) / (depth[x] - depth[y]);
	}

	struct queue
	{
		INT head;
		INT tail;
		INT s[maxn];

		queue() : head(), tail() {}
		bool empty()
		{
			return head == tail;
		}
		INT front()
		{
			return s[head];
		}
		void pop()
		{
			head = (head + 1) % maxn;
		}
		void push(INT x)
		{
			s[tail++] = x;
		}
	} q;

	void BFS()
	{
		q.push(1);
		while (!q.empty())
		{
			INT from = q.front();
			q.pop();

			depth[from] = depth[parent[from]] + 1;

			if (from != 1)
			{
				stack[0][from] = parent[from];
				for (int i = 1; i <= size; i++) stack[i][from] = stack[i - 1][stack[i - 1][from]];

				INT u = from;
				for (int i = size; ~i; i--)
				{
					INT v = stack[i][u];
					INT pv = stack[0][v];
					if (!stack[0][v] ||
						(cost[v] - cost[from]) * (depth[v] - depth[pv]) <= (cost[pv] - cost[v]) * (depth[from] - depth[v]))
						continue;
					u = v;
				}
				u = stack[0][u];

				ans[from] = slope(from, u);

				stack[0][from] = u;
				for (int i = 1; i <= size; i++) stack[i][from] = stack[i - 1][stack[i - 1][from]];
			}

			for (int i = head[from]; i; i = edges[i].next)
			{
				q.push(edges[i].to);
			}
		}
	}

	work() : size(), stack(), depth()
	{
		while (1 << size < n) size++;
		BFS();
		for (int i = 2; i <= n; i++) printf("%.10f\n", ans[i]);
	}
};
struct cheat1
{
	static double calc(INT node)
	{
		double ret = 1e100;
		INT p = parent[node];
		INT dis = 1;
		while (p)
		{
			if (ret > (double)(cost[p] - cost[node]) / dis)
			{
				ret = (double)(cost[p] - cost[node]) / dis;
			}
			p = parent[p];
			dis++;
		}
		return ret;
	}

	cheat1()
	{
		for (int i = 2; i <= n; i++)
		{
			printf("%.10f\n", calc(i));
		}
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++) cost[i] = readIn();
	for (int i = 2; i <= n; i++) addEdge(parent[i] = readIn(), i);

	//	if (n <= 500) RunInstance(cheat1);
	//	else
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("lost.in", "r", stdin);
	freopen("lost.out", "w", stdout);
#endif
	run();
	return 0;
}
