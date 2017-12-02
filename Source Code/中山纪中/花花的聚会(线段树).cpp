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
INT n, m;
INT parent[maxn];
INT depth[maxn];

INT headR[maxn];
INT R[maxn];
INT nextR[maxn];

struct ticket
{
	INT w;
	INT k;

	INT next;
} tickets[maxn];
INT headT[maxn];

INT f[maxn];
std::vector<INT> seq;
class SegTree
{
	std::vector<INT> tree;
	INT g_L, g_R;
	INT g_Pos, g_Val;

	void set_(INT node = 1, INT l = 1, INT r = n)
	{
		if (l == r)
		{
			tree[node] = g_Val;
			return;
		}
		INT mid = (l + r) >> 1;
		INT lc = node << 1;
		INT rc = lc | 1;
		if (g_Pos <= mid) set_(lc, l, mid);
		if (g_Pos > mid) set_(rc, mid + 1, r);
		tree[node] = std::min(tree[lc], tree[rc]);
	}
	INT query_(INT node = 1, INT l = 1, INT r = n)
	{
		if (g_L <= l && r <= g_R)
		{
			return tree[node];
		}
		INT mid = (l + r) >> 1;
		INT lc = node << 1;
		INT rc = lc | 1;
		INT ans = 0x7fffffff;
		if (g_L <= mid) ans = std::min(ans, query_(lc, l, mid));
		if (g_R > mid) ans = std::min(ans, query_(rc, mid + 1, r));
		return ans;
	}

public:
	SegTree() : tree(262150)
	{
	}

	void set(INT pos, INT val)
	{
		g_Pos = pos;
		g_Val = val;
		set_();
	}
	INT query(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		return query_();
	}
} sg;

void dfs(INT node = 1)
{
	if (node != 1)
	{
		for (int i = headT[node]; i; i = tickets[i].next)
		{
			INT cost = tickets[i].w + sg.query(std::max(1, depth[node] - tickets[i].k), depth[node] - 1);
			if (f[node] == -1 || cost < f[node])
			{
				f[node] = cost;
			}
		}
	}
	sg.set(depth[node], f[node]);
	for (int i = headR[node]; i; i = nextR[i])
	{
		INT to = R[i];
		if (to == parent[node]) continue;
		depth[to] = depth[node] + 1;
		dfs(to);
	}
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n - 1; i++)
	{
		INT from = readIn();
		INT to = readIn();
		parent[from] = to;

		R[i] = from;
		nextR[i] = headR[to];
		headR[to] = i;
	}
	for (int i = 1; i <= m; i++)
	{
		INT city = readIn();
		tickets[i].k = readIn();
		tickets[i].w = readIn();
		tickets[i].next = headT[city];
		headT[city] = i;
	}

	memset(f, -1, sizeof(f));
	f[1] = 0;
	depth[1] = 1;
	dfs();

	INT q = readIn();
	while (q--)
	{
		printf("%d\n", f[readIn()]); //INT is int here
	}
}

int main()
{
	run();
	return 0;
}
