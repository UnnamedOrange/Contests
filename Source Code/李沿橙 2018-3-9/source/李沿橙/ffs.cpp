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
}

const int INF = (~(int(1) << (sizeof(int) * 8 - 1)));
const int maxn = 100005;
int n;
int a[maxn];

int temp[maxn];
int maxRight[maxn];
int minLeft[maxn];

int mins[maxn];
int maxs[maxn];
struct SegTree
{
	struct Node
	{
		int lazy;
		int min;
	} nodes[maxn * 2];
	inline static int code(int l, int r) { return (l + r) | (l != r); }
#define PARAM int l, int r
#define DEF int mid = (l + r) >> 1
#define CNT l, r
#define LC l, mid
#define RC mid + 1, r

	int g_L, g_R, g_Val;
	void cover(PARAM, int v)
	{
		Node& t = nodes[code(CNT)];
		t.min += v;
		t.lazy += v;
	}
	void update(PARAM)
	{
		DEF;
		Node& t = nodes[code(CNT)];
		Node& lc = nodes[code(LC)];
		Node& rc = nodes[code(RC)];
		t.min = std::min(lc.min, rc.min);
	}
	void pushdown(PARAM)
	{
		Node& t = nodes[code(CNT)];
		if (!t.lazy) return;
		DEF;
		Node& lc = nodes[code(LC)];
		Node& rc = nodes[code(RC)];
		lc.lazy += t.lazy;
		rc.lazy += t.lazy;
		lc.min += t.lazy;
		rc.min += t.lazy;
		t.lazy = 0;
	}
	void add_(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			cover(CNT, g_Val);
			return;
		}
		DEF;
		pushdown(CNT);
		if (g_L <= mid) add_(LC);
		if (g_R > mid) add_(RC);
		update(CNT);
	}
	int query_(PARAM)
	{
		if (g_L <= l && r <= g_R && nodes[code(l, r)].min != g_Val)
			return -1;
		if (l == r)
		{
			if (nodes[code(l, r)].min == g_Val)
				return l;
			else
				return -1;
		}
		DEF;
		pushdown(CNT);
		int ret = -1;
		if (g_R > mid) ret = query_(RC);
		if (~ret) return ret;
		if (g_L <= mid) return query_(LC);
		else return -1;
	}

public:
	void add(int l, int r, int val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		add_(1, n);
	}
	int query(int l, int r, int val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		return query_(1, n);
	}
	void clear()
	{
		memset(nodes, 0, sizeof(nodes));
	}
} st;
struct SegTree2
{
	struct Node
	{
		int lazy;
		int max;
		int min;
	} nodes[maxn * 2];
	inline static int code(int l, int r) { return (l + r) | (l != r); }

	int g_L, g_R, g_Val;
	void cover(PARAM, int v)
	{
		Node& t = nodes[code(CNT)];
		t.min = v;
		t.max = v;
		t.lazy = v;
	}
	void update(PARAM)
	{
		DEF;
		Node& t = nodes[code(CNT)];
		Node& lc = nodes[code(LC)];
		Node& rc = nodes[code(RC)];
		t.max = std::max(lc.max, rc.max);
		t.min = std::min(lc.min, rc.min);
	}
	void pushdown(PARAM)
	{
		Node& t = nodes[code(CNT)];
		if (!~t.lazy) return;
		DEF;
		Node& lc = nodes[code(LC)];
		Node& rc = nodes[code(RC)];
		lc.lazy = t.lazy;
		rc.lazy = t.lazy;
		lc.max = t.lazy;
		rc.max = t.lazy;
		lc.min = t.lazy;
		rc.min = t.lazy;
		t.lazy = -1;
	}
	void set_(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			cover(CNT, g_Val);
			return;
		}
		DEF;
		pushdown(CNT);
		if (g_L <= mid) set_(LC);
		if (g_R > mid) set_(RC);
		update(CNT);
	}
	int queryMax_(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			return nodes[code(l, r)].max;
		}
		DEF;
		pushdown(CNT);
		int ret = 0;
		if (g_L <= mid) ret = std::max(ret, queryMax_(LC));
		if (g_R > mid) ret = std::max(ret, queryMax_(RC));
		return ret;
	}
	int queryMin_(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			return nodes[code(l, r)].min;
		}
		DEF;
		pushdown(CNT);
		int ret = INF;
		if (g_L <= mid) ret = std::min(ret, queryMin_(LC));
		if (g_R > mid) ret = std::min(ret, queryMin_(RC));
		return ret;
	}

public:
	void set(int l, int r, int val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		set_(1, n);
	}
	int queryMin(int l, int r)
	{
		g_L = l;
		g_R = r;
		return queryMin_(1, n);
	}
	int queryMax(int l, int r)
	{
		g_L = l;
		g_R = r;
		return queryMax_(1, n);
	}
	void clear()
	{
		for (int i = 0; i < maxn * 2; i++)
		{
			nodes[i].lazy = -1;
			nodes[i].max = 0;
			nodes[i].min = 1000000;
		}
	}
} st2;
void solve(int ans[maxn])
{
	mins[0] = 0;
	maxs[0] = 0;
	st.clear();
	for (int i = n; i; i--)
	{
		st.add(i, i, -i);

		while (mins[0] && a[i] < a[mins[mins[0]]])
		{
			int pos = mins[0] >= 2 ? mins[mins[0] - 1] : n + 1;
			int val = a[mins[mins[0]]];
			mins[0]--;
			if (i < pos) st.add(i + 1, pos - 1, val - a[i]);
		}
		mins[++mins[0]] = i;

		while (maxs[0] && a[i] > a[maxs[maxs[0]]])
		{
			int pos = maxs[0] >= 2 ? maxs[maxs[0] - 1] : n + 1;
			int val = a[maxs[maxs[0]]];
			maxs[0]--;
			if (i < pos) st.add(i + 1, pos - 1, a[i] - val);
		}
		maxs[++maxs[0]] = i;

		ans[i] = st.query(i, n, -i);
	}
}

int m;
int query[maxn][2];
int ans[maxn][2];

std::vector<int> lq[maxn];
std::vector<int> rq[maxn];

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	solve(maxRight);
	std::reverse(a + 1, a + 1 + n);
	solve(temp);
	std::reverse(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++)
		minLeft[n + 1 - i] = n + 1 - temp[i];

	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		lq[query[i][0] = readIn()].push_back(i);
		rq[query[i][1] = readIn()].push_back(i);
	}

	for (int i = 1; i <= n; i++)
	{
		st2.set(i, maxRight[i], i);
		for (int j = 0; j < lq[i].size(); j++)
			ans[lq[i][j]][0] = st2.queryMax(query[lq[i][j]][1], n);
	}
	st2.clear();
	for (int i = n; i >= 1; i--)
	{
		st2.set(minLeft[i], i, i);
		for (int j = 0; j < rq[i].size(); j++)
			ans[rq[i][j]][1] = st2.queryMin(1, query[rq[i][j]][0]);
	}
	for (int i = 1; i <= m; i++)
	{
		printOut(ans[i][0]);
		putchar(' ');
		printOut(ans[i][1]);
		putchar('\n');
	}
}

int main()
{
#ifndef LOCAL
	freopen("ffs.in", "r", stdin);
	freopen("ffs.out", "w", stdout);
#endif
	run();
	return 0;
}