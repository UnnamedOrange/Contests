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

const INT maxn = 100005;
INT n, q;
INT origin[maxn];

class SegTree
{
	std::vector<INT> tree;

	INT g_L, g_R;
	INT g_Pos, g_Val;

	INT query_(INT node = 1, INT l = 1, INT r = n - 1)
	{
		if (g_L <= l && r <= g_R)
		{
			return tree[node];
		}
		INT mid = (l + r) >> 1;
		INT lc = node << 1;
		INT rc = lc | 1;
		INT ans = 0;
		if (g_L <= mid) ans = std::max(ans, query_(lc, l, mid));
		if (g_R > mid) ans = std::max(ans, query_(rc, mid + 1, r));
		return ans;
	}

	void set_(INT node = 1, INT l = 1, INT r = n - 1)
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
		tree[node] = std::max(tree[lc], tree[rc]);
	}

	void build(INT node = 1, INT l = 1, INT r = n - 1)
	{
		if (l == r)
		{
			tree[node] = std::abs(origin[l] - origin[l + 1]);
			return;
		}
		INT mid = (l + r) >> 1;
		INT lc = node << 1;
		INT rc = lc | 1;
		build(lc, l, mid);
		build(rc, mid + 1, r);
		tree[node] = std::max(tree[lc], tree[rc]);
	}

public:
	SegTree() : tree(262150)
	{
	}

	void init()
	{
		build();
	}

	void set(INT pos, INT val)
	{
		origin[pos] = val;
		if (pos - 1 >= 1)
		{
			g_Pos = pos - 1;
			g_Val = std::abs(origin[pos] - origin[pos - 1]);
			set_();
		}
		if (pos + 1 <= n)
		{
			g_Pos = pos;
			g_Val = std::abs(origin[pos] - origin[pos + 1]);
			set_();
		}
	}

	INT query(INT l, INT r)
	{
		g_L = l;
		g_R = r - 1;
		return query_();
	}
} st;

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
	}
	st.init();

	q = readIn();
	while (q--)
	{
		INT ins = readIn();
		INT param1 = readIn();
		INT param2 = readIn();
		if (ins == 0)
		{
			st.set(param1, param2);
		}
		else if (ins == 1)
		{
			printf("%d\n", st.query(param1, param2));
		}
	}
}

int main()
{
#ifndef JUDGE
	freopen("lipschitz.in", "r", stdin);
	freopen("lipschitz.out", "w", stdout);
#endif
	run();
	return 0;
}
