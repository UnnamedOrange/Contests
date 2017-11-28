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
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[9];
		INT length = 0;
		bool minus = x < 0;
		if (minus) x = -x;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = INT(2e5) + 5;
INT n, q;
INT origin[maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	bool unava[maxn];

	cheat1() : unava()
	{
		INT nStudent = 0;
		INT sum = 0;
		for (int i = 1; i <= n; i++)
		{
			nStudent += origin[i];
			sum += i * origin[i];
		}

		while (q--)
		{
			INT ins = readIn();
			switch (ins)
			{
			case 1:
			case 2:
			{
				INT pos = readIn();
				INT val = readIn();
				if (ins == 2) val = -val;
				origin[pos] += val;
				nStudent += val;
				sum += pos * val;
				break;
			}
			case 3:
			case 4:
			{
				INT l = readIn();
				INT r = readIn();
				bool t = false;
				if (ins == 4) t = true;
				for (int i = l; i <= r; i++) unava[i] = t;
				break;
			}
			}

			INT ans = -1;
			INT minDis = INF;
			INT left = 0;
			INT right = nStudent;
			INT dis = sum;
			for (int i = 1; i <= n; i++)
			{
				dis += left;
				dis -= right;
				left += origin[i];
				right -= origin[i];
				if (unava[i]) continue;
				if (dis < minDis)
				{
					ans = i;
					minDis = dis;
				}
			}
			printOut(ans);
		}
	}
};
struct cheat2
{
	INT nStudent;

	struct BIT
	{
#define lowbit(x) ((x) & -(x))
		INT bit[maxn];

		BIT() : bit() {}
		void add(INT x, INT val)
		{
			while (x <= n)
			{
				bit[x] += val;
				x += lowbit(x);
			}
		}
		INT operator() (INT x)
		{
			INT ret = 0;
			while (x > 0)
			{
				ret += bit[x];
				x -= lowbit(x);
			}
			return ret;
		}
		INT operator() (INT l, INT r)
		{
			return (*this)(r) - (*this)(l - 1);
		}
	} bit;

	INT divide()
	{
		INT l = 1, r = n;
		while (r - l > 0)
		{
			INT mid = l + ((r - l) >> 1);
			if (bit(mid) < (nStudent >> 1) + (nStudent & 1))
				l = mid + 1;
			else
				r = mid;
		}
		return l;
	}

	cheat2() : nStudent()
	{
		for (int i = 1; i <= n; i++)
		{
			bit.add(i, origin[i]);
			nStudent += origin[i];
		}

		while (q--)
		{
			INT ins = readIn();
			switch (ins)
			{
			case 1:
			case 2:
			{
				INT pos = readIn();
				INT val = readIn();
				if (ins == 2) val = -val;
				bit.add(pos, val);
				nStudent += val;
				break;
			}
			case 3:
			case 4:
			{
				readIn();
				readIn();
				break;
			}
			}
			printOut(divide());
		}
	}
};
struct work
{
	class SegTree
	{
#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1
	protected:
		struct Node
		{
			INT val;
			INT min;
			INT lazy;
			bool bLazy;
			Node() : val(), min(), lazy(), bLazy() {}
		} nodes[524300];

		INT g_Pos, g_L, g_R, g_Val;

		virtual void pushdown(PARAM) = 0;
		void add_(PARAM)
		{
			if (g_L <= l && r <= g_R)
			{
				nodes[node].min += g_Val;
				nodes[node].val += g_Val * (r - l + 1);
				nodes[node].lazy += g_Val;
				nodes[node].bLazy = true;
				return;
			}
			pushdown(node, l, r);
			DEF;
			if (g_L <= mid) add_(lc, l, mid);
			if (g_R > mid) add_(rc, mid + 1, r);
			nodes[node].val = nodes[lc].val + nodes[rc].val;
			nodes[node].min = std::min(nodes[lc].min, nodes[rc].min);
		}
		void modify_(PARAM)
		{
			if (g_L <= l && r <= g_R)
			{
				nodes[node].val = g_Val * (r - l + 1);
				nodes[node].lazy = g_Val;
				nodes[node].bLazy = true;
				return;
			}
			pushdown(node, l, r);
			DEF;
			if (g_L <= mid) modify_(lc, l, mid);
			if (g_R > mid) modify_(rc, mid + 1, r);
			nodes[node].val = nodes[lc].val + nodes[rc].val;
		}
		INT queryLeft_(PARAM)
		{
			if (l == r)
			{
				if (nodes[node].val) return 0;
				return l;
			}
			if (g_L <= l && r <= g_R)
			{
				if (!nodes[node].val) return l;
				else if (nodes[node].val == r - l + 1) return 0;
			}
			pushdown(node, l, r);
			DEF;
			INT ret = 0;
			if (g_L <= mid) ret = queryLeft_(lc, l, mid);
			if (ret) return ret;
			if (g_R > mid) ret = queryLeft_(rc, mid + 1, r);
			return ret;
		}
		INT queryRight_(PARAM)
		{
			if (l == r)
			{
				if (nodes[node].val) return 0;
				return r;
			}
			if (g_L <= l && r <= g_R)
			{
				if (!nodes[node].val) return r;
				else if (nodes[node].val == r - l + 1) return 0;
			}
			pushdown(node, l, r);
			DEF;
			INT ret = 0;
			if (g_R > mid) ret = queryRight_(rc, mid + 1, r);
			if (ret) return ret;
			if (g_L <= mid) ret = queryRight_(lc, l, mid);
			return ret;
		}
		INT queryPos_(PARAM)
		{
			if (l == r)
			{
				return l;
			}
			pushdown(node, l, r);
			DEF;
			if (nodes[rc].min >= 0)
				return queryPos_(lc, l, mid);
			else
				return queryPos_(rc, mid + 1, r);
		}
		INT query_(PARAM)
		{
			if (l == r)
			{
				return nodes[node].val;
			}
			pushdown(node, l, r);
			DEF;
			if (g_Pos <= mid) return query_(lc, l, mid);
			if (g_Pos > mid) return query_(rc, mid + 1, r);
		}
		INT query2_(PARAM)
		{
			if (g_L <= l && r <= g_R)
			{
				return nodes[node].val;
			}
			pushdown(node, l, r);
			DEF;
			INT ret = 0;
			if (g_L <= mid) ret += query2_(lc, l, mid);
			if (g_R > mid) ret += query2_(rc, mid + 1, r);
			return ret;
		}

	public:
		void build(INT* a, PARAM)
		{
			if (l == r)
			{
				nodes[node].min = nodes[node].val = a[l];
				return;
			}
			DEF;
			build(a, lc, l, mid);
			build(a, rc, mid + 1, r);
			nodes[node].min = std::min(nodes[lc].min, nodes[rc].min);
			nodes[node].val = nodes[lc].val + nodes[rc].val;
		}
		void modify(INT l, INT r, INT val)
		{
			g_L = l;
			g_R = r;
			g_Val = val;
			modify_(1, 1, n);
		}
		void add(INT l, INT r, INT val)
		{
			g_L = l;
			g_R = r;
			g_Val = val;
			add_(1, 1, n);
		}
		INT queryLeft(INT l, INT r)
		{
			if (r < l) return 0;
			g_L = l;
			g_R = r;
			return queryLeft_(1, 1, n);
		}
		INT queryRight(INT l, INT r)
		{
			if (r < l) return 0;
			g_L = l;
			g_R = r;
			return queryRight_(1, 1, n);
		}
		INT queryPos()
		{
			return queryPos_(1, 1, n);
		}
		INT query(INT pos)
		{
			g_Pos = pos;
			return query_(1, 1, n);
		}
		INT query(INT l, INT r)
		{
			g_L = l;
			g_R = r;
			return query2_(1, 1, n);
		}
	};
	class SegTreeA : public SegTree
	{
		void pushdown(PARAM)
		{
			if (nodes[node].bLazy)
			{
				DEF;
				nodes[lc].val += nodes[node].lazy * (mid - l + 1);
				nodes[rc].val += nodes[node].lazy * (r - mid);
				nodes[lc].min += nodes[node].lazy;
				nodes[rc].min += nodes[node].lazy;
				nodes[lc].lazy += nodes[node].lazy;
				nodes[rc].lazy += nodes[node].lazy;
				nodes[node].lazy = 0;
				nodes[node].bLazy = false;
				nodes[lc].bLazy = true;
				nodes[rc].bLazy = true;
			}
		}
	} d;
	class SetTreeM : public SegTree
	{
		void pushdown(PARAM)
		{
			if (nodes[node].bLazy)
			{
				DEF;
				nodes[lc].val = nodes[node].lazy * (mid - l + 1);
				nodes[rc].val = nodes[node].lazy * (r - mid);
				nodes[lc].lazy = nodes[node].lazy;
				nodes[rc].lazy = nodes[node].lazy;
				nodes[node].lazy = false;
				nodes[node].bLazy = false;
				nodes[lc].bLazy = true;
				nodes[rc].bLazy = true;
			}
		}
	} unavai;

	INT nStudent;
	INT sum;
	INT contri[maxn];

	work() : nStudent(), contri()
	{
		for (int i = 1; i <= n; i++)
		{
			nStudent += origin[i];
			sum += origin[i] * i;
			contri[1] -= origin[i];
			contri[i + 1] += origin[i] * 2;
		}
		for (int i = 1; i <= n; i++)
			contri[i] += contri[i - 1];
		d.build(contri, 1, 1, n);

		while (q--)
		{
			INT ins = readIn();
			switch (ins)
			{
			case 1:
			case 2:
			{
				INT pos = readIn();
				INT val = readIn();
				if (ins == 2) val = -val;

				d.add(1, pos, -val);
				d.add(pos + 1, n, val);

				nStudent += val;
				sum += pos * val;
				break;
			}
			case 3:
			case 4:
			{
				INT l = readIn();
				INT r = readIn();
				bool t = false;
				if (ins == 4) t = true;
				unavai.modify(l, r, t);
				break;
			}
			}

			INT p = d.queryPos();
			if (!unavai.query(p)) printOut(p);
			else
			{
				INT lp = unavai.queryRight(1, p - 1);
				INT rp = unavai.queryLeft(p + 1, n);
				if (!lp && !rp) printOut(-1);
				else if (!lp && rp) printOut(rp);
				else if (lp && !rp) printOut(lp);
				else
				{
					if (-d.query(lp + 1, p) < d.query(p + 1, rp))
						printOut(lp);
					else
						printOut(rp);
				}
			}
		}
	}
};

void run()
{
	n = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++) origin[i] = readIn();

	//	if (n <= 2000 && q <= 2000)
	//		RunInstance(cheat1);
	//	else
	//		RunInstance(cheat2);

	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("position.in", "r", stdin);
	freopen("position.out", "w", stdout);
#endif
	run();
	return 0;
}
