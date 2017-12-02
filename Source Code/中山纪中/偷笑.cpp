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

const INT maxn = 300005;
const INT laughter[] =
{
	0, 2, 3, 22, 23, 32, 33, 222, 223, 232, 233, 322, 323, 332, 333, 2222, 2223, 2232, 2233, 2322, 2323, 2332, 2333, 3222, 3223, 3232, 3233, 3322, 3323, 3332, 3333, 0x7fffffff
};
INT n, m;

INT Index[maxn];
class SegTree
{
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1
#define PARAM INT node = 1, INT l = 1, INT r = n
	struct node
	{
		INT sub;
		INT count_;
		INT lazy;

		node() : sub(), count_(), lazy()
		{
		}
	};
	std::vector<node> tree;
	INT g_L, g_R, g_Val;

	void modify(PARAM)
	{
		if (tree[node].sub >= 0)
		{
			return;
		}
		DEF;
		if (l == r)
		{
			while (tree[node].sub < 0)
			{
				tree[node].sub += laughter[Index[l] + 1] - laughter[Index[l]];
				Index[l]++;
			}
			return;
		}
		pushdown(node, l, r);
		modify(lc, l, mid);
		modify(rc, mid + 1, r);
		update(node, l, r, lc, rc);
	}
	void pushdown(INT node, INT l, INT r)
	{
		DEF;
		if (tree[node].lazy)
		{
			tree[lc].sub -= tree[node].lazy;
			tree[rc].sub -= tree[node].lazy;
			tree[lc].lazy += tree[node].lazy;
			tree[rc].lazy += tree[node].lazy;
			tree[node].lazy = 0;
		}
	}
	void update(INT node, INT l, INT r, INT lc, INT rc)
	{
		if (tree[lc].sub < tree[rc].sub)
		{
			tree[node].sub = tree[lc].sub;
			tree[node].count_ = tree[lc].count_;
		}
		else if (tree[lc].sub == tree[rc].sub)
		{
			tree[node].sub = tree[lc].sub;
			tree[node].count_ = tree[lc].count_ + tree[rc].count_;
		}
		else
		{
			tree[node].sub = tree[rc].sub;
			tree[node].count_ = tree[rc].count_;
		}
	}

	void add_(PARAM)
	{
		modify(node, l, r);
		if (g_L <= l && r <= g_R)
		{
			tree[node].sub -= g_Val;
			tree[node].lazy += g_Val;
			modify(node, l, r);
			return;
		}
		pushdown(node, l, r);
		DEF;
		if (g_L <= mid) add_(lc, l, mid);
		if (g_R > mid) add_(rc, mid + 1, r);
		update(node, l, r, lc, rc);
	}
	INT query_(PARAM)
	{
		modify(node, l, r);
		if (g_L <= l && r <= g_R)
		{
			if (tree[node].sub == 0) return tree[node].count_;
			return 0;
		}
		pushdown(node, l, r);
		DEF;
		INT ans = 0;
		if (g_L <= mid) ans += query_(lc, l, mid);
		if (g_R > mid) ans += query_(rc, mid + 1, r);
		return ans;
	}

public:
	SegTree() : tree(1048600)
	{
	}
	void build(INT node = 1, INT l = 1, INT r = n)
	{
		if (l == r)
		{
			INT val = readIn();
			Index[l] = 1;
			while (val > laughter[Index[l]]) Index[l]++;
			val = laughter[Index[l]] - val;
			tree[node].sub = val;
			tree[node].count_ = 1;
			return;
		}
		DEF;
		build(lc, l, mid);
		build(rc, mid + 1, r);
		update(node, l, r, lc, rc);
	}

	void add(INT l, INT r, INT x)
	{
		g_L = l;
		g_R = r;
		g_Val = x;
		add_();
	}

	INT query(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		return query_();
	}
} st;

void run()
{
	n = readIn();
	m = readIn();
	st.build();

	while (m--)
	{
		char buffer[10];
		scanf("%s", buffer);
		INT l = readIn();
		INT r = readIn();
		if (buffer[0] == 'c')
		{
			printOut(st.query(l, r));
		}
		else if (buffer[0] == 'a')
		{
			st.add(l, r, readIn());
		}
	}
}

int main()
{
	run();
	return 0;
}