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
	char buffer[20];
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

const INT maxn = INT(2e5) + 5;
INT n, q;
INT parent[maxn];
INT b[maxn], l[maxn];
struct Edge
{
	INT to;
	INT next;
} edges[maxn];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

INT seq[maxn];
INT dfn[maxn];
INT end[maxn];
void dfs1(INT node)
{
	static INT clock;
	clock++;
	dfn[node] = clock;
	seq[clock] = node;
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		dfs1(to);
	}
	end[node] = clock;
}

struct SegTree
{
	struct Node
	{
		INT a[3];
		INT b[3];
		Node()
		{
			a[0] = a[1] = a[2] = b[0] = b[1] = b[2] = -1;
		}
	} nodes[524300];

#define NODE INT* a = nodes[node].a; INT* b = nodes[node].b
#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1
#define CNT node, l, r
#define LC lc, l, mid
#define RC rc, mid + 1, r

	static void maxSame(INT& c1, INT& c2, INT& c3, INT a1, INT a2, INT a3, INT a4, INT a5, INT a6)
	{
		INT c[] = { a1, a2, a3, a4, a5, a6 };
		const INT size = sizeof(c) / sizeof(INT);
		std::sort(c, c + size, std::greater<INT>());
		c1 = c[0];
		c2 = c[1];
		c3 = c[2];
	}
	static void maxDiff(INT& c1, INT& c2, INT& c3, INT a1, INT a2, INT a3, INT a4, INT a5, INT a6)
	{
		INT c[] = { a1, a2, a3, a4, a5, a6 };
		const INT size = sizeof(c) / sizeof(INT);
		std::sort(c, c + size, std::greater<INT>());
		INT t = std::unique(c, c + size) - c;
		c1 = c2 = c3 = -1;
		if (t > 0) c1 = c[0];
		if (t > 1) c2 = c[1];
		if (t > 2) c3 = c[2];
	}
	void update(PARAM)
	{
		NODE;
		DEF;
		maxSame(a[0], a[1], a[2], nodes[lc].a[0], nodes[lc].a[1], nodes[lc].a[2], nodes[rc].a[0], nodes[rc].a[1], nodes[rc].a[2]);
		maxDiff(b[0], b[1], b[2], nodes[lc].b[0], nodes[lc].b[1], nodes[lc].b[2], nodes[rc].b[0], nodes[rc].b[1], nodes[rc].b[2]);
	}

	INT g_L, g_R;
	void query_(PARAM)
	{
		NODE;
		if (g_L <= l && r <= g_R)
		{
			maxSame(A[0], A[1], A[2], A[0], A[1], A[2], a[0], a[1], a[2]);
			maxDiff(B[0], B[1], B[2], B[0], B[1], B[2], b[0], b[1], b[2]);
			return;
		}
		DEF;
		if (g_L <= mid) query_(LC);
		if (g_R > mid) query_(RC);
	}

public:
	SegTree() {}

	typedef INT(*Func)(INT idx);
	void build(PARAM, Func f)
	{
		NODE;
		if (l == r)
		{
			a[0] = b[0] = f(l);
			return;
		}
		DEF;
		build(LC, f);
		build(RC, f);
		update(CNT);
	}

	INT A[3];
	INT B[3];
	void clearCache()
	{
		A[0] = A[1] = A[2] = B[0] = B[1] = B[2] = -1;
	}
	void query(INT l, INT r)
	{
		if (l > r) return;
		g_L = l;
		g_R = r;
		query_(1, 1, n);
	}
} stb, stl;
INT getb(INT x)
{
	return b[seq[x]];
}
INT getl(INT x)
{
	return l[seq[x]];
}

void work()
{
	dfs1(1);
	stb.build(1, 1, n, getb);
	stl.build(1, 1, n, getl);
	while (q--)
	{
		INT leader = readIn();
		stb.clearCache();
		stb.query(dfn[leader], end[leader]);
		stl.clearCache();
		stl.query(1, dfn[leader] - 1);
		stl.query(end[leader] + 1, n);

		INT ans = 0;
		//no a2: ans = 0
		if (!~stb.A[1])
			ans = 0;
		else if (stb.A[0] == stb.A[1])
		{
			if (~stl.B[0] && stl.B[0]) //l1 exists: ans = a1
				ans = stb.A[0];
			else if (~stb.B[1]) //b1 exists: ans = b1
				ans = stb.B[1];
			else //else: all are a1, and no l1, ans = 0
				ans = 0;
		}
		else
		{
			ans = stb.B[1];
			//notice: only 3 circumstances exist: b2 + l1, b2 + l2, b3 + l1 
			for (int i = 0; i < 2 && ~stl.B[i]; i++)
				for (int j = 1; j < 3 - i && ~stb.B[j]; j++)
					ans = std::max(ans, std::min(stb.B[j] + stl.B[i], stb.A[0]) % std::max(stb.B[j] + stl.B[i], stb.A[0]));
		}
		printOut(ans);
	}
}

void run()
{
	n = readIn();
	q = readIn();
	for (int i = 2; i <= n; i++)
	{
		parent[i] = readIn();
		addEdge(parent[i], i);
	}
	for (int i = 1; i <= n; i++)
	{
		b[i] = readIn();
		l[i] = readIn();
	}

	work();
}

int main()
{
#ifndef LOCAL
	freopen("soldier.in", "r", stdin);
	freopen("soldier.out", "w", stdout);
#endif
	run();
	return 0;
}
