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
	if(!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[9];
		INT length = 0;
		while(x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		do
		{
			putchar(buffer[--length]);
		}
		while(length);
	}
	putchar('\n');
}

const INT maxn = INT(3e5) + 5;
INT n, m;
INT origin[maxn];

#define RunInstance(x) delete new x
struct cheat
{
	cheat()
	{
		while(m--)
		{
			INT ins = readIn();
			if(ins == 1)
			{
				INT l = readIn();
				INT r = readIn();
				INT c = readIn();
				INT ans = 0;
				for(int i = l; i <= r; i++)
				{
					if(origin[i] == c) ans++;
				}
				printOut(ans);
			}
			else if(ins == 2)
			{
				INT x = readIn();
				std::swap(origin[x], origin[x + 1]);
			}
		}
	}
};
struct work
{
	class SegTree
	{
		INT sum[1048580];

#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1
		INT g_L, g_R, g_Val, g_Pos;
		void modify_(PARAM)
		{
			if(l == r)
			{
				sum[node] += g_Val;
				return;
			}
			DEF;
			if(g_Pos <= mid) modify_(lc, l, mid);
			if(g_Pos > mid) modify_(rc, mid + 1, r);
			sum[node] = sum[lc] + sum[rc];
		}
		INT query_(PARAM)
		{
			if(g_L <= l && r <= g_R)
			{
				return sum[node];
			}
			DEF;
			INT ret = 0;
			if(g_L <= mid) ret += query_(lc, l, mid);
			if(g_R > mid) ret += query_(rc, mid + 1, r);
			return ret;
		}

	public:
		SegTree() : sum() {}

		void inc(INT x)
		{
			g_Pos = x;
			g_Val = 1;
			modify_(1, 1, n);
		}
		void dec(INT x)
		{
			g_Pos = x;
			g_Val = -1;
			modify_(1, 1, n);
		}

		INT query(INT l, INT r)
		{
			g_L = l;
			g_R = r;
			return query_(1, 1, n);
		}
	} st[10];

	work()
	{
		for(int i = 1; i <= n; i++)
		{
			if(origin[i] > 10) return;
			st[origin[i] - 1].inc(i);
		}

		while(m--)
		{
			INT ins = readIn();
			if(ins == 1)
			{
				INT l = readIn();
				INT r = readIn();
				INT c = readIn();
				printOut(st[c - 1].query(l, r));
			}
			else if(ins == 2)
			{
				INT x = readIn();
				st[origin[x] - 1].dec(x);
				st[origin[x + 1] - 1].dec(x + 1);
				st[origin[x] - 1].inc(x + 1);
				st[origin[x + 1] - 1].inc(x);
				std::swap(origin[x], origin[x + 1]);
			}
		}
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

	if(n <= 1000)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
#endif
	run();
	return 0;
}
