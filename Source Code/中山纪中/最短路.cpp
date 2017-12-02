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

INT n, m, q;

void cheat1()
{
	INT rect[105][105];
	memset(rect, 0x3f, sizeof(rect));
	for (int i = 1; i <= n; i++)
	{
		rect[i][i] = 0;
	}

	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		rect[from][to] = std::min(rect[from][to], cost);
		rect[to][from] = std::min(rect[to][from], cost);
	}

	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (k != i && i != j && k != j)
				{
					rect[i][j] = std::min(rect[i][j], rect[i][k] + rect[k][j]);
				}
			}
		}
	}

	while (q--)
	{
		printf("%lld\n", rect[readIn()][readIn()]); //INT is long long here
	}
}

namespace C2
{
	struct edge
	{
		INT to;
		INT cost;
		edge(INT to = 0, INT cost = 0) : to(to), cost(cost)
		{
		}
	};
	std::vector<std::vector<edge> > edges;
	INT size;
	std::vector<INT> depth;
	std::vector<std::vector<INT> > next;
	std::vector<std::vector<INT> > length;
}
void dfs(INT node = 1)
{
	using namespace C2;
	for (int i = 0; i < edges[node].size(); i++)
	{
		INT to = edges[node][i].to;
		INT cost = edges[node][i].cost;
		if (to == next[0][node]) continue;
		depth[to] = depth[node] + 1;
		next[0][to] = node;
		length[0][to] = cost;
		dfs(to);
	}
}
void cheat2()
{
	using namespace C2;
	edges.resize(n + 1);
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT cost = readIn();
		edges[from].push_back(edge(to, cost));
		edges[to].push_back(edge(from, cost));
	}

	while (1 << size < n) size++;
	next.resize(size + 1);
	length.resize(size + 1);
	for (int i = 0; i <= size; i++)
	{
		next[i].resize(n + 1);
		length[i].resize(n + 1);
	}
	depth.resize(n + 1);
	depth[1] = 1;
	dfs();

	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			next[i][j] = next[i - 1][next[i - 1][j]];
			length[i][j] = length[i - 1][j] + length[i - 1][next[i - 1][j]];
		}
	}

	while (q--)
	{
		INT from = readIn();
		INT to = readIn();
		INT ans = 0;

		if (depth[from] < depth[to]) std::swap(from, to);
		for (int i = size; ~i; i--)
		{
			if (depth[next[i][from]] < depth[to]) continue;
			ans += length[i][from];
			from = next[i][from];
		}

		if (from != to)
		{
			for (int i = size; ~i; i--)
			{
				if (next[i][from] == next[i][to]) continue;
				ans += length[i][from] + length[i][to];
				from = next[i][from];
				to = next[i][to];
			}
			ans += length[0][from] + length[0][to];
		}
		printf("%lld\n", ans); //INT is long long here
	}
}

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	if (n <= 100)
	{
		cheat1();
		return;
	}
	else if (m == n - 1)
	{
		cheat2();
		return;
	}
}

int main()
{
	run();
	return 0;
}
