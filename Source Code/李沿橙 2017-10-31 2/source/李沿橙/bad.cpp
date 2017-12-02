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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
inline void printOut(INT x)
{
	char buffer[15];
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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = INT(2e5) + 5;
INT n, m;
INT origin[maxn];
INT la;

class SegTree
{
	struct Node
	{
		INT sum;
		INT min;
		INT max;

		bool reverse;
	} nodes[524300];
	INT g_Min, g_Max, g_Sum;
	INT g_L, g_R, g_Pos, g_Val;
	INT g_Type;
	enum
	{
		_add,
		_set
	};

#define PARAM INT node, INT l, INT r
#define DEF Node& c = nodes[node]; INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1
#define CNT node, l, r
#define LC lc, l, mid
#define RC rc, mid + 1, r

	void update(PARAM)
	{
		DEF;
		c.sum = nodes[lc].sum + nodes[rc].sum;
		c.min = std::min(nodes[lc].min, nodes[rc].min);
		c.max = std::max(nodes[lc].max, nodes[rc].max);
	}
	void cover(PARAM)
	{
		DEF;
		c.sum = -c.sum;
		c.max = -c.max;
		c.min = -c.min;
		std::swap(c.min, c.max);
		c.reverse = !c.reverse;
	}
	void pushdown(PARAM)
	{
		DEF;
		if (c.reverse)
		{
			cover(LC);
			cover(RC);
			c.reverse = false;
		}
	}
	void modify(PARAM)
	{
		DEF;
		if (l == r)
		{
			if (g_Type == _add)
			{
				c.sum += g_Val;
				c.max += g_Val;
				c.min += g_Val;
			}
			else if (g_Type == _set)
				c.max = c.min = c.sum = g_Val;
			return;
		}
		pushdown(CNT);
		if (g_Pos <= mid) modify(LC);
		else modify(RC);
		update(CNT);
	}
	void query(PARAM)
	{
		DEF;
		if (g_L <= l && r <= g_R)
		{
			g_Sum += c.sum;
			g_Min = std::min(g_Min, c.min);
			g_Max = std::max(g_Max, c.max);
			return;
		}
		pushdown(CNT);
		if (g_L <= mid) query(LC);
		if (g_R > mid) query(RC);
	}
	void reverse_(PARAM)
	{
		DEF;
		if (g_L <= l && r <= g_R)
		{
			cover(CNT);
			return;
		}
		pushdown(CNT);
		if (g_L <= mid) reverse_(LC);
		if (g_R > mid) reverse_(RC);
		update(CNT);
	}

public:
	void build(PARAM)
	{
		DEF;
		if (l == r)
		{
			c.min = c.max = c.sum = readIn();
			return;
		}
		build(LC);
		build(RC);
		update(CNT);
	}
	void add(INT pos, INT val)
	{
		g_Pos = pos;
		g_Val = val;
		g_Type = _add;
		modify(1, 1, n);
	}
	void set(INT pos, INT val)
	{
		g_Pos = pos;
		g_Val = val;
		g_Type = _set;
		modify(1, 1, n);
	}
	void reverse(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		reverse_(1, 1, n);
	}

	INT querySum(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		g_Sum = 0;
		query(1, 1, n);
		return g_Sum;
	}
	INT queryMax(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		g_Max = -INF;
		query(1, 1, n);
		return g_Max;
	}
	INT queryMin(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		g_Min = INF;
		query(1, 1, n);
		return g_Min;
	}
} st;

void run()
{
	n = readIn();
	m = readIn();

	st.build(1, 1, n);
	while (m--)
	{
		INT ins = readIn();
		INT l, r, val;
		switch (ins)
		{
		case 1:
		case 2:
		{
			l = readIn();
			l = (l ^ la) % n + 1;
			val = readIn();
			break;
		}
		case 3:
		case 4:
		case 5:
		case 6:
		{
			l = readIn();
			r = readIn();
			l = (l ^ la) % n + 1;
			r = (r ^ la) % n + 1;
			if (l > r) std::swap(l, r);
			break;
		}
		}

		if (ins == 1)
			st.set(l, val);
		else if (ins == 2)
			st.add(l, val);
		else if (ins == 3)
			st.reverse(l, r);
		else if (ins == 4)
		{
			la = st.queryMax(l, r);
			printOut(la);
			la = std::abs(la);
		}
		else if (ins == 5)
		{
			la = st.queryMin(l, r);
			printOut(la);
			la = std::abs(la);
		}
		else if (ins == 6)
		{
			la = st.querySum(l, r);
			printOut(la);
			la = std::abs(la);
		}
	}
}

int main()
{
#ifndef JUDGE
	freopen("bad.in", "r", stdin);
	freopen("bad.out", "w", stdout);
#endif
	run();
	return 0;
}
