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
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	char buffer[8];
	INT length = 0;
	while (x)
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 200005;
const INT maxm = maxn * 2;
INT n, m, q;
INT count_;
INT head[maxn];
INT To[maxm];
INT next[maxm];
void addEdge(INT from, INT to)
{
	count_++;
	To[count_] = to;
	next[count_] = head[from];
	head[from] = count_;
}

INT depth[maxn];
INT parent[maxn];
INT size[maxn];
INT heavy[maxn];
INT top[maxn];
INT Index[maxn];

void dfs1(INT node = 1)
{
	size[node] = 1;
	INT maxVal = 0;
	INT maxIndex = 0;
	for (int i = head[node]; i; i = next[i])
	{
		INT to = To[i];
		if (to == parent[node]) continue;
		parent[to] = node;
		depth[to] = depth[node] + 1;
		dfs1(to);
		if (size[to] > maxVal)
		{
			maxVal = size[to];
			maxIndex = to;
		}
		size[node] += size[to];
	}
	heavy[node] = maxIndex;
}
void dfs2(INT node = 1, INT heavyTop = 0)
{
	Index[node] = ++Index[0];
	heavyTop = heavyTop ? heavyTop : node;
	top[node] = heavyTop;
	if (heavy[node]) dfs2(heavy[node], heavyTop);
	for (int i = head[node]; i; i = next[i])
	{
		INT to = To[i];
		if (to == parent[node] || to == heavy[node]) continue;
		dfs2(to);
	}
}

enum
{
	MODIFY,
	QUERY
};
class SegTree
{
#define PARAM INT node = 1, INT l = 1, INT r = n
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1;

	INT tree[524300];
	INT lazy[524300];

	INT g_L, g_R, g_Pos;
	void pushdown(INT node, INT lc, INT rc)
	{
		if (lazy[node])
		{
			tree[lc] += lazy[node];
			tree[rc] += lazy[node];

			lazy[lc] += lazy[node];
			lazy[rc] += lazy[node];
			lazy[node] = 0;
		}
	}
	void update(INT node, INT lc, INT rc)
	{
		tree[node] = tree[lc] + tree[rc];
	}

	void addPoint_(PARAM)
	{
		if (l == r)
		{
			tree[node]++;
			return;
		}
		DEF;
		pushdown(node, lc, rc);
		if (g_Pos <= mid) addPoint_(lc, l, mid);
		if (g_Pos > mid) addPoint_(rc, mid + 1, r);
		update(node, lc, rc);
	}
	INT queryPoint_(PARAM)
	{
		if (l == r)
		{
			return tree[node];
		}
		DEF;
		pushdown(node, lc, rc);
		if (g_Pos <= mid) return queryPoint_(lc, l, mid);
		else return queryPoint_(rc, mid + 1, r);
	}

	void addItv_(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			tree[node]++;
			lazy[node]++;
			return;
		}
		DEF;
		pushdown(node, lc, rc);
		if (g_L <= mid) addItv_(lc, l, mid);
		if (g_R > mid) addItv_(rc, mid + 1, r);
		update(node, lc, rc);
	}
	INT queryItv_(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			return tree[node];
		}
		DEF;
		pushdown(node, lc, rc);
		INT ret = 0;
		if (g_L <= mid) ret += queryItv_(lc, l, mid);
		if (g_R > mid) ret += queryItv_(rc, mid + 1, r);
		return ret;
	}

public:
	void addItv(INT x, INT y)
	{
		g_L = Index[x];
		g_R = Index[y];
		if (g_L > g_R) std::swap(g_L, g_R);
		return addItv_();
	}
	void addPoint(INT x)
	{
		g_Pos = Index[x];
		addPoint_();
	}
	INT queryItv(INT x, INT y)
	{
		g_L = Index[x];
		g_R = Index[y];
		if (g_L > g_R) std::swap(g_L, g_R);
		return queryItv_();
	}
	INT queryPoint(INT x)
	{
		g_Pos = Index[x];
		return queryPoint_();
	}
} st1, st2;

INT driver(INT x, INT y, INT type, INT& LCA)
{
	INT ret = 0;
	while (top[x] != top[y])
	{
		if (depth[top[x]] < depth[top[y]]) std::swap(x, y);
		if (type == MODIFY) st1.addItv(top[x], x);
		else if (type == QUERY) ret += st2.queryItv(top[x], x);
		x = parent[top[x]];
	}
	if (depth[x] > depth[y]) std::swap(x, y);
	if (type == MODIFY) st1.addItv(x, y);
	else if (type == QUERY) ret += st2.queryItv(x, y);
	LCA = x;
	return ret;
}

INT lca[maxn];

void run()
{
	n = readIn();
	m = n - 1;
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to);
		addEdge(to, from);
	}
	dfs1();
	dfs2();

	q = readIn();
	while (q--)
	{
		INT from = readIn();
		INT to = readIn();
		INT ans = 0;
		INT LCA = 0;
		ans += driver(from, to, QUERY, LCA);
		ans += st1.queryPoint(LCA);
		printOut(ans - lca[LCA]);
		lca[LCA]++;
		driver(from, to, MODIFY, LCA);
		st2.addPoint(LCA);
	}
}

int main()
{
	run();
	return 0;
}