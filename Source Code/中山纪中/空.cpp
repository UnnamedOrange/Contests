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

const INT maxn = 200005;
INT n;
struct SegEx
{
	INT N;
	INT disc[maxn * 2];
	struct Seg
	{
		INT l;
		INT r;

		void read()
		{
			l = readIn();
			r = readIn();
		}
		bool operator< (const Seg& b) const
		{
			return l < b.l;
		}
	} segs[maxn];
	SegEx& read()
	{
		for (int i = 1; i <= n; i++)
		{
			segs[i].read();
		}
		return *this;
	}
	SegEx& discretize()
	{
		std::sort(segs + 1, segs + n + 1);
		for (int i = 1; i <= n; i++)
		{
			disc[++N] = segs[i].l;
			disc[++N] = segs[i].r;
		}
		std::sort(disc + 1, disc + N + 1);
		N = std::unique(disc + 1, disc + N + 1) - (disc + 1);
		for (int i = 1; i <= n; i++)
		{
			segs[i].l = std::lower_bound(disc + 1, disc + 1 + N, segs[i].l) - disc;
			segs[i].r = std::lower_bound(disc + 1, disc + 1 + N, segs[i].r) - disc;
		}
		return *this;
	}
} seg;

template <bool bMin>
class SegTree
{
#define PARAM INT node = 1, INT l = 1, INT r = seg.N
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1;
	INT tree[524300 * 2];

	INT g_L, g_R, g_Pos, g_Val;

	void update(PARAM)
	{
		DEF;
		tree[node] =
			bMin ?
			std::min(tree[lc], tree[rc]) :
			std::max(tree[lc], tree[rc]);
	}
	void set_(PARAM)
	{
		if (l == r)
		{
			tree[node] =
				bMin ?
				std::min(tree[node], g_Val) :
				std::max(tree[node], g_Val);
			return;
		}
		DEF;
		if (g_Pos <= mid) set_(lc, l, mid);
		if (g_Pos > mid) set_(rc, mid + 1, r);
		update(node, l, r);
	}
	INT query_(PARAM)
	{
		if (g_L <= l && r <= g_R)
		{
			return tree[node];
		}
		DEF;
		INT ans = bMin ? 0x7fffffff : 0;
		if (g_L <= mid)
		{
			INT temp = query_(lc, l, mid);
			if (bMin) ans = std::min(ans, temp);
			else ans = std::max(ans, temp);
		}
		if (g_R > mid)
		{
			INT temp = query_(rc, mid + 1, r);
			if (bMin) ans = std::min(ans, temp);
			else ans = std::max(ans, temp);
		}
		return ans;
	}

public:
	SegTree()
	{
		if (bMin) memset(tree, 0x7f, sizeof(tree));
	}

	void set(INT pos, INT x)
	{
		g_Pos = pos;
		g_Val = x;
		set_();
	}
	INT query(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		return query_();
	}
};
SegTree<true> stMin;
SegTree<false> stMax;

void run()
{
	n = readIn();
	seg.read().discretize();
	INT ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = std::max(ans, stMax.query(seg.segs[i].r + 1, seg.N) -
			(seg.disc[seg.segs[i].r] - seg.disc[seg.segs[i].l]));
		ans = std::max(ans,
			(seg.disc[seg.segs[i].r] + seg.disc[seg.segs[i].l]) -
			stMin.query(seg.segs[i].l, seg.segs[i].r));
		stMax.set(seg.segs[i].r, seg.disc[seg.segs[i].r] - seg.disc[seg.segs[i].l]);
		stMin.set(seg.segs[i].r, seg.disc[seg.segs[i].r] + seg.disc[seg.segs[i].l]);
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
