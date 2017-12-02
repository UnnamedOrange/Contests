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

const INT maxn = 1e5 + 5;
const INT maxm = 2e5 + 5;
INT n, m;
struct edge
{
	INT from;
	INT to;
	INT cost;

	bool selected;

	bool operator< (const edge& b) const
	{
		return cost < b.cost;
	}
} edges[maxm];

class DS
{
	std::vector<INT> parent;

	INT find(INT x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}

public:
	DS(INT size) : parent(size + 1)
	{
		for (int i = 1; i <= size; i++)
		{
			parent[i] = i;
		}
	}

	void unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		parent[py] = px;
	}

	bool judge(INT x, INT y)
	{
		return find(x) == find(y);
	}
};

struct edge2
{
	INT to;
	INT cost;
	INT next;

	edge2(INT to = 0, INT cost = 0) : to(to), cost(cost)
	{
	}
} E[maxm * 2];
INT count_;
INT head[maxn];
inline void addEdge(INT from, INT to, INT cost)
{
	count_++;
	E[count_].to = to;
	E[count_].cost = cost;
	E[count_].next = head[from];
	head[from] = count_;
}

INT depth[maxn];
INT next[18][maxn];
INT maxEdge[18][maxn];

void init()
{
	memset(depth, 0, sizeof(depth));
	std::queue<INT> q;
	depth[1] = 1;
	q.push(1);
	while (!q.empty())
	{
		INT from = q.front();
		q.pop();
		for (int i = head[from]; i; i = E[i].next)
		{
			INT to = E[i].to;
			INT cost = E[i].cost;
			if (depth[to]) continue;
			depth[to] = depth[from] + 1;
			next[0][to] = from;
			maxEdge[0][to] = cost;
			q.push(to);
		}
	}

	for (int i = 1; i <= 17; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			next[i][j] = next[i - 1][next[i - 1][j]];
			maxEdge[i][j] = std::max(maxEdge[i - 1][j], maxEdge[i - 1][next[i - 1][j]]);
		}
	}
}

INT lca(INT u, INT v)
{
	INT ans = 0;
	if (depth[u] < depth[v]) std::swap(u, v);
	for (int i = 17; ~i; i--)
	{
		if (depth[next[i][u]] < depth[v]) continue;
		ans = std::max(ans, maxEdge[i][u]);
		u = next[i][u];
	}

	if (u != v)
	{
		for (int i = 17; ~i; i--)
		{
			if (next[i][u] == next[i][v]) continue;
			ans = std::max(ans, maxEdge[i][u]);
			ans = std::max(ans, maxEdge[i][v]);
			u = next[i][u];
			v = next[i][v];
		}

		ans = std::max(ans, maxEdge[0][u]);
		ans = std::max(ans, maxEdge[0][v]);
	}
	return ans;
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		for (int i = 1; i <= m; i++)
		{
			edges[i].from = readIn();
			edges[i].to = readIn();
			edges[i].cost = readIn();
			edges[i].selected = false;
		}
		std::sort(edges + 1, edges + 1 + m);

		long long ans = 0;
		INT count_ = 1;
		DS ds(n);
		count_ = 0;
		memset(head, 0, sizeof(head));
		for (int i = 1; i <= m; i++)
		{
			if (!ds.judge(edges[i].from, edges[i].to))
			{
				ans += edges[i].cost;
				edges[i].selected = true;
				addEdge(edges[i].from, edges[i].to, edges[i].cost);
				addEdge(edges[i].to, edges[i].from, edges[i].cost);
				ds.unite(edges[i].from, edges[i].to);
				count_++;
			}
			if (count_ == n) break;
		}
		cout << ans << endl;

		init();
		bool bExist = false;
		for (int i = 1; i <= m; i++)
		{
			if (edges[i].selected) continue;
			INT longest = lca(edges[i].from, edges[i].to);

			if (longest == edges[i].cost)
			{
				bExist = true;
				break;
			}
		}
		cout << (bExist ? "No" : "Yes") << endl;
	}
}

int main()
{
	run();
	return 0;
}