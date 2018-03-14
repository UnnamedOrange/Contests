#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int U = (1 << 20) - 1;
const int maxn = 200005;
int n, q;
int a[maxn];

class SegTree
{
	inline static int code(int l, int r)
	{
		return (l + r) | (l != r);
	}
	struct Node
	{
		int max;
		int sum_or;
		int sum_and;
		int lazy_or;
		int lazy_and;
		Node() : lazy_and(U) {}
	} nodes[maxn * 2];

#define PARAM int l, int r
#define DEF int mid = (l + r) >> 1
#define CNT l, r
#define LC l, mid
#define RC mid + 1, r

	int g_L, g_R, g_Val;
	void update(PARAM)
	{
		Node& t = nodes[code(CNT)];
		DEF;
		Node& lc = nodes[code(LC)];
		Node& rc = nodes[code(RC)];
		t.max = std::max(lc.max, rc.max);
		t.sum_and = lc.sum_and & rc.sum_and;
		t.sum_or = lc.sum_or | rc.sum_or;
	}
	void pushdown(PARAM)
	{
		Node& t = nodes[code(CNT)];
		DEF;
		Node& lc = nodes[code(LC)];
		Node& rc = nodes[code(RC)];
		if (U ^ t.lazy_and)
		{
			cover_and(LC, t.lazy_and);
			cover_and(RC, t.lazy_and);
			t.lazy_and = U;
		}
		if (t.lazy_or)
		{
			cover_or(LC, t.lazy_or);
			cover_or(RC, t.lazy_or);
			t.lazy_or = 0;
		}
	}
	void cover_and(PARAM, int val)
	{
		Node& t = nodes[code(CNT)];
		t.sum_and &= val;
		t.sum_or &= val;
		t.lazy_and &= val;
		t.lazy_or &= val;
		t.max &= val;
	}
	void cover_or(PARAM, int val)
	{
		Node& t = nodes[code(CNT)];
		t.sum_and |= val;
		t.sum_or |= val;
		t.lazy_or |= val;
		t.max |= val;
	}

	int query_(PARAM)
	{
		if (g_L <= l && r <= g_R) return nodes[code(CNT)].max;
		DEF;
		pushdown(CNT);
		int ret = 0;
		if (g_L <= mid) ret = std::max(ret, query_(LC));
		if (g_R > mid) ret = std::max(ret, query_(RC));
		return ret;
	}
	void and_(PARAM)
	{
		Node& t = nodes[code(CNT)];
		if (g_L <= l && r <= g_R && (t.sum_and & (U ^ g_Val)) == (t.sum_or & (U ^ g_Val)))
		{
			cover_and(CNT, g_Val);
			return;
		}
		DEF;
		pushdown(CNT);
		if (g_L <= mid) and_(LC);
		if (g_R > mid) and_(RC);
		update(CNT);
	}
	void or_(PARAM)
	{
		Node& t = nodes[code(CNT)];
		if (g_L <= l && r <= g_R && (t.sum_and & g_Val) == (t.sum_or & g_Val))
		{
			cover_or(CNT, g_Val);
			return;
		}
		DEF;
		pushdown(CNT);
		if (g_L <= mid) or_(LC);
		if (g_R > mid) or_(RC);
		update(CNT);
	}

public:
	void And(int l, int r, int val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		and_(1, n);
	}
	void Or(int l, int r, int val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		or_(1, n);
	}
	int query(int l, int r)
	{
		g_L = l;
		g_R = r;
		return query_(1, n);
	}
	void build(int l, int r)
	{
		if (l == r)
		{
			Node& t = nodes[code(l, r)];
			t.max = t.sum_and = t.sum_or = a[l];
			t.lazy_and = U;
			t.lazy_or = 0;
			return;
		}
		DEF;
		build(LC);
		build(RC);
		update(CNT);
	}
} st;

void run()
{
	n = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	st.build(1, n);

	while (q--)
	{
		int type = readIn();
		int l = readIn();
		int r = readIn();
		if (type == 1)
		{
			int x = readIn();
			st.And(l, r, x);
		}
		else if (type == 2)
		{
			int x = readIn();
			st.Or(l, r, x);
		}
		else if (type == 3)
		{
			printOut(st.query(l, r));
		}
	}
}

int main()
{
#ifndef LOCAL
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	run();
	return 0;
}