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
typedef double REAL;
INT readIn()
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
void printOut(INT x)
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

const INT maxn = 50005;
INT n, p;
INT parent[maxn];
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

INT depth[maxn];
INT seq[maxn];
INT dfn[maxn];
INT end[maxn];
INT dfs(INT node)
{
	static INT clock;
	++clock;
	seq[clock] = node;
	dfn[node] = clock;
	depth[node] = depth[parent[node]] + 1;
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		dfs(to);
	}
	end[node] = clock;
}

#define RunInstance(x) delete new x
struct work
{
	class SegTree
	{
		struct Node
		{
			INT sum;
			INT sumd;
			INT lazy1;
			INT lazy2;
			Node() : sum(), sumd(), lazy1(), lazy2() {}
		} nodes[131100];

#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1
#define LC lc, l, mid
#define RC rc, mid + 1, r
#define NODE node, l, r
#define CNT INT& sum = nodes[node].sum; INT& sumd = nodes[node].sumd; INT& lazy1 = nodes[node].lazy1; INT& lazy2 = nodes[node].lazy2

		INT g_L, g_R;
		INT g_Val, g_D;

		void cover(PARAM, INT val1, INT val2)
		{
			CNT;
			sum += val1 * (r - l + 1) + val2 * sumd;
			lazy1 += val1;
			lazy2 += val2;
		}

		void pushdown(PARAM)
		{
			CNT;
			DEF;
			if (lazy1 || lazy2)
			{
				cover(LC, lazy1, lazy2);
				cover(RC, lazy1, lazy2);
				lazy1 = lazy2 = 0;
			}
		}
		void update(PARAM)
		{
			CNT;
			DEF;
			sum = nodes[lc].sum + nodes[rc].sum;
		}

		void add_(PARAM)
		{
			CNT;
			if (g_L <= l && r <= g_R)
			{
				cover(NODE, g_Val, 1);
				return;
			}
			DEF;
			pushdown(NODE);
			INT ans = 0;
			if (g_L <= mid) add_(LC);
			if (g_R > mid) add_(RC);
			update(NODE);
		}
		INT query_(PARAM)
		{
			CNT;
			if (g_L <= l && r <= g_R)
			{
				return sum;
			}
			DEF;
			pushdown(NODE);
			INT ans = 0;
			if (g_L <= mid) ans += query_(LC);
			if (g_R > mid) ans += query_(RC);
			return ans;
		}

	public:
		void build(PARAM)
		{
			CNT;
			if (l == r)
			{
				sumd = depth[seq[l]];
				return;
			}
			DEF;
			build(LC);
			build(RC);
			sumd = nodes[lc].sumd + nodes[rc].sumd;
		}
		void add(INT l, INT r, INT val, INT d)
		{
			g_L = l;
			g_R = r;
			g_Val = val - d;
			add_(1, 1, n);
		}
		INT query(INT l, INT r)
		{
			g_L = l;
			g_R = r;
			return query_(1, 1, n);
		}
	} st;

	work()
	{
		st.build(1, 1, n);
		while (p--)
		{
			char ins;
			scanf(" %c ", &ins);
			if (ins == 'A')
			{
				INT x = readIn();
				INT val = readIn();
				st.add(dfn[x], end[x], val, depth[x]);
			}
			else if (ins == 'Q')
			{
				INT x = readIn();
				printOut(st.query(dfn[x], end[x]));
			}
		}
	}
};

void run()
{
	n = readIn();
	p = readIn();
	for (int i = 2; i <= n; i++)
	{
		parent[i] = readIn();
		addEdge(parent[i], i);
	}
	dfs(1);

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("truetears.in", "r", stdin);
	freopen("truetears.out", "w", stdout);
#endif
	run();
	return 0;
}
