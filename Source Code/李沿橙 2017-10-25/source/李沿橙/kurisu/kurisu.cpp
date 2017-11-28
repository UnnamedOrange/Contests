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
		char buffer[12];
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
	}
	putchar('\n');
}

#define MOD(x) ((x) % mod)
#define MOD2(x) ((((x) % mod) + mod) % mod)
const INT mod = 20170927;
const INT maxn = INT(1e6) + 5;
INT n, m;

INT vx[maxn];
INT vy[maxn];

#define RunInstance(x) delete new x
struct cheat
{
	cheat()
	{
		while (m--)
		{
			INT ins = readIn();
			if (ins == 1)
			{
				INT p = readIn();
				vx[p] = readIn();
				vy[p] = readIn();
			}
			else if (ins == 2)
			{
				INT l = readIn();
				INT r = readIn();
				INT ans = 0;
				for (int i = l; i <= r; i++)
				{
					for (int j = i + 1; j <= r; j++)
					{
						INT cross = (vx[i] * vy[j] - vx[j] * vy[i]) % mod;
						cross = cross * cross % mod;
						ans = (ans + cross) % mod;
					}
				}
				printOut(ans);
			}
		}
	}
};
struct work
{
	struct BIT
	{
#define lowbit(x) ((x) & -(x))
		INT bit[maxn];
		BIT() : bit() {}

		void add(INT x, INT val)
		{
			while (x <= n)
			{
				bit[x] = MOD(bit[x] + val);
				x += lowbit(x);
			}
		}
		INT query(INT x)
		{
			INT ret = 0;
			while (x > 0)
			{
				ret = MOD(ret + bit[x]);
				x -= lowbit(x);
			}
			return ret;
		}
		INT query(INT l, INT r)
		{
			return MOD(query(r) - query(l - 1));
		}
	} x2, y2, xy;

	work()
	{
		for (int i = 1; i <= n; i++)
		{
			xy.add(i, vx[i] * vy[i]);
			x2.add(i, vx[i] * vx[i]);
			y2.add(i, vy[i] * vy[i]);
		}
		while (m--)
		{
			INT ins = readIn();
			if (ins == 1)
			{
				INT p = readIn();
				xy.add(p, -vx[p] * vy[p]);
				x2.add(p, -vx[p] * vx[p]);
				y2.add(p, -vy[p] * vy[p]);

				vx[p] = readIn();
				vy[p] = readIn();

				xy.add(p, vx[p] * vy[p]);
				x2.add(p, vx[p] * vx[p]);
				y2.add(p, vy[p] * vy[p]);
			}
			else
			{
				INT l = readIn();
				INT r = readIn();

				INT ans = x2.query(l, r) * y2.query(l, r) % mod;
				INT qxy = xy.query(l, r);
				ans = MOD2(ans - qxy * qxy);
				printOut(ans);
			}
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		vx[i] = readIn();
		vy[i] = readIn();
	}
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("kurisu.in", "r", stdin);
	freopen("kurisu.out", "w", stdout);
#endif
	run();
	return 0;
}
