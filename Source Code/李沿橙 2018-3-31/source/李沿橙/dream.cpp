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
typedef LL INT_PUT;
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

const int maxn = 500005;
LL lastans;
int n, m;
LL a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		while (m--)
		{
			int ins = readIn();
			if (ins == 1)
			{
				LL pos = readIn() ^ lastans;
				LL val = readIn() ^ lastans;
				a[pos] -= val;
				a[pos] = std::max(a[pos], 0ll);
			}
			else if (ins == 2)
			{
				LL l = readIn() ^ lastans;
				LL r = readIn() ^ lastans;
				LL x = readIn() ^ lastans;
				for (int i = l; i <= r; i++)
					a[i] = std::min(a[i], x);
			}
			else if (ins == 3)
			{
				LL l = readIn() ^ lastans;
				LL r = readIn() ^ lastans;
				lastans = 0;
				for (int i = l; i <= r; i++)
					lastans += a[i];
				printOut(lastans);
			}
		}
	}
};
struct work
{
	class SegTree
	{
		inline static int code(int l, int r) { return (l + r) | (l != r); }
		struct Node
		{
			LL sum;
			LL major;
			LL minor;
			LL nMajor;
			LL lazy;
			Node() : lazy(-1) {}
		} nodes[maxn * 2];

#define PARAM int l, int r
#define DEF int mid = (l + r) >> 1
#define CNT l, r
#define LC l, mid
#define RC mid + 1, r

		void update(PARAM)
		{
			Node& t = nodes[code(CNT)];
			DEF;
			Node& lc = nodes[code(LC)];
			Node& rc = nodes[code(RC)];
			t.sum = lc.sum + rc.sum;
			if (lc.major > rc.major)
			{
				t.major = lc.major;
				t.nMajor = lc.nMajor;
				t.minor = std::max(lc.minor, rc.major);
			}
			else if (lc.major < rc.major)
			{
				t.major = rc.major;
				t.nMajor = rc.nMajor;
				t.minor = std::max(lc.major, rc.minor);
			}
			else
			{
				t.major = lc.major;
				t.nMajor = lc.nMajor + rc.nMajor;
				t.minor = std::max(lc.minor, rc.minor);
			}
		}
		LL g_Pos, g_Val, g_L, g_R;
		void cover(PARAM, LL val)
		{
			Node& t = nodes[code(CNT)];
			if (t.major <= val) return;
			t.sum -= t.nMajor * (t.major - val);
			t.major = val;
			t.lazy = val;
		}
		void pushdown(PARAM)
		{
			Node& t = nodes[code(CNT)];
			if (~t.lazy)
			{
				DEF;
				cover(LC, t.lazy);
				cover(RC, t.lazy);
				t.lazy = -1;
			}
		}
		void modify_(PARAM)
		{
			if (l == r)
			{
				Node& t = nodes[code(CNT)];
				t.major = t.sum = std::max(0ll, t.sum - g_Val);
				t.minor = -1;
				t.nMajor = 1;
				return;
			}
			pushdown(CNT);
			DEF;
			if (g_Pos <= mid) modify_(LC);
			if (g_Pos > mid) modify_(RC);
			update(CNT);
		}
		void setmin_(PARAM)
		{
			Node& t = nodes[code(CNT)];
			if (t.major <= g_Val) return;
			if (g_L <= l && r <= g_R && t.minor < g_Val)
			{
				cover(CNT, g_Val);
				return;
			}
			pushdown(CNT);
			DEF;
			if (g_L <= mid) setmin_(LC);
			if (g_R > mid) setmin_(RC);
			update(CNT);
		}
		LL query_(PARAM)
		{
			if (g_L <= l && r <= g_R)
			{
				Node& t = nodes[code(CNT)];
				return t.sum;
			}
			pushdown(CNT);
			DEF;
			LL ret = 0;
			if (g_L <= mid) ret += query_(LC);
			if (g_R > mid) ret += query_(RC);
			return ret;
		}

	public:
		void build(int l, int r)
		{
			Node& t = nodes[code(CNT)];
			if (l == r)
			{
				t.sum = t.major = a[l];
				t.minor = -1;
				t.nMajor = 1;
				return;
			}
			DEF;
			build(LC); build(RC);
			update(CNT);
		}
		void modify(LL pos, LL val)
		{
			g_Pos = pos;
			g_Val = val;
			modify_(1, n);
		}
		void setmin(LL l, LL r, LL val)
		{
			g_L = l;
			g_R = r;
			g_Val = val;
			setmin_(1, n);
		}
		LL query(LL l, LL r)
		{
			g_L = l;
			g_R = r;
			return query_(1, n);
		}
	} st;

	work()
	{
		st.build(1, n);
		while (m--)
		{
			int ins = readIn();
			if (ins == 1)
			{
				LL pos = readIn() ^ lastans;
				LL val = readIn() ^ lastans;
				st.modify(pos, val);
			}
			else if (ins == 2)
			{
				LL l = readIn() ^ lastans;
				LL r = readIn() ^ lastans;
				LL x = readIn() ^ lastans;
				st.setmin(l, r, x);
			}
			else if (ins == 3)
			{
				LL l = readIn() ^ lastans;
				LL r = readIn() ^ lastans;
				printOut(lastans = st.query(l, r));
			}
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	if (n <= 3000 && m <= 3000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
#endif
	run();
	return 0;
}