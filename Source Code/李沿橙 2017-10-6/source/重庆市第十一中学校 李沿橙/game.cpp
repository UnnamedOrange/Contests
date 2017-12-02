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
	if(!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[12];
		INT length = 0;
		bool minus = x < 0;
		x = x < 0 ? -x : x;
		while(x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if(minus)
		{
			buffer[length++] = '-';
		}
		do
		{
			putchar(buffer[--length]);
		}
		while(length);
	}
	putchar('\n');
}

const INT mod = INT(1e9) + 7;
const INT maxn = 50005;
INT n, m;
INT origin[maxn];
struct InsSet
{
	struct Ins
	{
		INT type;
		union
		{
			struct
			{
				INT l, r, val;
			} add;
			struct
			{
				INT l, r;
			} minus;
			struct
			{
				INT l, r, k;
			} query;
		};
	} ins[maxn];

	bool haveMinus;
	INT maxK;

	InsSet() : haveMinus(), maxK() {}
	Ins& operator[] (INT x)
	{
		return ins[x];
	}
	void read(INT i)
	{
		ins[i].type = readIn();
		if(ins[i].type == 1)
		{
			ins[i].add.l = readIn();
			ins[i].add.r = readIn();
			ins[i].add.val = readIn();
		}
		else if(ins[i].type == 2)
		{
			ins[i].minus.l = readIn();
			ins[i].minus.r = readIn();
			haveMinus = true;
		}
		else if(ins[i].type == 3)
		{
			ins[i].query.l = readIn();
			ins[i].query.r = readIn();
			ins[i].query.k = readIn();
			maxK = std::max(maxK, ins[i].query.k);
		}
	}
} ins;

#define RunInstance(x) delete new x
struct cheat2
{
	class SegTree
	{
		struct Node
		{
			INT sum;

			INT add;
			bool minus;

			Node() : sum(), add(), minus() {}
		} nodes[131080];

#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1

		INT g_L, g_R, g_Val;
		void pushDown(PARAM)
		{
			DEF;
			if(nodes[node].add)
			{
				nodes[lc].sum += nodes[node].add * (mid - l + 1);
				nodes[rc].sum += nodes[node].add * (r - mid);
				nodes[lc].add += nodes[node].add;
				nodes[rc].add += nodes[node].add;
				nodes[node].add = 0;
			}
			if(nodes[node].minus)
			{
				nodes[lc].sum = -nodes[lc].sum;
				nodes[rc].sum = -nodes[rc].sum;
				nodes[lc].minus = !nodes[lc].minus;
				nodes[rc].minus = !nodes[rc].minus;
				nodes[node].minus = false;
			}
		}

		void add_(PARAM)
		{
			if(l != r) pushDown(node, l, r);
			if(g_L <= l && r <= g_R)
			{
				nodes[node].sum += g_Val * (r - l + 1);
				nodes[node].add += g_Val;
				return;
			}
			DEF;
			if(g_L <= mid) add_(lc, l, mid);
			if(g_R > mid) add_(rc, mid + 1, r);
			nodes[node].sum = nodes[lc].sum + nodes[rc].sum;
		}
		void minus_(PARAM)
		{
			if(l != r) pushDown(node, l, r);
			if(g_L <= l && r <= g_R)
			{
				nodes[node].sum = -nodes[node].sum;
				nodes[node].minus = true;
				return;
			}
			DEF;
			if(g_L <= mid) minus_(lc, l, mid);
			if(g_R > mid) minus_(rc, mid + 1, r);
			nodes[node].sum = nodes[lc].sum + nodes[rc].sum;
		}
		INT query_(PARAM)
		{
			if(g_L <= l && r <= g_R)
			{
				return nodes[node].sum;
			}
			pushDown(node, l, r);
			DEF;
			INT ret = 0;
			if(g_L <= mid) ret += query_(lc, l, mid);
			if(g_R > mid) ret += query_(rc, mid + 1, r);
			return ret;
		}

	public:
		void build(PARAM)
		{
			if(l == r)
			{
				nodes[node].sum = origin[l];
				return;
			}
			DEF;
			build(lc, l, mid);
			build(rc, mid + 1, r);
			nodes[node].sum = nodes[lc].sum + nodes[rc].sum;
		}
		void add(INT l, INT r, INT val)
		{
			g_L = l;
			g_R = r;
			g_Val = val;
			add_(1, 1, n);
		}
		void minus(INT l, INT r)
		{
			g_L = l;
			g_R = r;
			minus_(1, 1, n);
		}
		INT query(INT l, INT r)
		{
			g_L = l;
			g_R = r;
			return query_(1, 1, n);
		}
	} st;

	cheat2()
	{
		st.build(1, 1, n);
		for(int o = 1; o <= m; o++)
		{
			if(ins[o].type == 1)
			{
				st.add(ins[o].add.l, ins[o].add.r, ins[o].add.val);
			}
			else if(ins[o].type == 2)
			{
				st.minus(ins[o].add.l, ins[o].add.r);
			}
			else if(ins[o].type == 3)
			{
				printOut((st.query(ins[o].query.l, ins[o].query.r) % mod + mod) % mod);
			}
		}
	}
};
struct cheat1
{
	cheat1()
	{
		for(int o = 1; o <= m; o++)
		{
			if(ins[o].type == 1)
			{
				for(int i = ins[o].add.l; i <= ins[o].add.r; i++)
				{
					origin[i] += ins[o].add.val;
				}
			}
			else if(ins[o].type == 2)
			{
				for(int i = ins[o].minus.l; i <= ins[o].minus.r; i++)
				{
					origin[i] = -origin[i];
				}
			}
			else if(ins[o].type == 3)
			{
				INT ans = 0;
				INT sum = 0;
				for(int i = ins[o].query.l; i <= ins[o].query.r; i++)
				{
					sum = (sum + origin[i] % mod + mod) % mod;
				}
				if(ins[o].query.k == 1)
				{
					ans = sum;
				}
				else if(ins[o].query.k == 2)
				{
					for(int i = ins[o].query.l; i <= ins[o].query.r; i++)
					{
						ans = (ans + (sum - origin[i]) % mod * origin[i] % mod + mod) % mod;
					}
					ans = ans * 500000004 % mod;
				}
				printOut(ans);
			}
		}
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	m = readIn();
	for(int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
	}
	for(int i = 1; i <= m; i++)
	{
		ins.read(i);
	}

	if(n * m <= 100 * 50000 && ins.maxK <= 2)
		RunInstance(cheat1);
	else if(ins.maxK <= 1) RunInstance(cheat2);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	run();
	return 0;
}
