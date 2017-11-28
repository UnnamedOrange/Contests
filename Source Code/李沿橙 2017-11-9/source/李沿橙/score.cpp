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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 1005;
const INT maxt = 3005;
INT n, t;
struct Problem
{
	INT a;
	INT b;
	INT c;
	void read()
	{
		a = readIn();
		b = readIn();
		c = readIn();
	}
	bool operator< (const Problem& b) const
	{
		return (long long)c * b.b < (long long)b.c * this->b;
	}
} p[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const INT maxN = 15;
	INT ans;

	INT ts[(1 << 10) + 5];
	INT f[maxN][(1 << 10) + 5];

	brute() : ans(), ts(), f()
	{
		INT U = 1 << n;
		for (int S = 1; S < U; S++)
			for (int i = 0; i < n; i++)
				if (S & (1 << i))
					ts[S] += p[i + 1].c;

		for (int i = 0; i < n; i++)
			f[i][1 << i] = p[i + 1].a - p[i + 1].b * ts[1 << i];
		for (int S = 1; S < U; S++)
		{
			if (ts[S] > t) continue;
			for (int i = 0; i < n; i++)
			{
				if (!(S & (1 << i))) continue;
				INT S0 = S ^ (1 << i);
				for (int j = 0; j < n; j++)
				{
					if (!(S0 & (1 << j))) continue;
					f[i][S] = std::max(f[i][S], f[j][S0] + p[i + 1].a - p[i + 1].b * ts[S]);
				}
				ans = std::max(ans, f[i][S]);
			}
		}
		printOut(ans);
	}
};
struct work
{
	INT f[maxt];

	work() : f()
	{
		for (int i = 1; i <= n; i++)
			for (int j = t; j >= p[i].c; j--)
				f[j] = std::max(f[j], f[j - p[i].c] + p[i].a - p[i].b * j);
		for (int i = 1; i <= t; i++)
			f[t] = std::max(f[t], f[i]);
		printOut(f[t]);
	}
};

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		t = readIn();
		INT minb = INF;
		INT maxb = 0;
		for (int i = 1; i <= n; i++)
		{
			p[i].read();
			minb = std::min(minb, p[i].b);
			maxb = std::max(maxb, p[i].b);
		}
		std::sort(p + 1, p + 1 + n);

		RunInstance(work);
	}
}

int main()
{
#ifndef LOCAL
	freopen("score.in", "r", stdin);
	freopen("score.out", "w", stdout);
#endif
	run();
	return 0;
}
